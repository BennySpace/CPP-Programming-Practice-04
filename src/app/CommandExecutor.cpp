#include "Application.h"
#include "text/UiText.h"
#include "GameBalance.h"

void Application::executeCommand(const AppCommand action) {
    switch (action) {
        case AppCommand::go_race:
            openScreen(ApplicationScreen::race_hub, app_text::kBannerRaceDeckTitle, false);
            return;

        case AppCommand::go_garage:
            openScreen(ApplicationScreen::garage, app_text::kBannerGarageTitle, true);
            return;

        case AppCommand::go_museum:
            openScreen(ApplicationScreen::museum, app_text::kBannerMuseumHallTitle, true);
            return;

        case AppCommand::exit_app:
            closeApplication();
            return;

        case AppCommand::new_game:
            mUiState.mConfirmingNewGame = true;
            showBanner(app_text::kBannerConfirmResetTitle, false);
            return;

        case AppCommand::confirm_new_game: {
            const PlayerCommandResult result = mGame.restart();
            mUiState.mConfirmingNewGame = false;
            mUiState.mScreen = ApplicationScreen::main_menu;
            mUiState.mSelectedInventoryIndex.reset();
            showBanner(result.mTitle, result.mMessage, result.mSuccess);
            return;
        }

        case AppCommand::cancel_new_game:
            mUiState.mConfirmingNewGame = false;
            showBanner(app_text::kBannerResetCanceledTitle, true);
            return;

        case AppCommand::back_main:
            returnToMainMenu(app_text::kBannerHqOnlineTitle);
            return;

        case AppCommand::start_race: {
            const GameCommandResult result = mGame.startRace(mUiState.mSelectedRace);
            showBanner(result.mTitle, result.mMessage, result.mSuccess && result.mHighlightSuccess);
            showRaceFeedback(
                result.mSuccess
                    ? (result.mHighlightSuccess ? app_text::kFeedbackCleanStart : app_text::kFeedbackRoughStart)
                    : app_text::kFeedbackEntryFailed,
                result.mSuccess && result.mHighlightSuccess);
            return;
        }

        case AppCommand::drive_aero:
        case AppCommand::drive_power:
        case AppCommand::drive_wet: {
            const auto modType = mod_type_from_action(action);
            if (!modType.has_value()) {
                return;
            }

            const RaceDriveResult result = mGame.driveActiveRace(*modType);
            showBanner(result.mTitle, result.mMessage, result.mSuccess && result.mFoundLoot);
            showRaceFeedback(
                result.mSuccess
                    ? (result.mFoundLoot ? app_text::kFeedbackSectorCleared : app_text::kFeedbackEmptyRun)
                    : app_text::kFeedbackRunFailed,
                result.mSuccess && result.mFoundLoot);
            return;
        }

        case AppCommand::leave_race:
            mGame.leaveRace();
            showBanner(app_text::kBannerRaceCompleteTitle, true);
            return;

        case AppCommand::buy_fuel: {
            const PlayerCommandResult result = mGame.buyFuel();
            showBanner(result.mTitle, result.mMessage, result.mSuccess);
            return;
        }

        case AppCommand::buy_aero:
        case AppCommand::buy_power:
        case AppCommand::buy_wet: {
            const auto modType = mod_type_from_action(action);
            if (!modType.has_value()) {
                return;
            }

            const int modCost = action == AppCommand::buy_aero
                ? game_balance::kAeroModCost
                : (action == AppCommand::buy_power ? game_balance::kHighPowerModCost : game_balance::kWetGripModCost);
            const PlayerCommandResult result = mGame.buyMod(*modType, modCost);
            showBanner(result.mTitle, result.mMessage, result.mSuccess);
            return;
        }

        case AppCommand::sell_selected:
            if (mUiState.mSelectedInventoryIndex.has_value()) {
                const PlayerCommandResult result = mGame.sellLoot(*mUiState.mSelectedInventoryIndex);
                showBanner(result.mTitle, result.mMessage, result.mSuccess);
                if (result.mSuccess) {
                    mUiState.mSelectedInventoryIndex.reset();
                }
            }
            return;

        case AppCommand::repair_selected:
            if (mUiState.mSelectedInventoryIndex.has_value()) {
                const PlayerCommandResult result = mGame.repairMod(*mUiState.mSelectedInventoryIndex);
                showBanner(result.mTitle, result.mMessage, result.mSuccess);
                if (result.mSuccess) {
                    mUiState.mSelectedInventoryIndex.reset();
                }
            }
            return;

        case AppCommand::donate_selected:
            if (mUiState.mSelectedInventoryIndex.has_value()) {
                const PlayerCommandResult result = mGame.donateLoot(*mUiState.mSelectedInventoryIndex);
                showBanner(result.mTitle, result.mMessage, result.mSuccess);
                if (result.mSuccess) {
                    mUiState.mSelectedInventoryIndex.reset();
                }
            }
            return;
    }
}
