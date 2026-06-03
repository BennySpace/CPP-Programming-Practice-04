#ifndef COMMAND_COORDINATOR_H
#define COMMAND_COORDINATOR_H

#include "ApplicationState.h"
#include "GameSession.h"
#include "screens/ScreenNavigation.h"
#include <optional>
#include <string>

struct CommandBannerUpdate {
    std::string mTitle;
    std::string mMessage;
    bool mSuccess = true;
};

struct CommandRaceFeedbackUpdate {
    std::string mLabel;
    bool mSuccess = false;
};

struct CommandExecutionResult {
    std::optional<NavigationCommandResult> mNavigation;
    std::optional<CommandBannerUpdate> mBanner;
    std::optional<CommandRaceFeedbackUpdate> mRaceFeedback;
    bool mShowPendingAlert = false;
};

[[nodiscard]] CommandExecutionResult execute_app_command(
    GameSession& pGame,
    ApplicationState& pUiState,
    AppCommand pAction);

#endif // COMMAND_COORDINATOR_H
