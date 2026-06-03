#include "Application.h"
#include "commands/CommandCoordinator.h"

void Application::applyCommandExecutionResult(const CommandExecutionResult& pResult) {
    if (pResult.mNavigation.has_value()) {
        applyNavigation(*pResult.mNavigation);
    }

    if (pResult.mBanner.has_value()) {
        showBanner(pResult.mBanner->mTitle, pResult.mBanner->mMessage, pResult.mBanner->mSuccess);
    }

    if (pResult.mRaceFeedback.has_value()) {
        showRaceFeedback(pResult.mRaceFeedback->mLabel, pResult.mRaceFeedback->mSuccess);
    }

    if (pResult.mShowPendingAlert && !pResult.mNavigation.has_value()) {
        showPendingSessionAlert();
    }
}

void Application::executeCommand(const AppCommand action) {
    applyCommandExecutionResult(execute_app_command(mGame, mUiState, action));
}
