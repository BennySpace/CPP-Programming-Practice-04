#include "debug/DebugLayoutEditor.h"

#include "BitmapText.h"
#include <algorithm>
#include <sstream>

namespace {
constexpr float kMinRectSize = 1.0f;
constexpr float kOverlayX = 20.0f;
constexpr float kOverlayY = 760.0f;
constexpr float kOverlayWidth = 520.0f;
constexpr float kOverlayHeight = 140.0f;

const char* screen_name(const ApplicationScreen pScreen) {
    switch (pScreen) {
        case ApplicationScreen::main_menu:
            return "MAIN MENU";
        case ApplicationScreen::race_hub:
            return "RACE DECK";
        case ApplicationScreen::garage:
            return "GARAGE";
        case ApplicationScreen::museum:
            return "MUSEUM";
    }

    return "UNKNOWN";
}

const char* mode_name(const DebugLayoutMode pMode) {
    switch (pMode) {
        case DebugLayoutMode::panels:
            return "PANELS";
        case DebugLayoutMode::buttons:
            return "BUTTONS";
    }

    return "UNKNOWN";
}
}

void DebugLayoutEditor::toggle() {
    mEnabled = !mEnabled;
    mDragging = false;
}

bool DebugLayoutEditor::enabled() const {
    return mEnabled;
}

void DebugLayoutEditor::cycleMode() {
    mMode = mMode == DebugLayoutMode::panels ? DebugLayoutMode::buttons : DebugLayoutMode::panels;
    mSelectedIndex.reset();
    mDragging = false;
}

DebugLayoutMode DebugLayoutEditor::mode() const {
    return mMode;
}

void DebugLayoutEditor::rebuild(const ApplicationScreen pScreen, const std::vector<DebugEditableRect>& pRects) {
    if (!mEnabled) {
        return;
    }

    const std::string selectedName = selectedRect() != nullptr ? selectedRect()->mName : std::string{};

    mScreen = pScreen;
    mRects = pRects;
    mSelectedIndex.reset();

    if (selectedName.empty()) {
        return;
    }

    for (size_t index = 0; index < mRects.size(); ++index) {
        if (mRects[index].mName == selectedName) {
            mSelectedIndex = index;
            break;
        }
    }
}

std::optional<size_t> DebugLayoutEditor::hitTest(const sf::Vector2f pPoint) const {
    if (!mEnabled) {
        return std::nullopt;
    }

    for (size_t index = mRects.size(); index > 0; --index) {
        const DebugEditableRect& rect = mRects[index - 1];
        const bool modeMatches = mMode == DebugLayoutMode::buttons ? rect.mIsButton : !rect.mIsButton;
        if (modeMatches && rect.mRect.contains(pPoint)) {
            return index - 1;
        }
    }

    return std::nullopt;
}

void DebugLayoutEditor::select(const std::optional<size_t> pIndex) {
    if (pIndex.has_value() && *pIndex < mRects.size()) {
        mSelectedIndex = pIndex;
        return;
    }

    mSelectedIndex.reset();
}

void DebugLayoutEditor::beginDrag(const sf::Vector2f pMousePosition) {
    DebugEditableRect* rect = selectedRect();
    if (!mEnabled || rect == nullptr) {
        return;
    }

    mDragging = true;
    mDragOffset = pMousePosition - rect->mRect.position;
}

void DebugLayoutEditor::dragTo(const sf::Vector2f pMousePosition) {
    if (!mEnabled || !mDragging || !mSelectedIndex.has_value() || *mSelectedIndex >= mRects.size()) {
        return;
    }

    const sf::Vector2f targetPosition = pMousePosition - mDragOffset;
    const sf::Vector2f currentPosition = mRects[*mSelectedIndex].mRect.position;
    moveRectWithChildren(*mSelectedIndex, targetPosition.x - currentPosition.x, targetPosition.y - currentPosition.y);
}

void DebugLayoutEditor::endDrag() {
    mDragging = false;
}

void DebugLayoutEditor::nudgePosition(const float pDx, const float pDy) {
    if (!mEnabled || !mSelectedIndex.has_value() || *mSelectedIndex >= mRects.size()) {
        return;
    }

    moveRectWithChildren(*mSelectedIndex, pDx, pDy);
}

void DebugLayoutEditor::resizeSelected(const float pDw, const float pDh) {
    DebugEditableRect* rect = selectedRect();
    if (!mEnabled || rect == nullptr) {
        return;
    }

    rect->mRect.size.x = std::max(kMinRectSize, rect->mRect.size.x + pDw);
    rect->mRect.size.y = std::max(kMinRectSize, rect->mRect.size.y + pDh);
}

std::optional<sf::FloatRect> DebugLayoutEditor::rectOverride(const std::string& pName) const {
    if (!mEnabled) {
        return std::nullopt;
    }

    for (const DebugEditableRect& rect : mRects) {
        if (rect.mName == pName) {
            return rect.mRect;
        }
    }

    return std::nullopt;
}

