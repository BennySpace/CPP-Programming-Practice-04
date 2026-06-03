#ifndef SCREEN_INTERACTIONS_H
#define SCREEN_INTERACTIONS_H

#include "ApplicationState.h"
#include "GameSession.h"
#include <functional>
#include <vector>

enum class ScreenSelectionKind {
    race,
    inventory
};

struct ScreenSelectionHotspot {
    sf::FloatRect mRect;
    ScreenSelectionKind mKind;
    size_t mValue = 0;
    std::string mBannerTitle;
    std::string mBannerMessage;
    bool mBannerSuccess = true;
};

struct ScreenInteractions {
    std::vector<UiButton> mButtons;
    std::vector<ScreenSelectionHotspot> mHotspots;
};

[[nodiscard]] ScreenInteractions build_screen_interactions(const GameSession& pGame, const ApplicationState& pUiState);
using ScreenRectResolver = std::function<sf::FloatRect(const std::string&, const sf::FloatRect&)>;
[[nodiscard]] ScreenInteractions build_screen_interactions(const GameSession& pGame, const ApplicationState& pUiState, const ScreenRectResolver& pResolveRect);

#endif // SCREEN_INTERACTIONS_H
