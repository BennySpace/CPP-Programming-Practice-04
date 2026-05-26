#include "screens/ScreenNavigation.h"
#include "text/UiText.h"

namespace {
NavigationCommandResult make_banner_result(const std::string& pTitle, const bool pSuccess) {
    NavigationCommandResult result;
    result.mShowBanner = true;
    result.mBannerTitle = pTitle;
    result.mBannerSuccess = pSuccess;
    return result;
}

NavigationCommandResult open_screen(
    ApplicationState& pUiState,
    const ApplicationScreen pScreen,
    const std::string& pBannerTitle,
    const bool pResetSelection) {
    pUiState.mScreen = pScreen;
    if (pResetSelection) {
        pUiState.mSelectedInventoryIndex.reset();
    }

    return make_banner_result(pBannerTitle, true);
}

NavigationCommandResult back_to_main_menu(
    ApplicationState& pUiState,
    const std::string& pBannerTitle,
    const bool pLeaveRace) {
    pUiState.mScreen = ApplicationScreen::main_menu;
    pUiState.mSelectedInventoryIndex.reset();

    NavigationCommandResult result = make_banner_result(pBannerTitle, true);
    result.mLeaveRace = pLeaveRace;
    return result;
}
}

namespace app_navigation {
NavigationCommandResult exit_application() {
    NavigationCommandResult result;
    result.mCloseWindow = true;
    return result;
}

NavigationCommandResult handle_escape(ApplicationState& pUiState) {
    if (pUiState.mScreen == ApplicationScreen::main_menu) {
        return exit_application();
    }

    return back_to_main_menu(pUiState, app_text::kBannerReturnedTitle, true);
}

NavigationCommandResult open_race_hub(ApplicationState& pUiState) {
    return open_screen(pUiState, ApplicationScreen::race_hub, app_text::kBannerRaceDeckTitle, false);
}

NavigationCommandResult open_garage(ApplicationState& pUiState) {
    return open_screen(pUiState, ApplicationScreen::garage, app_text::kBannerGarageTitle, true);
}

NavigationCommandResult open_museum(ApplicationState& pUiState) {
    return open_screen(pUiState, ApplicationScreen::museum, app_text::kBannerMuseumHallTitle, true);
}

NavigationCommandResult back_to_main_menu(ApplicationState& pUiState) {
    return ::back_to_main_menu(pUiState, app_text::kBannerHqOnlineTitle, true);
}

NavigationCommandResult begin_new_game_confirmation(ApplicationState& pUiState) {
    pUiState.mConfirmingNewGame = true;
    return make_banner_result(app_text::kBannerConfirmResetTitle, false);
}

NavigationCommandResult cancel_new_game_confirmation(ApplicationState& pUiState) {
    pUiState.mConfirmingNewGame = false;
    return make_banner_result(app_text::kBannerResetCanceledTitle, true);
}

void reset_to_main_menu(ApplicationState& pUiState) {
    pUiState.mConfirmingNewGame = false;
    pUiState.mScreen = ApplicationScreen::main_menu;
    pUiState.mSelectedInventoryIndex.reset();
}
}
