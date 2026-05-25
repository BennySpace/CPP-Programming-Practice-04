#ifndef APPLICATION_STATE_H
#define APPLICATION_STATE_H

#include "commands/Command.h"
#include <SFML/Graphics.hpp>
#include <cstddef>
#include <optional>
#include <string>

enum class ApplicationScreen {
    main_menu,
    race_hub,
    garage,
    museum
};

struct UiButton {
    AppCommand mAction;
    std::string mLabel;
    sf::FloatRect mRect;
    sf::Color mFill;
    sf::Color mAccent;
    bool mEnabled = true;
};

struct AppBannerState {
    std::string mTitle;
    std::string mMessage;
    bool mSuccess = true;
    float mTimer = 0.0f;
};

struct AppRaceFeedbackState {
    float mTimer = 0.0f;
    bool mSuccess = false;
    std::string mLabel;
};

struct ApplicationState {
    ApplicationScreen mScreen = ApplicationScreen::main_menu;
    size_t mSelectedRace = 0;
    std::optional<size_t> mSelectedInventoryIndex;
    bool mConfirmingNewGame = false;
    AppBannerState mBanner;
    AppRaceFeedbackState mRaceFeedback;
};

#endif // APPLICATION_STATE_H
