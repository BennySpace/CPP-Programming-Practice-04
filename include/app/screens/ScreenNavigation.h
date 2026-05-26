#ifndef SCREEN_NAVIGATION_H
#define SCREEN_NAVIGATION_H

#include "ApplicationState.h"
#include <string>

struct NavigationCommandResult {
    bool mCloseWindow = false;
    bool mLeaveRace = false;
    bool mShowBanner = false;
    std::string mBannerTitle;
    std::string mBannerMessage;
    bool mBannerSuccess = true;
};

namespace app_navigation {
[[nodiscard]] NavigationCommandResult exit_application();
[[nodiscard]] NavigationCommandResult handle_escape(ApplicationState& pUiState);
[[nodiscard]] NavigationCommandResult open_race_hub(ApplicationState& pUiState);
[[nodiscard]] NavigationCommandResult open_garage(ApplicationState& pUiState);
[[nodiscard]] NavigationCommandResult open_museum(ApplicationState& pUiState);
[[nodiscard]] NavigationCommandResult back_to_main_menu(ApplicationState& pUiState);
[[nodiscard]] NavigationCommandResult begin_new_game_confirmation(ApplicationState& pUiState);
[[nodiscard]] NavigationCommandResult cancel_new_game_confirmation(ApplicationState& pUiState);
void reset_to_main_menu(ApplicationState& pUiState);
}

#endif // SCREEN_NAVIGATION_H
