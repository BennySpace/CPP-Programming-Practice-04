#include "Application.h"
#include "layout/Layouts.h"
#include "sfml/SfmlUtils.h"
#include "text/UiText.h"
#include "BitmapText.h"
#include <algorithm>
#include <sstream>

void Application::drawPanel(const sf::FloatRect& rect, const sf::Color& fill, const sf::Color& outline, const float outlineThickness) {
    using widget = app_layout::WidgetLayout;

    // Generic framed panel used by screen sections and modal containers.
    sf::RectangleShape panel(rect.size);
    panel.setPosition(rect.position);
    panel.setFillColor(fill);
    panel.setOutlineThickness(outlineThickness);
    panel.setOutlineColor(outline);
    mWindow.draw(panel);

    // Accent strip along the top edge of each panel.
    sf::RectangleShape topBar({rect.size.x, widget::kPanelAccentBarHeight});
    topBar.setPosition(rect.position);
    topBar.setFillColor(with_alpha(outline, 130));
    mWindow.draw(topBar);
}

void Application::drawPhotoFit(const sf::Texture& texture, const sf::FloatRect& rect) {
    sf::Sprite photo(texture);
    const sf::Vector2u textureSize = texture.getSize();
    const float scaleX = rect.size.x / static_cast<float>(textureSize.x);
    const float scaleY = rect.size.y / static_cast<float>(textureSize.y);
    const float fitScale = std::min(scaleX, scaleY);
    photo.setScale({fitScale, fitScale});

    const sf::FloatRect bounds = photo.getGlobalBounds();
    photo.setPosition({
        rect.position.x + (rect.size.x - bounds.size.x) * 0.5f,
        rect.position.y + (rect.size.y - bounds.size.y) * 0.5f
    });
    mWindow.draw(photo);
}

void Application::drawPhotoPlaceholder(const sf::FloatRect& rect, const float textScale) {
    using widget = app_layout::WidgetLayout;

    // Fallback card image placeholder when a texture is missing.
    drawPanel(rect, sf::Color(44, 46, 52), sf::Color(106, 112, 124), 2.0f);
    bitmap_text::draw_text(
        mWindow,
        app_text::kPhotoPlaceholder,
        {rect_center(rect).x, rect.position.y + rect.size.y * 0.5f - textScale * widget::kPhotoPlaceholderBaselineFactor},
        textScale,
        sf::Color(196, 200, 209),
        true);
}

void Application::drawItemCard(const Item& currentItem, const sf::FloatRect& rect, const bool selected, const bool museumStyle) {
    using widget = app_layout::WidgetLayout;

    // Reusable item card shell used in garage and museum lists.
    const sf::Color outline = selected ? sf::Color(255, 223, 130) : (museumStyle ? sf::Color(172, 145, 84) : sf::Color(126, 132, 144));
    drawPanel(rect, museumStyle ? sf::Color(55, 42, 28) : sf::Color(34, 35, 39), outline, 3.0f);

    // Decorative header stripe at the top of the item card.
    sf::RectangleShape stripe({rect.size.x - widget::kItemCardStripeInsetX * 2.0f, widget::kItemCardStripeHeight});
    stripe.setPosition({rect.position.x + widget::kItemCardStripeInsetX, rect.position.y + widget::kItemCardStripeY});
    stripe.setFillColor(museumStyle ? sf::Color(208, 173, 86) : sf::Color(236, 239, 233));
    mWindow.draw(stripe);

    // Item photo area inside the card.
    const sf::FloatRect photoRect(
        {rect.position.x + widget::kItemCardPhotoInsetX, rect.position.y + widget::kItemCardPhotoInsetY},
        {rect.size.x - widget::kItemCardPhotoInsetWidth, rect.size.y - widget::kItemCardBottomInset});
    if (const sf::Texture* texture = itemTexture(currentItem); texture != nullptr) {
        drawPhotoFit(*texture, photoRect);
    } else {
        drawPhotoPlaceholder(photoRect, 2.2f);
    }

    const float textWidth = rect.size.x - widget::kItemCardTextWidthInset;
    const float nameY = currentItem.mType == ItemType::equipment
        ? rect.position.y + rect.size.y - widget::kItemCardEquipmentNameOffsetY
        : rect.position.y + rect.size.y - widget::kItemCardLootNameOffsetY;
    drawWrapped(currentItem.mName, {rect.position.x + widget::kItemCardTextInsetX, nameY}, 1.75f, textWidth, sf::Color(236, 240, 248));

    if (currentItem.mType == ItemType::equipment) {
        if (currentItem.mIsEquipped) {
            bitmap_text::draw_text(
                mWindow,
                "ACTIVE",
                {rect.position.x + widget::kItemCardTextInsetX, rect.position.y + rect.size.y - widget::kItemCardMetaOffsetY - 18.0f},
                1.35f,
                sf::Color(255, 223, 130));
        }

        // Equipment durability label at the bottom of the card.
        const std::string durabilityText = currentItem.mIsBroken ? app_text::kBrokenLabel : app_text::format_durability(currentItem.mDurability);
        bitmap_text::draw_text(mWindow, durabilityText, {rect.position.x + widget::kItemCardTextInsetX, rect.position.y + rect.size.y - widget::kItemCardMetaOffsetY}, 1.6f, currentItem.mIsBroken ? sf::Color(255, 156, 156) : sf::Color(174, 241, 188));
    } else {
        // Loot value label at the bottom of the card.
        bitmap_text::draw_text(mWindow, app_text::format_item_value(currentItem.mValue), {rect.position.x + widget::kItemCardTextInsetX, rect.position.y + rect.size.y - widget::kItemCardMetaOffsetY}, 1.6f, sf::Color(255, 219, 152));
    }
}

void Application::drawWrapped(const std::string& text, const sf::Vector2f position, const float scale, const float width, const sf::Color& color) {
    std::istringstream input(text);
    std::string word;
    std::string currentLine;
    float currentY = position.y;

    while (input >> word) {
        const std::string candidate = currentLine.empty() ? word : currentLine + " " + word;
        if (bitmap_text::measure_text(to_upper_copy(candidate), scale) > width && !currentLine.empty()) {
            bitmap_text::draw_text(mWindow, currentLine, {position.x, currentY}, scale, color);
            currentLine = word;
            currentY += scale * 9.0f;
        } else {
            currentLine = candidate;
        }
    }

    if (!currentLine.empty()) {
        bitmap_text::draw_text(mWindow, currentLine, {position.x, currentY}, scale, color);
    }
}

void Application::drawButtons() {
    using widget = app_layout::WidgetLayout;

    // Shared action buttons collected for the current screen.
    for (const auto& currentButton : mScreenInteractions.mButtons) {
        drawPanel(
            currentButton.mRect,
            currentButton.mEnabled ? currentButton.mFill : sf::Color(62, 66, 76),
            currentButton.mEnabled ? currentButton.mAccent : sf::Color(98, 104, 118),
            2.0f);

        bitmap_text::draw_text(
            mWindow,
            currentButton.mLabel,
            {rect_center(currentButton.mRect).x, currentButton.mRect.position.y + widget::kButtonLabelOffsetY},
            2.2f,
            currentButton.mEnabled ? sf::Color(245, 247, 250) : sf::Color(176, 182, 193),
            true);
    }
}
