#include "Application.h"
#include "layout/Layouts.h"
#include "rendering/RenderHelpers.h"
#include "sfml/SfmlUtils.h"
#include "text/UiText.h"
#include "BitmapText.h"

void Application::drawMainMenu() {
    using layout = app_layout::MainMenuLayout;

    drawPanel(layout::panel_rect(), sf::Color(22, 22, 24), sf::Color(186, 62, 56), 3.0f);

    bitmap_text::draw_text(mWindow, app_text::kMainMenuTitle, {layout::kTitleX, layout::kTitleY}, 3.0f, sf::Color(255, 217, 116));

    for (int light = 0; light < 5; ++light) {
        sf::CircleShape startLight(layout::kStartLightRadius);
        startLight.setPosition({layout::kStartLightX + static_cast<float>(light) * layout::kStartLightStepX, layout::kStartLightY});
        startLight.setFillColor(light < 4 ? sf::Color(212, 42, 35) : sf::Color(255, 214, 67));
        mWindow.draw(startLight);
    }

    for (size_t index = 0; index < mGame.races().size(); ++index) {
        const sf::FloatRect cardRect = layout::track_card(index);
        const sf::FloatRect photoRect = layout::track_photo(index);
        drawPanel(cardRect, sf::Color(36, 37, 41), sf::Color(138, 144, 154), 3.0f);

        if (const sf::Texture* texture = trackPreviewTexture(index); texture != nullptr) {
            drawPhotoFit(*texture, photoRect);
        } else {
            drawPhotoPlaceholder(photoRect);
        }

        bitmap_text::draw_text(
            mWindow,
            app_render_helpers::display_track_name(index),
            {cardRect.position.x + layout::kTrackLabelCenterOffsetX, layout::kTrackLabelY},
            3.0f,
            sf::Color(244, 245, 240),
            true);
    }
}

void Application::drawNewGameConfirmation() {
    using layout = app_layout::MainMenuLayout;
    using scene = app_layout::SceneLayout;

    sf::RectangleShape overlay({scene::kWindowWidth, scene::kWindowHeight});
    overlay.setPosition({0.0f, 0.0f});
    overlay.setFillColor(with_alpha(sf::Color(8, 8, 10), 180));
    mWindow.draw(overlay);

    const sf::FloatRect modalRect = layout::confirm_modal_rect();
    drawPanel(modalRect, sf::Color(24, 24, 27), sf::Color(228, 83, 74), 3.0f);

    bitmap_text::draw_text(mWindow, app_text::kConfirmNewGameTitle, {layout::kConfirmTitleCenterX, layout::kConfirmTitleY}, 3.3f, sf::Color(255, 221, 170), true);
    drawWrapped(
        app_text::kConfirmNewGameBody,
        {layout::kConfirmTextX, layout::kConfirmTextY},
        1.7f,
        layout::kConfirmTextWidth,
        sf::Color(232, 235, 240));
}
