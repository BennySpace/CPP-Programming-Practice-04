#include "Application.h"
#include "layout/Layouts.h"
#include "rendering/RenderHelpers.h"
#include "sfml/SfmlUtils.h"
#include "text/UiText.h"
#include "BitmapText.h"

void Application::drawMainMenu() {
    using layout = app_layout::MainMenuLayout;

    // Main menu container panel.
    const sf::FloatRect panelRect =
#ifndef NDEBUG
        debugRectOverride("main.panel", layout::panel_rect());
#else
        layout::panel_rect();
#endif
    drawPanel(panelRect, sf::Color(22, 22, 24), sf::Color(186, 62, 56), 3.0f);

    // Main menu title text.
    const sf::FloatRect titleRect = debugRectOverride("main.title_text", {{layout::kTitleX, layout::kTitleY}, {520.0f, 32.0f}});
    bitmap_text::draw_text(mWindow, app_text::kMainMenuTitle, titleRect.position, 3.0f, sf::Color(255, 217, 116));

    // Start lights decoration above the track cards.
    for (int light = 0; light < 5; ++light) {
        sf::CircleShape startLight(layout::kStartLightRadius);
        startLight.setPosition({layout::kStartLightX + static_cast<float>(light) * layout::kStartLightStepX, layout::kStartLightY});
        startLight.setFillColor(light < 4 ? sf::Color(212, 42, 35) : sf::Color(255, 214, 67));
        mWindow.draw(startLight);
    }

    // Track preview cards with circuit image and title.
    for (size_t index = 0; index < mGame.races().size(); ++index) {
        const sf::FloatRect cardRect =
#ifndef NDEBUG
            debugRectOverride("main.track_card_" + std::to_string(index), layout::track_card(index));
#else
            layout::track_card(index);
#endif
        const sf::FloatRect photoRect =
#ifndef NDEBUG
            debugRectOverride("main.track_photo_" + std::to_string(index), layout::track_photo(index));
#else
            layout::track_photo(index);
#endif
        drawPanel(cardRect, sf::Color(36, 37, 41), sf::Color(138, 144, 154), 3.0f);

        if (const sf::Texture* texture = trackPreviewTexture(index); texture != nullptr) {
            drawPhotoFit(*texture, photoRect);
        } else {
            drawPhotoPlaceholder(photoRect);
        }

        bitmap_text::draw_text(
            mWindow,
            app_render_helpers::display_track_name(index),
            debugRectOverride("main.track_label_" + std::to_string(index), {{cardRect.position.x + layout::kTrackLabelCenterOffsetX, layout::kTrackLabelY}, {240.0f, 28.0f}}).position,
            3.0f,
            sf::Color(244, 245, 240),
            true);
    }
}

void Application::drawNewGameConfirmation() {
    using layout = app_layout::MainMenuLayout;
    using scene = app_layout::SceneLayout;

    // Dimmed backdrop behind the new game confirmation modal.
    sf::RectangleShape overlay({scene::kWindowWidth, scene::kWindowHeight});
    overlay.setPosition({0.0f, 0.0f});
    overlay.setFillColor(with_alpha(sf::Color(8, 8, 10), 180));
    mWindow.draw(overlay);

    // Confirmation modal window.
    const sf::FloatRect modalRect =
#ifndef NDEBUG
        debugRectOverride("main.confirm_modal", layout::confirm_modal_rect());
#else
        layout::confirm_modal_rect();
#endif
    drawPanel(modalRect, sf::Color(24, 24, 27), sf::Color(228, 83, 74), 3.0f);

    // Confirmation title and body copy.
    const sf::FloatRect confirmTitleRect = debugRectOverride("main.confirm_title_text", {{layout::kConfirmTitleCenterX, layout::kConfirmTitleY}, {320.0f, 32.0f}});
    bitmap_text::draw_text(mWindow, app_text::kConfirmNewGameTitle, confirmTitleRect.position, 3.3f, sf::Color(255, 221, 170), true);
    const sf::FloatRect confirmBodyRect = debugRectOverride("main.confirm_body_text", {{layout::kConfirmTextX, layout::kConfirmTextY}, {layout::kConfirmTextWidth, 80.0f}});
    drawWrapped(
        app_text::kConfirmNewGameBody,
        confirmBodyRect.position,
        1.7f,
        confirmBodyRect.size.x,
        sf::Color(232, 235, 240));
}
