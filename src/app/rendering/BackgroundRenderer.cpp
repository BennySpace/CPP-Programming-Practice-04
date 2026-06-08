#include "Application.h"
#include "layout/Layouts.h"
#include "rendering/RenderHelpers.h"
#include "sfml/SfmlUtils.h"
#include "text/UiText.h"
#include "BitmapText.h"

void Application::drawBackground() {
    using scene = app_layout::SceneLayout;

    // Full-screen asphalt backdrop.
    sf::RectangleShape asphalt({scene::kAsphaltWidth, scene::kAsphaltHeight});
    asphalt.setFillColor(sf::Color(28, 29, 31));
    mWindow.draw(asphalt);

    // Repeating grain bands that texture the track background.
    for (int band = 0; band < scene::kGrainCount; ++band) {
        sf::RectangleShape grain({scene::kGrainWidth, scene::kGrainHeight});
        grain.setPosition({0.0f, static_cast<float>(band) * scene::kGrainStepY});
        grain.setFillColor((band % 2 == 0) ? sf::Color(34, 35, 38) : sf::Color(24, 25, 27));
        mWindow.draw(grain);
    }

    // Pit lane strip behind the foreground UI.
    sf::RectangleShape pitLane({scene::kPitLaneWidth, scene::kPitLaneHeight});
    pitLane.setPosition({scene::kPitLaneX, scene::kPitLaneY});
    pitLane.setFillColor(sf::Color(47, 49, 54));
    mWindow.draw(pitLane);

    // Lane dash markers across the pit lane.
    for (int marker = 0; marker < scene::kDashCount; ++marker) {
        sf::RectangleShape dash({scene::kDashWidth, scene::kDashHeight});
        dash.setPosition({scene::kDashX + static_cast<float>(marker) * scene::kDashStepX, scene::kDashY});
        dash.setFillColor(sf::Color(238, 240, 238));
        mWindow.draw(dash);
    }

    // Red-white curb decoration near the bottom edge.
    for (int stripe = 0; stripe < scene::kCurbCount; ++stripe) {
        sf::RectangleShape curb({scene::kCurbWidth, scene::kCurbHeight});
        curb.setPosition({scene::kCurbX + static_cast<float>(stripe) * scene::kCurbStepX, scene::kCurbY});
        curb.setFillColor((stripe % 2 == 0) ? sf::Color(215, 49, 42) : sf::Color(241, 241, 236));
        mWindow.draw(curb);
    }

    // Ambient glows that add depth to the scene background.
    sf::CircleShape glow(scene::kPrimaryGlowRadius);
    glow.setFillColor(with_alpha(sf::Color(210, 36, 31), 35));
    glow.setPosition({scene::kPrimaryGlowX, scene::kPrimaryGlowY});
    mWindow.draw(glow);

    sf::CircleShape secondGlow(scene::kSecondaryGlowRadius);
    secondGlow.setFillColor(with_alpha(sf::Color(255, 214, 49), 22));
    secondGlow.setPosition({scene::kSecondaryGlowX, scene::kSecondaryGlowY});
    mWindow.draw(secondGlow);

    // Brief full-screen flash after a race result.
    if (mUiState.mScreen == ApplicationScreen::race_hub && mUiState.mRaceFeedback.mTimer > 0.0f) {
        const float normalized = mUiState.mRaceFeedback.mTimer / 1.35f;
        sf::RectangleShape flash({scene::kFeedbackFlashWidth, scene::kFeedbackFlashHeight});
        flash.setPosition({scene::kFeedbackFlashX, scene::kFeedbackFlashY});
        flash.setFillColor(with_alpha(
            mUiState.mRaceFeedback.mSuccess ? sf::Color(88, 214, 141) : sf::Color(231, 76, 60),
            static_cast<std::uint8_t>(18.0f + normalized * 42.0f)));
        mWindow.draw(flash);
    }
}

void Application::drawStatusBar() {
    using layout = app_layout::StatusBarLayout;

    // Top status bar container.
    drawPanel(layout::panel_rect(), sf::Color(18, 18, 20), sf::Color(226, 55, 46), 3.0f);

    // App title in the left part of the status bar.
    bitmap_text::draw_text(mWindow, app_text::kAppTitle, {layout::kTitleX, layout::kTitleY}, 4.0f, sf::Color(244, 245, 240));

    const PlayerProfile& currentPlayer = mGame.player();

    // Credits and fuel counters.
    drawTextRightAligned(app_text::format_credits(currentPlayer.money()), {layout::kCounterRightX, layout::kCreditsY}, 3.0f, sf::Color(255, 223, 126));
    drawTextRightAligned(app_text::format_fuel(currentPlayer.fuel()), {layout::kCounterRightX, layout::kFuelY}, 3.0f, sf::Color(139, 223, 255));

    const sf::Color bannerColor = mUiState.mBanner.mSuccess ? sf::Color(168, 255, 180) : sf::Color(255, 170, 170);

    // Banner title and message shown for transient notifications.
    bitmap_text::draw_text(mWindow, mUiState.mBanner.mTitle, {layout::kBannerTitleX, layout::kBannerTitleY}, 3.0f, bannerColor);
    drawWrappedClamped(
        mUiState.mBanner.mMessage,
        {layout::kBannerTextX, layout::kBannerTextY},
        1.55f,
        layout::kBannerTextWidth,
        2,
        sf::Color(232, 234, 238));
}
