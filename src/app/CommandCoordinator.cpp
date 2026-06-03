#include "commands/CommandCoordinator.h"

#include "text/UiText.h"

namespace {
CommandBannerUpdate make_banner(const std::string& pTitle, const std::string& pMessage, const bool pSuccess) {
    return {pTitle, pMessage, pSuccess};
}

CommandRaceFeedbackUpdate make_race_feedback(const std::string& pLabel, const bool pSuccess) {
    return {pLabel, pSuccess};
}

CommandExecutionResult make_navigation_result(const NavigationCommandResult& pNavigation) {
    CommandExecutionResult execution;
    execution.mNavigation = pNavigation;
    return execution;
}

CommandExecutionResult make_banner_result(const PlayerCommandResult& pResult, const bool pShowPendingAlert = true) {
    CommandExecutionResult execution;
    execution.mBanner = make_banner(pResult.mTitle, pResult.mMessage, pResult.mSuccess);
    execution.mShowPendingAlert = pShowPendingAlert;
    return execution;
}

void move_page_backward(size_t& pPage, std::optional<size_t>* pSelectedInventoryIndex = nullptr) {
    if (pPage > 0) {
        --pPage;
        if (pSelectedInventoryIndex != nullptr) {
            *pSelectedInventoryIndex = std::nullopt;
        }
    }
}

void move_page_forward(size_t& pPage, std::optional<size_t>* pSelectedInventoryIndex = nullptr) {
    ++pPage;
    if (pSelectedInventoryIndex != nullptr) {
        *pSelectedInventoryIndex = std::nullopt;
    }
}
}

CommandExecutionResult execute_app_command(
    GameSession& pGame,
    ApplicationState& pUiState,
    const AppCommand pAction) {
    CommandExecutionResult execution;

    switch (pAction) {
        case AppCommand::go_race:
            return make_navigation_result(app_navigation::open_race_hub(pUiState));

        case AppCommand::go_garage:
            return make_navigation_result(app_navigation::open_garage(pUiState));

        case AppCommand::go_museum:
            return make_navigation_result(app_navigation::open_museum(pUiState));

        case AppCommand::exit_app:
            return make_navigation_result(app_navigation::exit_application());

        case AppCommand::new_game:
            return make_navigation_result(app_navigation::begin_new_game_confirmation(pUiState));

        case AppCommand::confirm_new_game: {
            const PlayerCommandResult result = pGame.restart();
            app_navigation::reset_to_main_menu(pUiState);
            execution = make_banner_result(result);
            return execution;
        }

        case AppCommand::cancel_new_game:
            return make_navigation_result(app_navigation::cancel_new_game_confirmation(pUiState));

        case AppCommand::back_main:
            return make_navigation_result(app_navigation::back_to_main_menu(pUiState));

        case AppCommand::start_race: {
            const GameCommandResult result = pGame.startRace(pUiState.mSelectedRace);
            execution.mBanner = make_banner(result.mTitle, result.mMessage, result.mSuccess && result.mHighlightSuccess);
            execution.mRaceFeedback = make_race_feedback(
                result.mSuccess
                    ? (result.mHighlightSuccess ? app_text::kFeedbackCleanStart : app_text::kFeedbackRoughStart)
                    : app_text::kFeedbackEntryFailed,
                result.mSuccess && result.mHighlightSuccess);
            execution.mShowPendingAlert = true;
            return execution;
        }

        case AppCommand::drive_aero:
        case AppCommand::drive_power:
        case AppCommand::drive_wet: {
            const auto modType = mod_type_from_action(pAction);
            if (!modType.has_value()) {
                return execution;
            }

            const RaceDriveResult result = pGame.driveActiveRace(*modType);
            execution.mBanner = make_banner(result.mTitle, result.mMessage, result.mSuccess && result.mFoundLoot);
            execution.mRaceFeedback = make_race_feedback(
                result.mSuccess
                    ? (result.mFoundLoot ? app_text::kFeedbackSectorCleared : app_text::kFeedbackEmptyRun)
                    : app_text::kFeedbackRunFailed,
                result.mSuccess && result.mFoundLoot);
            execution.mShowPendingAlert = true;
            return execution;
        }

        case AppCommand::leave_race:
            pGame.leaveRace();
            execution.mBanner = make_banner(app_text::kBannerRaceCompleteTitle, "", true);
            execution.mShowPendingAlert = true;
            return execution;

        case AppCommand::buy_fuel:
            return make_banner_result(pGame.buyFuel());

        case AppCommand::buy_aero:
        case AppCommand::buy_power:
        case AppCommand::buy_wet: {
            const auto modType = mod_type_from_action(pAction);
            if (!modType.has_value()) {
                return execution;
            }

            return make_banner_result(pGame.repairMod(*modType));
        }

        case AppCommand::garage_prev_page:
            move_page_backward(pUiState.mGarageInventoryPage, &pUiState.mSelectedInventoryIndex);
            return execution;

        case AppCommand::garage_next_page:
            move_page_forward(pUiState.mGarageInventoryPage, &pUiState.mSelectedInventoryIndex);
            return execution;

        case AppCommand::sell_selected:
            if (pUiState.mSelectedInventoryIndex.has_value()) {
                const PlayerCommandResult result = pGame.sellLoot(*pUiState.mSelectedInventoryIndex);
                execution.mBanner = make_banner(result.mTitle, result.mMessage, result.mSuccess);
                execution.mShowPendingAlert = true;
                if (result.mSuccess) {
                    app_state::clear_selected_inventory(pUiState);
                }
            }
            return execution;

        case AppCommand::museum_exhibit_prev_page:
            move_page_backward(pUiState.mMuseumExhibitPage);
            return execution;

        case AppCommand::museum_exhibit_next_page:
            move_page_forward(pUiState.mMuseumExhibitPage);
            return execution;

        case AppCommand::museum_drop_prev_page:
            move_page_backward(pUiState.mMuseumDropPage, &pUiState.mSelectedInventoryIndex);
            return execution;

        case AppCommand::museum_drop_next_page:
            move_page_forward(pUiState.mMuseumDropPage, &pUiState.mSelectedInventoryIndex);
            return execution;

        case AppCommand::donate_selected:
            if (pUiState.mSelectedInventoryIndex.has_value()) {
                const PlayerCommandResult result = pGame.donateLoot(*pUiState.mSelectedInventoryIndex);
                execution.mBanner = make_banner(result.mTitle, result.mMessage, result.mSuccess);
                execution.mShowPendingAlert = true;
                if (result.mSuccess) {
                    app_state::clear_selected_inventory(pUiState);
                }
            }
            return execution;
    }

    return execution;
}
