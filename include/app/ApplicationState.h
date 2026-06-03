#ifndef APPLICATION_STATE_H
#define APPLICATION_STATE_H

#include "commands/Command.h"
#include <SFML/Graphics.hpp>
#include <algorithm>
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
    size_t mGarageInventoryPage = 0;
    size_t mMuseumExhibitPage = 0;
    size_t mMuseumDropPage = 0;
    bool mConfirmingNewGame = false;
    AppBannerState mBanner;
    AppRaceFeedbackState mRaceFeedback;
};

namespace app_state {
[[nodiscard]] inline size_t page_count(const size_t pItemCount, const size_t pPageSize) {
    return std::max<size_t>(1, (pItemCount + pPageSize - 1) / pPageSize);
}

[[nodiscard]] inline size_t page_start(const size_t pPage, const size_t pPageSize) {
    return pPage * pPageSize;
}

[[nodiscard]] inline size_t visible_item_count(const size_t pItemCount, const size_t pPageStart, const size_t pPageSize) {
    return std::min(pPageSize, pItemCount - std::min(pPageStart, pItemCount));
}

inline void clamp_page(size_t& pPage, const size_t pItemCount, const size_t pPageSize) {
    pPage = std::min(pPage, page_count(pItemCount, pPageSize) - 1);
}

[[nodiscard]] inline bool has_selected_inventory(const ApplicationState& pUiState, const size_t pInventorySize) {
    return pUiState.mSelectedInventoryIndex.has_value() && *pUiState.mSelectedInventoryIndex < pInventorySize;
}

inline void clear_selected_inventory(ApplicationState& pUiState) {
    pUiState.mSelectedInventoryIndex.reset();
}
}

#endif // APPLICATION_STATE_H
