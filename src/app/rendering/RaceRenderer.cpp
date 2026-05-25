#include "Application.h"
#include "layout/Layouts.h"
#include "rendering/RenderHelpers.h"
#include "sfml/SfmlUtils.h"
#include "text/UiText.h"
#include "BitmapText.h"

void Application::drawRaceHub() {
    using layout = app_layout::RaceLayout;

    drawPanel(layout::board_panel_rect(), sf::Color(18, 24, 30), sf::Color(84, 124, 164), 3.0f);

    for (size_t index = 0; index < mGame.races().size(); ++index) {
        const auto& currentRace = mGame.races()[index];
        const bool selected = index == mUiState.mSelectedRace;
        const sf::Color accent = selected ? sf::Color(255, 212, 82) : sf::Color(229, 231, 228);
        const sf::FloatRect raceCardRect = layout::race_card(index);

        drawPanel(raceCardRect, sf::Color(28, 33, 40), accent, 3.0f);

        bitmap_text::draw_text(mWindow, app_render_helpers::display_track_name(index), {layout::kRaceCardTextX, raceCardRect.position.y + layout::kRaceCardTitleOffsetY}, 2.8f, sf::Color(243, 245, 249));
        drawWrapped(currentRace->get_circuit_type(), {layout::kRaceCardTextX, raceCardRect.position.y + layout::kRaceCardTypeOffsetY}, 1.7f, 320.0f, sf::Color(178, 184, 194));
        bitmap_text::draw_text(mWindow, app_text::format_entry_fee(currentRace->get_fee()), {layout::kRaceCardTextX, raceCardRect.position.y + layout::kRaceCardFeeOffsetY}, 2.0f, sf::Color(239, 205, 144));
    }

    drawPanel(layout::control_panel_rect(), sf::Color(20, 26, 34), sf::Color(124, 144, 168), 3.0f);

    const sf::FloatRect mapRect = layout::track_map_rect();
    if (const sf::Texture* texture = trackMapTexture(mUiState.mSelectedRace); texture != nullptr) {
        drawPhotoFit(*texture, mapRect);
    } else {
        drawPhotoPlaceholder(mapRect, 3.0f);
    }

    bitmap_text::draw_text(mWindow, app_text::kRaceHubAeroWing, {layout::kModTextX, layout::kAeroLabelY}, 1.55f, sf::Color(167, 218, 194));
    bitmap_text::draw_text(mWindow, modStatusText(ModType::aero_wing), {layout::kModTextX, layout::kAeroValueY}, 1.8f, modStatusColor(ModType::aero_wing));
    bitmap_text::draw_text(mWindow, app_text::kRaceHubHighPower, {layout::kModTextX, layout::kPowerLabelY}, 1.55f, sf::Color(227, 188, 182));
    bitmap_text::draw_text(mWindow, modStatusText(ModType::high_power), {layout::kModTextX, layout::kPowerValueY}, 1.8f, modStatusColor(ModType::high_power));
    bitmap_text::draw_text(mWindow, app_text::kRaceHubWetGrip, {layout::kModTextX, layout::kWetLabelY}, 1.55f, sf::Color(183, 203, 233));
    bitmap_text::draw_text(mWindow, modStatusText(ModType::wet_grip), {layout::kModTextX, layout::kWetValueY}, 1.8f, modStatusColor(ModType::wet_grip));

    if (mUiState.mRaceFeedback.mTimer > 0.0f) {
        const sf::Color accent = mUiState.mRaceFeedback.mSuccess ? sf::Color(101, 223, 137) : sf::Color(240, 97, 97);
        const sf::FloatRect resultRect = layout::result_rect();
        drawPanel(resultRect, with_alpha(accent, 40), accent, 3.0f);
        bitmap_text::draw_text(mWindow, mUiState.mRaceFeedback.mLabel, {layout::kResultCenterX, layout::kResultTextY}, 2.3f, sf::Color(245, 247, 250), true);
    }

    drawPanel(layout::radio_panel_rect(), sf::Color(20, 26, 32), sf::Color(118, 138, 164), 3.0f);
    const Race* focusedRace = mGame.activeRace();
    if (focusedRace == nullptr && mUiState.mSelectedRace < mGame.races().size()) {
        focusedRace = mGame.races()[mUiState.mSelectedRace].get();
    }

    if (focusedRace != nullptr) {
        drawWrapped(focusedRace->get_name(), {layout::kRadioTitleX, layout::kRadioNameY}, 1.8f, layout::kRadioBodyWidth, sf::Color(244, 211, 144));
        drawWrapped(focusedRace->get_intro_text(), {layout::kRadioTitleX, layout::kRadioBodyY}, 1.35f, layout::kRadioBodyWidth, sf::Color(188, 196, 210));
        drawWrapped(focusedRace->get_strategy_text(), {layout::kRadioTitleX, layout::kRadioBodyY + 54.0f}, 1.3f, layout::kRadioBodyWidth, sf::Color(170, 208, 219));
        drawWrapped(focusedRace->get_best_mod_text(), {layout::kRadioTitleX, layout::kRadioBodyY + 104.0f}, 1.4f, layout::kRadioBodyWidth, sf::Color(232, 202, 142));
    } else {
        drawWrapped(app_text::kRaceHubRadioFallback, {layout::kRadioTitleX, layout::kRadioFallbackY}, 1.7f, layout::kRadioBodyWidth, sf::Color(188, 196, 210));
    }
}
