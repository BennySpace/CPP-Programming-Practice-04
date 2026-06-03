#ifndef MUSEUM_LAYOUT_H
#define MUSEUM_LAYOUT_H

#include "layout/Layout.h"

namespace app_layout {
struct MuseumLayout {
    // Number of cards visible per page in both museum sections.
    static constexpr size_t kVisibleExhibitCardCount = 9;
    static constexpr size_t kVisibleDropCardCount = 6;

    // Main exhibit hall panel and its empty-state copy.
    static constexpr float kHallPanelX = SceneLayout::kOuterMarginX;
    static constexpr float kHallPanelY = SceneLayout::kOuterMarginTop;
    static constexpr float kHallPanelWidth = 820.0f;
    static constexpr float kHallPanelHeight = 654.0f;
    static constexpr float kHallTitleX = kHallPanelX + 28.0f;
    static constexpr float kHallTitleY = kHallPanelY + 24.0f;
    static constexpr float kHallEmptyX = kHallPanelX + 40.0f;
    static constexpr float kHallEmptyY = kHallPanelY + 96.0f;
    static constexpr float kHallEmptyWidth = kHallPanelWidth - 80.0f;

    // Exhibit card grid for donated items.
    static constexpr float kExhibitCardX = kHallPanelX + 32.0f;
    static constexpr float kExhibitCardStartY = kHallPanelY + 72.0f;
    static constexpr float kExhibitCardWidth = 220.0f;
    static constexpr float kExhibitCardHeight = 174.0f;
    static constexpr float kExhibitCardStepX = 252.0f;
    static constexpr float kExhibitCardStepY = 188.0f;

    // Drop-off panel with loot waiting for donation.
    static constexpr float kDropPanelX = kHallPanelX + kHallPanelWidth + SceneLayout::kPanelGap;
    static constexpr float kDropPanelY = kHallPanelY;
    static constexpr float kDropPanelWidth = SceneLayout::kWindowWidth - SceneLayout::kOuterMarginX - kDropPanelX;
    static constexpr float kDropPanelHeight = 350.0f;
    static constexpr float kDropTitleX = kDropPanelX + 28.0f;
    static constexpr float kDropTitleY = kDropPanelY + 24.0f;
    static constexpr float kDropEmptyX = kDropPanelX + 28.0f;
    static constexpr float kDropEmptyY = kDropPanelY + 96.0f;
    static constexpr float kDropEmptyWidth = kDropPanelWidth - 56.0f;

    // Drop-off card grid for candidate donation items.
    static constexpr float kDropCardX = kDropPanelX + 28.0f;
    static constexpr float kDropCardStartY = kDropPanelY + 82.0f;
    static constexpr float kDropCardWidth = 128.0f;
    static constexpr float kDropCardHeight = 120.0f;
    static constexpr float kDropCardStepX = 138.0f;
    static constexpr float kDropCardStepY = 132.0f;

    // Milestones panel with museum reward summary.
    static constexpr float kMilestonePanelX = kDropPanelX;
    static constexpr float kMilestonePanelY = kDropPanelY + kDropPanelHeight + SceneLayout::kSectionGap;
    static constexpr float kMilestonePanelWidth = kDropPanelWidth;
    static constexpr float kMilestonePanelHeight = 128.0f;
    static constexpr float kMilestoneTitleX = kMilestonePanelX + 28.0f;
    static constexpr float kMilestoneTitleY = kMilestonePanelY + 30.0f;
    static constexpr float kRewardsTextX = kMilestonePanelX + 28.0f;
    static constexpr float kRewardsTextY = kMilestonePanelY + 72.0f;

