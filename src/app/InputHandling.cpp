#include "Application.h"
#include "layout/Layouts.h"
#include "sfml/SfmlUtils.h"
#include "text/UiText.h"
#include <algorithm>

void Application::handleMouseClick(const sf::Vector2f mousePosition) {
    if (mUiState.mConfirmingNewGame) {
        for (const auto& currentButton : mButtons) {
            if (currentButton.mEnabled && rect_contains(currentButton.mRect, mousePosition)) {
                executeCommand(currentButton.mAction);
                return;
            }
        }
        return;
    }

    if (mUiState.mScreen == ApplicationScreen::race_hub) {
        for (size_t index = 0; index < mGame.races().size(); ++index) {
            const sf::FloatRect raceRect = app_layout::RaceLayout::race_card(index);
            if (rect_contains(raceRect, mousePosition)) {
                mUiState.mSelectedRace = index;
                showBanner(app_text::kBannerRaceSelectedTitle, mGame.races()[index]->get_name(), true);
                return;
            }
        }
    }

    if (mUiState.mScreen == ApplicationScreen::garage) {
        const auto& inventory = mGame.player().inventory();
        const size_t visibleCount = std::min(inventory.size(), app_layout::GarageLayout::kVisibleInventoryCardCount);
        for (size_t index = 0; index < visibleCount; ++index) {
            const sf::FloatRect itemRect = app_layout::GarageLayout::inventory_card(index);
            if (rect_contains(itemRect, mousePosition)) {
                mUiState.mSelectedInventoryIndex = index;
                showBanner(app_text::kBannerItemSelectedTitle, inventory[index].mName, true);
                return;
            }
        }
    }

    if (mUiState.mScreen == ApplicationScreen::museum) {
        const auto lootIndices = mGame.player().lootIndices();
        const size_t visibleCount = std::min(lootIndices.size(), app_layout::MuseumLayout::kVisibleDropCardCount);
        for (size_t displayIndex = 0; displayIndex < visibleCount; ++displayIndex) {
            const sf::FloatRect itemRect = app_layout::MuseumLayout::drop_card(displayIndex);
            if (rect_contains(itemRect, mousePosition)) {
                mUiState.mSelectedInventoryIndex = lootIndices[displayIndex];
                showBanner(app_text::kBannerDonationSlotTitle, mGame.player().inventory()[lootIndices[displayIndex]].mName, true);
                return;
            }
        }
    }

    for (const auto& currentButton : mButtons) {
        if (currentButton.mEnabled && rect_contains(currentButton.mRect, mousePosition)) {
            executeCommand(currentButton.mAction);
            return;
        }
    }
}