void DebugLayoutEditor::moveRectWithChildren(const size_t pIndex, const float pDx, const float pDy) {
    if (pIndex >= mRects.size()) {
        return;
    }

    mRects[pIndex].mRect.position.x += pDx;
    mRects[pIndex].mRect.position.y += pDy;
    moveChildrenRecursive(mRects[pIndex].mName, pDx, pDy);
}

void DebugLayoutEditor::moveChildrenRecursive(const std::string& pParentName, const float pDx, const float pDy) {
    for (size_t index = 0; index < mRects.size(); ++index) {
        if (mRects[index].mParentName.has_value() && *mRects[index].mParentName == pParentName) {
            moveRectWithChildren(index, pDx, pDy);
        }
    }
}

void DebugLayoutEditor::draw(sf::RenderWindow& pWindow) const {
    if (!mEnabled) {
        return;
    }

    for (size_t index = 0; index < mRects.size(); ++index) {
        const DebugEditableRect& rect = mRects[index];
        const bool modeMatches = mMode == DebugLayoutMode::buttons ? rect.mIsButton : !rect.mIsButton;
        if (!modeMatches) {
            continue;
        }

        sf::RectangleShape outline(rect.mRect.size);
        outline.setPosition(rect.mRect.position);
        outline.setFillColor(sf::Color::Transparent);
        outline.setOutlineThickness(2.0f);
        outline.setOutlineColor(
            mSelectedIndex.has_value() && *mSelectedIndex == index
                ? sf::Color(255, 220, 80)
                : sf::Color(80, 200, 255));
        pWindow.draw(outline);
    }

    sf::RectangleShape overlay({kOverlayWidth, kOverlayHeight});
    overlay.setPosition({kOverlayX, kOverlayY});
    overlay.setFillColor(sf::Color(14, 16, 20, 220));
    overlay.setOutlineThickness(2.0f);
    overlay.setOutlineColor(sf::Color(80, 200, 255));
    pWindow.draw(overlay);

    bitmap_text::draw_text(pWindow, "LAYOUT EDITOR", {kOverlayX + 16.0f, kOverlayY + 12.0f}, 1.9f, sf::Color(244, 246, 249));
    bitmap_text::draw_text(pWindow, screen_name(mScreen), {kOverlayX + 300.0f, kOverlayY + 12.0f}, 1.8f, sf::Color(144, 230, 255));
    bitmap_text::draw_text(pWindow, mode_name(mMode), {kOverlayX + 300.0f, kOverlayY + 38.0f}, 1.6f, sf::Color(255, 220, 80));

    if (const DebugEditableRect* rect = selectedRect(); rect != nullptr) {
        bitmap_text::draw_text(pWindow, rect->mName, {kOverlayX + 16.0f, kOverlayY + 42.0f}, 1.45f, sf::Color(255, 220, 80));

        std::ostringstream metrics;
        metrics
            << "X " << static_cast<int>(rect->mRect.position.x)
            << "  Y " << static_cast<int>(rect->mRect.position.y)
            << "  W " << static_cast<int>(rect->mRect.size.x)
            << "  H " << static_cast<int>(rect->mRect.size.y);
        bitmap_text::draw_text(pWindow, metrics.str(), {kOverlayX + 16.0f, kOverlayY + 68.0f}, 1.55f, sf::Color(232, 236, 244));

        std::ostringstream rectCode;
        rectCode
            << "MAKE_RECT("
            << static_cast<int>(rect->mRect.position.x) << ", "
            << static_cast<int>(rect->mRect.position.y) << ", "
            << static_cast<int>(rect->mRect.size.x) << ", "
            << static_cast<int>(rect->mRect.size.y) << ")";
        bitmap_text::draw_text(pWindow, rectCode.str(), {kOverlayX + 16.0f, kOverlayY + 92.0f}, 1.3f, sf::Color(170, 224, 192));
    } else {
        bitmap_text::draw_text(pWindow, "SELECT RECT WITH LEFT MOUSE", {kOverlayX + 16.0f, kOverlayY + 50.0f}, 1.55f, sf::Color(232, 236, 244));
    }

    bitmap_text::draw_text(pWindow, "TAB MODE / DRAG / WASD / ARROWS / SHIFT", {kOverlayX + 16.0f, kOverlayY + 114.0f}, 1.35f, sf::Color(170, 178, 192));
}

DebugEditableRect* DebugLayoutEditor::selectedRect() {
    if (!mSelectedIndex.has_value() || *mSelectedIndex >= mRects.size()) {
        return nullptr;
    }

    return &mRects[*mSelectedIndex];
}

const DebugEditableRect* DebugLayoutEditor::selectedRect() const {
    if (!mSelectedIndex.has_value() || *mSelectedIndex >= mRects.size()) {
        return nullptr;
    }

    return &mRects[*mSelectedIndex];
}