    // Main museum action buttons and paging controls.
    static constexpr float kDonateButtonX = kDropPanelX;
    static constexpr float kDonateButtonY = kMilestonePanelY + kMilestonePanelHeight + SceneLayout::kActionRowGap;
    static constexpr float kDonateButtonWidth = 206.0f;
    static constexpr float kDonateButtonHeight = 56.0f;
    static constexpr float kBackButtonWidth = 206.0f;
    static constexpr float kBackButtonHeight = 56.0f;
    static constexpr float kBackButtonX = kDropPanelX + kDropPanelWidth - kBackButtonWidth;
    static constexpr float kBackButtonY = kDonateButtonY;
    static constexpr float kHallPageIndicatorX = kHallPanelX + kHallPanelWidth - 190.0f;
    static constexpr float kHallPageIndicatorY = kHallPanelY + 22.0f;
    static constexpr float kHallPrevButtonX = kHallPanelX + kHallPanelWidth - 162.0f;
    static constexpr float kHallPrevButtonY = kHallPanelY + 16.0f;
    static constexpr float kHallPrevButtonWidth = 70.0f;
    static constexpr float kHallPrevButtonHeight = 36.0f;
    static constexpr float kHallNextButtonX = kHallPanelX + kHallPanelWidth - 82.0f;
    static constexpr float kHallNextButtonY = kHallPrevButtonY;
    static constexpr float kHallNextButtonWidth = 70.0f;
    static constexpr float kHallNextButtonHeight = 36.0f;
    static constexpr float kDropPageIndicatorX = kDropPanelX + kDropPanelWidth - 190.0f;
    static constexpr float kDropPageIndicatorY = kDropPanelY + 22.0f;
    static constexpr float kDropPrevButtonX = kDropPanelX + kDropPanelWidth - 162.0f;
    static constexpr float kDropPrevButtonY = kDropPanelY + 16.0f;
    static constexpr float kDropPrevButtonWidth = 70.0f;
    static constexpr float kDropPrevButtonHeight = 36.0f;
    static constexpr float kDropNextButtonX = kDropPanelX + kDropPanelWidth - 82.0f;
    static constexpr float kDropNextButtonY = kDropPrevButtonY;
    static constexpr float kDropNextButtonWidth = 70.0f;
    static constexpr float kDropNextButtonHeight = 36.0f;

    // Rectangle helper for the exhibit hall container.
    static sf::FloatRect hall_panel_rect() {
        return make_rect(kHallPanelX, kHallPanelY, kHallPanelWidth, kHallPanelHeight);
    }

    // Rectangle helper for the drop-off container.
    static sf::FloatRect drop_panel_rect() {
        return make_rect(kDropPanelX, kDropPanelY, kDropPanelWidth, kDropPanelHeight);
    }

    // Rectangle helper for the milestones container.
    static sf::FloatRect milestone_panel_rect() {
        return make_rect(kMilestonePanelX, kMilestonePanelY, kMilestonePanelWidth, kMilestonePanelHeight);
    }

    // Anchor rectangle for the first exhibit card.
    static sf::FloatRect first_exhibit_card_rect() {
        return make_rect(kExhibitCardX, kExhibitCardStartY, kExhibitCardWidth, kExhibitCardHeight);
    }

    // Rectangle helper for any donated exhibit card by page-local index.
    static sf::FloatRect exhibit_card(const size_t index) {
        return grid_rect(first_exhibit_card_rect(), index, 3, kExhibitCardStepX, kExhibitCardStepY);
    }

    // Anchor rectangle for the first drop-off card.
    static sf::FloatRect first_drop_card_rect() {
        return make_rect(kDropCardX, kDropCardStartY, kDropCardWidth, kDropCardHeight);
    }

    // Rectangle helper for any drop-off card by page-local index.
    static sf::FloatRect drop_card(const size_t index) {
        return grid_rect(first_drop_card_rect(), index, 3, kDropCardStepX, kDropCardStepY);
    }

    // Rectangle helper for the donate selected item button.
    static sf::FloatRect donate_button_rect() {
        return make_rect(kDonateButtonX, kDonateButtonY, kDonateButtonWidth, kDonateButtonHeight);
    }

    // Rectangle helper for the button that returns to the main menu.
    static sf::FloatRect back_button_rect() {
        return make_rect(kBackButtonX, kBackButtonY, kBackButtonWidth, kBackButtonHeight);
    }

    // Rectangle helper for the previous exhibit page button.
    static sf::FloatRect hall_prev_button_rect() {
        return make_rect(kHallPrevButtonX, kHallPrevButtonY, kHallPrevButtonWidth, kHallPrevButtonHeight);
    }

    // Rectangle helper for the next exhibit page button.
    static sf::FloatRect hall_next_button_rect() {
        return make_rect(kHallNextButtonX, kHallNextButtonY, kHallNextButtonWidth, kHallNextButtonHeight);
    }

    // Rectangle helper for the previous drop-off page button.
    static sf::FloatRect drop_prev_button_rect() {
        return make_rect(kDropPrevButtonX, kDropPrevButtonY, kDropPrevButtonWidth, kDropPrevButtonHeight);
    }

    // Rectangle helper for the next drop-off page button.
    static sf::FloatRect drop_next_button_rect() {
        return make_rect(kDropNextButtonX, kDropNextButtonY, kDropNextButtonWidth, kDropNextButtonHeight);
    }
};
}

#endif // MUSEUM_LAYOUT_H
