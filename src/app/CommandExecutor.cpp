#include "Application.h"
#include "text/UiText.h"
#include "GameBalance.h"

void Application::executeCommand(const AppCommand action) {
    switch (action) {
        case AppCommand::go_race:
            applyNavigation(app_navigation::open_race_hub(mUiState));
            return;

        case AppCommand::go_garage:
            applyNavigation(app_navigation::open_garage(mUiState));
            return;

        case AppCommand::go_museum:
            applyNavigation(app_navigation::open_museum(mUiState));
            return;

        case AppCommand::exit_app:
            applyNavigation(app_navigation::exit_application());
            return;

        case AppCommand::new_game:
            applyNavigation(app_navigation::begin_new_game_confirmation(mUiState));
            return;

        case AppCommand::confirm_new_game: {
            const PlayerCommandResult result = mGame.restart();
            app_navigation::reset_to_main_menu(mUiState);
            showBanner(result.mTitle, result.mMessage, result.mSuccess);
            showPendingSessionAlert();
            return;
        }

        case AppCommand::cancel_new_game:
            applyNavigation(app_navigation::cancel_new_game_confirmation(mUiState));
            return;

        case AppCommand::back_main:
            applyNavigation(app_navigation::back_to_main_menu(mUiState));
            return;

        case AppCommand::start_race: {
            const GameCommandResult result = mGame.startRace(mUiState.mSelectedRace);
            showBanner(result.mTitle, result.mMessage, result.mSuccess && result.mHighlightSuccess);
            showPendingSessionAlert();
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
            showPendingSessionAlert();
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
            showPendingSessionAlert();
            return;

        case AppCommand::buy_fuel: {
            const PlayerCommandResult result = mGame.buyFuel();
            showBanner(result.mTitle, result.mMessage, result.mSuccess);
            showPendingSessionAlert();
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
            showPendingSessionAlert();
            return;
        }

        case AppCommand::garage_prev_page:
            if (mUiState.mGarageInventoryPage > 0) {
                --mUiState.mGarageInventoryPage;
                mUiState.mSelectedInventoryIndex.reset();
            }
            return;

        case AppCommand::garage_next_page:
            ++mUiState.mGarageInventoryPage;
            mUiState.mSelectedInventoryIndex.reset();
            return;

        case AppCommand::sell_selected:
            if (mUiState.mSelectedInventoryIndex.has_value()) {
                const PlayerCommandResult result = mGame.sellLoot(*mUiState.mSelectedInventoryIndex);
                showBanner(result.mTitle, result.mMessage, result.mSuccess);
                showPendingSessionAlert();
                if (result.mSuccess) {
                    mUiState.mSelectedInventoryIndex.reset();
                }
            }
            return;

        case AppCommand::repair_selected:
            if (mUiState.mSelectedInventoryIndex.has_value()) {
                const PlayerCommandResult result = mGame.repairMod(*mUiState.mSelectedInventoryIndex);
                showBanner(result.mTitle, result.mMessage, result.mSuccess);
                showPendingSessionAlert();
                if (result.mSuccess) {
                    mUiState.mSelectedInventoryIndex.reset();
                }
            }
            return;

        case AppCommand::museum_exhibit_prev_page:
            if (mUiState.mMuseumExhibitPage > 0) {
                --mUiState.mMuseumExhibitPage;
            }
            return;

        case AppCommand::museum_exhibit_next_page:
            ++mUiState.mMuseumExhibitPage;
            return;

        case AppCommand::museum_drop_prev_page:
            if (mUiState.mMuseumDropPage > 0) {
                --mUiState.mMuseumDropPage;
                mUiState.mSelectedInventoryIndex.reset();
            }
            return;

        case AppCommand::museum_drop_next_page:
            ++mUiState.mMuseumDropPage;
            mUiState.mSelectedInventoryIndex.reset();
            return;

        case AppCommand::donate_selected:
            if (mUiState.mSelectedInventoryIndex.has_value()) {
                const PlayerCommandResult result = mGame.donateLoot(*mUiState.mSelectedInventoryIndex);
                showBanner(result.mTitle, result.mMessage, result.mSuccess);
                showPendingSessionAlert();
                if (result.mSuccess) {
                    mUiState.mSelectedInventoryIndex.reset();
                }
            }
            return;
    }
}
