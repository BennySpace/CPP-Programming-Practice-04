#include "Application.h"
#include "layout/Layouts.h"
#include "rendering/RenderHelpers.h"
#include "sfml/SfmlUtils.h"
#include "text/UiText.h"
#include "BitmapText.h"

void Application::drawRaceHub() {
    using layout = app_layout::RaceLayout;
    const size_t focusedRaceIndex = mGame.activeRaceIndex().value_or(mUiState.mSelectedRace);

    // Race hub layout anchors for panels, labels and text areas.
    const sf::FloatRect boardPanelRect = debugRectOverride("race.board_panel", layout::board_panel_rect());
    const sf::FloatRect controlPanelRect = debugRectOverride("race.control_panel", layout::control_panel_rect());
    const sf::FloatRect trackMapRect = debugRectOverride("race.track_map", layout::track_map_rect());
    const sf::FloatRect resultRect = debugRectOverride("race.result_panel", layout::result_rect());
    const sf::FloatRect radioPanelRect = debugRectOverride("race.radio_panel", layout::radio_panel_rect());
    const sf::FloatRect aeroLabelRect = debugRectOverride("race.aero_label_text", {{layout::kModTextX, layout::kAeroLabelY}, {180.0f, 20.0f}});
    const sf::FloatRect aeroValueRect = debugRectOverride("race.aero_value_text", {{layout::kModTextX, layout::kAeroValueY}, {180.0f, 20.0f}});
    const sf::FloatRect powerLabelRect = debugRectOverride("race.power_label_text", {{layout::kModTextX, layout::kPowerLabelY}, {180.0f, 20.0f}});
    const sf::FloatRect powerValueRect = debugRectOverride("race.power_value_text", {{layout::kModTextX, layout::kPowerValueY}, {180.0f, 20.0f}});
    const sf::FloatRect wetLabelRect = debugRectOverride("race.wet_label_text", {{layout::kModTextX, layout::kWetLabelY}, {180.0f, 20.0f}});
    const sf::FloatRect wetValueRect = debugRectOverride("race.wet_value_text", {{layout::kModTextX, layout::kWetValueY}, {180.0f, 20.0f}});
    const sf::FloatRect resultTextRect = debugRectOverride("race.result_text", {{layout::kResultCenterX, layout::kResultTextY}, {220.0f, 24.0f}});
    const sf::FloatRect radioTitleRect = debugRectOverride("race.radio_title_text", {{layout::kRadioTitleX, layout::kRadioTitleY}, {220.0f, 24.0f}});
    const sf::FloatRect radioNameRect = debugRectOverride("race.radio_name_text", {{layout::kRadioTitleX, layout::kRadioNameY}, {layout::kRadioBodyWidth, 36.0f}});
    const sf::FloatRect radioIntroRect = debugRectOverride("race.radio_intro_text", {{layout::kRadioTitleX, layout::kRadioBodyY}, {layout::kRadioBodyWidth, 42.0f}});
    const sf::FloatRect radioStrategyRect = debugRectOverride("race.radio_strategy_text", {{layout::kRadioTitleX, layout::kRadioBodyY + 50.0f}, {layout::kRadioBodyWidth, 42.0f}});
    const sf::FloatRect radioBestRect = debugRectOverride("race.radio_best_text", {{layout::kRadioTitleX, layout::kRadioBodyY + 100.0f}, {layout::kRadioBodyWidth, 42.0f}});
    const sf::FloatRect radioFallbackRect = debugRectOverride("race.radio_fallback_text", {{layout::kRadioTitleX, layout::kRadioFallbackY}, {layout::kRadioBodyWidth, 42.0f}});

    // Race selection board with available event cards.
    drawPanel(boardPanelRect, sf::Color(18, 24, 30), sf::Color(84, 124, 164), 3.0f);

    for (size_t index = 0; index < mGame.races().size(); ++index) {
        const auto& currentRace = mGame.races()[index];
        const bool selected = index == focusedRaceIndex;
        const sf::Color accent = selected ? sf::Color(255, 212, 82) : sf::Color(229, 231, 228);
        const sf::FloatRect raceCardRect = debugRectOverride("race.card_" + std::to_string(index), layout::race_card(index));

        drawPanel(raceCardRect, sf::Color(28, 33, 40), accent, 3.0f);

        bitmap_text::draw_text(mWindow, app_render_helpers::display_track_name(index), {layout::kRaceCardTextX, raceCardRect.position.y + layout::kRaceCardTitleOffsetY}, 2.8f, sf::Color(243, 245, 249));
        drawWrapped(
            currentRace->get_circuit_type(),
            {layout::kRaceCardTextX, raceCardRect.position.y + layout::kRaceCardTypeOffsetY},
            1.7f,
            raceCardRect.size.x - 32.0f,
            sf::Color(178, 184, 194));
        bitmap_text::draw_text(mWindow, app_text::format_entry_fee(currentRace->get_fee()), {layout::kRaceCardTextX, raceCardRect.position.y + layout::kRaceCardFeeOffsetY}, 2.0f, sf::Color(239, 205, 144));
    }

    // Control panel with track map and installed mod statuses.
    drawPanel(controlPanelRect, sf::Color(20, 26, 34), sf::Color(124, 144, 168), 3.0f);

    if (const sf::Texture* texture = trackMapTexture(focusedRaceIndex); texture != nullptr) {
        drawPhotoFit(*texture, trackMapRect);
    } else {
        drawPhotoPlaceholder(trackMapRect, 3.0f);
    }

    bitmap_text::draw_text(mWindow, app_text::kRaceHubAeroWing, aeroLabelRect.position, 1.55f, sf::Color(167, 218, 194));
    bitmap_text::draw_text(mWindow, modStatusText(ModType::aero_wing), aeroValueRect.position, 1.8f, modStatusColor(ModType::aero_wing));
    bitmap_text::draw_text(mWindow, app_text::kRaceHubHighPower, powerLabelRect.position, 1.55f, sf::Color(227, 188, 182));
    bitmap_text::draw_text(mWindow, modStatusText(ModType::high_power), powerValueRect.position, 1.8f, modStatusColor(ModType::high_power));
    bitmap_text::draw_text(mWindow, app_text::kRaceHubWetGrip, wetLabelRect.position, 1.55f, sf::Color(183, 203, 233));
    bitmap_text::draw_text(mWindow, modStatusText(ModType::wet_grip), wetValueRect.position, 1.8f, modStatusColor(ModType::wet_grip));

    // Temporary race result banner after an action resolves.
    if (mUiState.mRaceFeedback.mTimer > 0.0f) {
        const sf::Color accent = mUiState.mRaceFeedback.mSuccess ? sf::Color(101, 223, 137) : sf::Color(240, 97, 97);
        drawPanel(resultRect, with_alpha(accent, 40), accent, 3.0f);
        bitmap_text::draw_text(mWindow, mUiState.mRaceFeedback.mLabel, resultTextRect.position, 2.3f, sf::Color(245, 247, 250), true);
    }

    // Radio briefing panel with flavor text for the focused race.
    drawPanel(radioPanelRect, sf::Color(20, 26, 32), sf::Color(118, 138, 164), 3.0f);
    bitmap_text::draw_text(mWindow, app_text::kRaceHubPitRadioTitle, radioTitleRect.position, 1.7f, sf::Color(198, 210, 228));
    const Race* focusedRace = mGame.activeRace();
    if (focusedRace == nullptr && focusedRaceIndex < mGame.races().size()) {
        focusedRace = mGame.races()[focusedRaceIndex].get();
    }

    if (focusedRace != nullptr) {
        drawWrapped(focusedRace->get_name(), radioNameRect.position, 1.8f, radioNameRect.size.x, sf::Color(244, 211, 144));
        drawWrapped(focusedRace->get_intro_text(), radioIntroRect.position, 1.35f, radioIntroRect.size.x, sf::Color(188, 196, 210));
        drawWrapped(focusedRace->get_strategy_text(), radioStrategyRect.position, 1.3f, radioStrategyRect.size.x, sf::Color(170, 208, 219));
        drawWrapped(focusedRace->get_best_mod_text(), radioBestRect.position, 1.4f, radioBestRect.size.x, sf::Color(232, 202, 142));
    } else {
        drawWrapped(app_text::kRaceHubRadioFallback, radioFallbackRect.position, 1.7f, radioFallbackRect.size.x, sf::Color(188, 196, 210));
    }
}
