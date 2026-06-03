#ifndef NDEBUG

#include "debug/DebugLayoutRegistry.h"

#include "layout/Layouts.h"
#include <optional>

namespace {
void add_debug_rect(
    std::vector<DebugEditableRect>& pRects,
    const std::string& pName,
    const sf::FloatRect& pFallbackRect,
    const DebugLayoutEditor& pEditor,
    const bool pIsButton = false,
    const std::optional<std::string>& pParentName = std::nullopt) {
    pRects.push_back({pName, pEditor.rectOverride(pName).value_or(pFallbackRect), pIsButton, pParentName});
}
}

std::vector<DebugEditableRect> build_debug_layout_rects(
    const GameSession& pGame,
    const ApplicationState& pUiState,
    const DebugLayoutEditor& pEditor) {
    std::vector<DebugEditableRect> rects;

    switch (pUiState.mScreen) {
        case ApplicationScreen::main_menu:
            add_debug_rect(rects, "main.panel", app_layout::MainMenuLayout::panel_rect(), pEditor);
            add_debug_rect(rects, "main.title_text", {{app_layout::MainMenuLayout::kTitleX, app_layout::MainMenuLayout::kTitleY}, {260.0f, 32.0f}}, pEditor, false, "main.panel");
            add_debug_rect(rects, "main.track_card_0", app_layout::MainMenuLayout::track_card(0), pEditor, false, "main.panel");
            add_debug_rect(rects, "main.track_card_1", app_layout::MainMenuLayout::track_card(1), pEditor, false, "main.panel");
            add_debug_rect(rects, "main.track_card_2", app_layout::MainMenuLayout::track_card(2), pEditor, false, "main.panel");
            add_debug_rect(rects, "main.track_photo_0", app_layout::MainMenuLayout::track_photo(0), pEditor, false, "main.panel");
            add_debug_rect(rects, "main.track_photo_1", app_layout::MainMenuLayout::track_photo(1), pEditor, false, "main.panel");
            add_debug_rect(rects, "main.track_photo_2", app_layout::MainMenuLayout::track_photo(2), pEditor, false, "main.panel");
            add_debug_rect(rects, "main.track_label_0", {{app_layout::MainMenuLayout::kTrackCardX + app_layout::MainMenuLayout::kTrackLabelCenterOffsetX, app_layout::MainMenuLayout::kTrackLabelY}, {220.0f, 28.0f}}, pEditor, false, "main.panel");
            add_debug_rect(rects, "main.track_label_1", {{app_layout::MainMenuLayout::kTrackCardX + app_layout::MainMenuLayout::kTrackCardStepX + app_layout::MainMenuLayout::kTrackLabelCenterOffsetX, app_layout::MainMenuLayout::kTrackLabelY}, {220.0f, 28.0f}}, pEditor, false, "main.panel");
            add_debug_rect(rects, "main.track_label_2", {{app_layout::MainMenuLayout::kTrackCardX + app_layout::MainMenuLayout::kTrackCardStepX * 2.0f + app_layout::MainMenuLayout::kTrackLabelCenterOffsetX, app_layout::MainMenuLayout::kTrackLabelY}, {220.0f, 28.0f}}, pEditor, false, "main.panel");
            add_debug_rect(rects, "main.go_race_button", app_layout::MainMenuLayout::go_race_button_rect(), pEditor, true);
            add_debug_rect(rects, "main.go_garage_button", app_layout::MainMenuLayout::go_garage_button_rect(), pEditor, true);
            add_debug_rect(rects, "main.go_museum_button", app_layout::MainMenuLayout::go_museum_button_rect(), pEditor, true);
            add_debug_rect(rects, "main.new_game_button", app_layout::MainMenuLayout::new_game_button_rect(), pEditor, true);
            add_debug_rect(rects, "main.exit_button", app_layout::MainMenuLayout::exit_button_rect(), pEditor, true);
            if (pUiState.mConfirmingNewGame) {
                add_debug_rect(rects, "main.confirm_modal", app_layout::MainMenuLayout::confirm_modal_rect(), pEditor);
                add_debug_rect(rects, "main.confirm_title_text", {{app_layout::MainMenuLayout::kConfirmTitleCenterX, app_layout::MainMenuLayout::kConfirmTitleY}, {260.0f, 32.0f}}, pEditor, false, "main.confirm_modal");
                add_debug_rect(rects, "main.confirm_body_text", {{app_layout::MainMenuLayout::kConfirmTextX, app_layout::MainMenuLayout::kConfirmTextY}, {app_layout::MainMenuLayout::kConfirmTextWidth, 80.0f}}, pEditor, false, "main.confirm_modal");
                add_debug_rect(rects, "main.confirm_yes_button", app_layout::MainMenuLayout::confirm_yes_button_rect(), pEditor, true);
                add_debug_rect(rects, "main.confirm_cancel_button", app_layout::MainMenuLayout::confirm_cancel_button_rect(), pEditor, true);
            }
            break;

        case ApplicationScreen::garage:
            add_debug_rect(rects, "garage.inventory_panel", app_layout::GarageLayout::inventory_panel_rect(), pEditor);
            add_debug_rect(rects, "garage.menu_panel", app_layout::GarageLayout::menu_panel_rect(), pEditor);
            add_debug_rect(rects, "garage.selected_panel", app_layout::GarageLayout::selected_panel_rect(), pEditor);
            add_debug_rect(rects, "garage.menu_fuel_text", {{app_layout::GarageLayout::kMenuLineX, app_layout::GarageLayout::kMenuFuelY}, {180.0f, 24.0f}}, pEditor, false, "garage.menu_panel");
            add_debug_rect(rects, "garage.menu_aero_text", {{app_layout::GarageLayout::kMenuLineX, app_layout::GarageLayout::kMenuAeroY}, {180.0f, 24.0f}}, pEditor, false, "garage.menu_panel");
            add_debug_rect(rects, "garage.menu_power_text", {{app_layout::GarageLayout::kMenuLineX, app_layout::GarageLayout::kMenuPowerY}, {180.0f, 24.0f}}, pEditor, false, "garage.menu_panel");
            add_debug_rect(rects, "garage.menu_wet_text", {{app_layout::GarageLayout::kMenuLineX, app_layout::GarageLayout::kMenuWetY}, {180.0f, 24.0f}}, pEditor, false, "garage.menu_panel");
            add_debug_rect(rects, "garage.selected_title_text", {{app_layout::GarageLayout::kSelectedTitleX, app_layout::GarageLayout::kSelectedTitleY}, {220.0f, 28.0f}}, pEditor, false, "garage.selected_panel");
            add_debug_rect(rects, "garage.selected_hint_text", {{app_layout::GarageLayout::kSelectedHintX, app_layout::GarageLayout::kSelectedHintY}, {app_layout::GarageLayout::kSelectedHintWidth, 90.0f}}, pEditor, false, "garage.selected_panel");
            add_debug_rect(rects, "garage.selected_status_text", {{app_layout::GarageLayout::kSelectedStatusX, app_layout::GarageLayout::kSelectedStatusY}, {app_layout::GarageLayout::kSelectedStatusWidth, 90.0f}}, pEditor, false, "garage.selected_panel");
            for (size_t index = 0; index < app_layout::GarageLayout::kVisibleInventoryCardCount; ++index) {
                add_debug_rect(rects, "garage.inventory_card_" + std::to_string(index), app_layout::GarageLayout::inventory_card(index), pEditor, false, "garage.inventory_panel");
            }
            add_debug_rect(rects, "garage.selected_card", app_layout::GarageLayout::selected_card_rect(), pEditor, false, "garage.selected_panel");
            add_debug_rect(rects, "garage.buy_fuel_button", app_layout::GarageLayout::buy_fuel_button_rect(), pEditor, true);
            add_debug_rect(rects, "garage.buy_aero_button", app_layout::GarageLayout::buy_aero_button_rect(), pEditor, true);
            add_debug_rect(rects, "garage.buy_power_button", app_layout::GarageLayout::buy_power_button_rect(), pEditor, true);
            add_debug_rect(rects, "garage.buy_wet_button", app_layout::GarageLayout::buy_wet_button_rect(), pEditor, true);
            add_debug_rect(rects, "garage.sell_button", app_layout::GarageLayout::sell_button_rect(), pEditor, true);
            add_debug_rect(rects, "garage.prev_page_button", app_layout::GarageLayout::prev_page_button_rect(), pEditor, true);
            add_debug_rect(rects, "garage.next_page_button", app_layout::GarageLayout::next_page_button_rect(), pEditor, true);
            add_debug_rect(rects, "garage.back_button", app_layout::GarageLayout::back_button_rect(), pEditor, true);
            break;

        case ApplicationScreen::museum:
            add_debug_rect(rects, "museum.hall_panel", app_layout::MuseumLayout::hall_panel_rect(), pEditor);
            add_debug_rect(rects, "museum.drop_panel", app_layout::MuseumLayout::drop_panel_rect(), pEditor);
            add_debug_rect(rects, "museum.milestone_panel", app_layout::MuseumLayout::milestone_panel_rect(), pEditor);
            add_debug_rect(rects, "museum.hall_title_text", {{app_layout::MuseumLayout::kHallTitleX, app_layout::MuseumLayout::kHallTitleY}, {260.0f, 28.0f}}, pEditor, false, "museum.hall_panel");
            add_debug_rect(rects, "museum.hall_empty_text", {{app_layout::MuseumLayout::kHallEmptyX, app_layout::MuseumLayout::kHallEmptyY}, {app_layout::MuseumLayout::kHallEmptyWidth, 90.0f}}, pEditor, false, "museum.hall_panel");
            add_debug_rect(rects, "museum.drop_title_text", {{app_layout::MuseumLayout::kDropTitleX, app_layout::MuseumLayout::kDropTitleY}, {240.0f, 28.0f}}, pEditor, false, "museum.drop_panel");
            add_debug_rect(rects, "museum.drop_empty_text", {{app_layout::MuseumLayout::kDropEmptyX, app_layout::MuseumLayout::kDropEmptyY}, {app_layout::MuseumLayout::kDropEmptyWidth, 90.0f}}, pEditor, false, "museum.drop_panel");
            add_debug_rect(rects, "museum.milestone_title_text", {{app_layout::MuseumLayout::kMilestoneTitleX, app_layout::MuseumLayout::kMilestoneTitleY}, {240.0f, 28.0f}}, pEditor, false, "museum.milestone_panel");
            add_debug_rect(rects, "museum.rewards_text", {{app_layout::MuseumLayout::kRewardsTextX, app_layout::MuseumLayout::kRewardsTextY}, {260.0f, 24.0f}}, pEditor, false, "museum.milestone_panel");
            for (size_t index = 0; index < app_layout::MuseumLayout::kVisibleExhibitCardCount; ++index) {
                add_debug_rect(rects, "museum.exhibit_card_" + std::to_string(index), app_layout::MuseumLayout::exhibit_card(index), pEditor, false, "museum.hall_panel");
            }
            for (size_t index = 0; index < app_layout::MuseumLayout::kVisibleDropCardCount; ++index) {
                add_debug_rect(rects, "museum.drop_card_" + std::to_string(index), app_layout::MuseumLayout::drop_card(index), pEditor, false, "museum.drop_panel");
            }
            add_debug_rect(rects, "museum.hall_prev_button", app_layout::MuseumLayout::hall_prev_button_rect(), pEditor, true);
            add_debug_rect(rects, "museum.hall_next_button", app_layout::MuseumLayout::hall_next_button_rect(), pEditor, true);
            add_debug_rect(rects, "museum.drop_prev_button", app_layout::MuseumLayout::drop_prev_button_rect(), pEditor, true);
            add_debug_rect(rects, "museum.drop_next_button", app_layout::MuseumLayout::drop_next_button_rect(), pEditor, true);
            add_debug_rect(rects, "museum.donate_button", app_layout::MuseumLayout::donate_button_rect(), pEditor, true);
            add_debug_rect(rects, "museum.back_button", app_layout::MuseumLayout::back_button_rect(), pEditor, true);
            break;

        case ApplicationScreen::race_hub:
            add_debug_rect(rects, "race.board_panel", app_layout::RaceLayout::board_panel_rect(), pEditor);
            add_debug_rect(rects, "race.control_panel", app_layout::RaceLayout::control_panel_rect(), pEditor);
            for (size_t index = 0; index < pGame.races().size(); ++index) {
                add_debug_rect(rects, "race.card_" + std::to_string(index), app_layout::RaceLayout::race_card(index), pEditor, false, "race.board_panel");
            }
            add_debug_rect(rects, "race.track_map", app_layout::RaceLayout::track_map_rect(), pEditor, false, "race.control_panel");
            add_debug_rect(rects, "race.result_panel", app_layout::RaceLayout::result_rect(), pEditor, false, "race.control_panel");
            add_debug_rect(rects, "race.radio_panel", app_layout::RaceLayout::radio_panel_rect(), pEditor);
            add_debug_rect(rects, "race.radio_title_text", {{app_layout::RaceLayout::kRadioTitleX, app_layout::RaceLayout::kRadioTitleY}, {220.0f, 24.0f}}, pEditor, false, "race.radio_panel");
            add_debug_rect(rects, "race.aero_label_text", {{app_layout::RaceLayout::kModTextX, app_layout::RaceLayout::kAeroLabelY}, {180.0f, 20.0f}}, pEditor, false, "race.control_panel");
            add_debug_rect(rects, "race.aero_value_text", {{app_layout::RaceLayout::kModTextX, app_layout::RaceLayout::kAeroValueY}, {180.0f, 20.0f}}, pEditor, false, "race.control_panel");
            add_debug_rect(rects, "race.power_label_text", {{app_layout::RaceLayout::kModTextX, app_layout::RaceLayout::kPowerLabelY}, {180.0f, 20.0f}}, pEditor, false, "race.control_panel");
            add_debug_rect(rects, "race.power_value_text", {{app_layout::RaceLayout::kModTextX, app_layout::RaceLayout::kPowerValueY}, {180.0f, 20.0f}}, pEditor, false, "race.control_panel");
            add_debug_rect(rects, "race.wet_label_text", {{app_layout::RaceLayout::kModTextX, app_layout::RaceLayout::kWetLabelY}, {180.0f, 20.0f}}, pEditor, false, "race.control_panel");
            add_debug_rect(rects, "race.wet_value_text", {{app_layout::RaceLayout::kModTextX, app_layout::RaceLayout::kWetValueY}, {180.0f, 20.0f}}, pEditor, false, "race.control_panel");
            add_debug_rect(rects, "race.result_text", {{app_layout::RaceLayout::kResultCenterX, app_layout::RaceLayout::kResultTextY}, {220.0f, 24.0f}}, pEditor, false, "race.result_panel");
            add_debug_rect(rects, "race.radio_name_text", {{app_layout::RaceLayout::kRadioTitleX, app_layout::RaceLayout::kRadioNameY}, {app_layout::RaceLayout::kRadioBodyWidth, 36.0f}}, pEditor, false, "race.radio_panel");
            add_debug_rect(rects, "race.radio_intro_text", {{app_layout::RaceLayout::kRadioTitleX, app_layout::RaceLayout::kRadioBodyY}, {app_layout::RaceLayout::kRadioBodyWidth, 42.0f}}, pEditor, false, "race.radio_panel");
            add_debug_rect(rects, "race.radio_strategy_text", {{app_layout::RaceLayout::kRadioTitleX, app_layout::RaceLayout::kRadioBodyY + 50.0f}, {app_layout::RaceLayout::kRadioBodyWidth, 42.0f}}, pEditor, false, "race.radio_panel");
            add_debug_rect(rects, "race.radio_best_text", {{app_layout::RaceLayout::kRadioTitleX, app_layout::RaceLayout::kRadioBodyY + 100.0f}, {app_layout::RaceLayout::kRadioBodyWidth, 42.0f}}, pEditor, false, "race.radio_panel");
            add_debug_rect(rects, "race.radio_fallback_text", {{app_layout::RaceLayout::kRadioTitleX, app_layout::RaceLayout::kRadioFallbackY}, {app_layout::RaceLayout::kRadioBodyWidth, 42.0f}}, pEditor, false, "race.radio_panel");
            add_debug_rect(rects, "race.start_button", app_layout::RaceLayout::start_race_button_rect(), pEditor, true);
            add_debug_rect(rects, "race.drive_aero_button", app_layout::RaceLayout::drive_aero_button_rect(), pEditor, true);
            add_debug_rect(rects, "race.drive_power_button", app_layout::RaceLayout::drive_power_button_rect(), pEditor, true);
            add_debug_rect(rects, "race.drive_wet_button", app_layout::RaceLayout::drive_wet_button_rect(), pEditor, true);
            add_debug_rect(rects, "race.leave_button", app_layout::RaceLayout::leave_race_button_rect(), pEditor, true);
            add_debug_rect(rects, "race.back_button", app_layout::RaceLayout::back_button_rect(), pEditor, true);
            break;
    }

    return rects;
}

#endif
