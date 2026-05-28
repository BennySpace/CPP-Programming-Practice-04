#ifndef MUSEUM_LAYOUT_H
#define MUSEUM_LAYOUT_H

#include "layout/Layout.h"

namespace app_layout {
struct MuseumLayout {
    static constexpr size_t kVisibleExhibitCardCount = 9;
    static constexpr size_t kVisibleDropCardCount = 12;

    static constexpr float kHallGroupOffsetX = 0.0f;
    static constexpr float kHallGroupOffsetY = 4.0f;
    static constexpr float kSideGroupOffsetX = 0.0f;
    static constexpr float kSideGroupOffsetY = -2.0f;
    static constexpr float kButtonGroupOffsetX = 0.0f;
    static constexpr float kButtonGroupOffsetY = -6.0f;

    static constexpr float kHallPanelX = 90.0f + kHallGroupOffsetX;
    static constexpr float kHallPanelY = 140.0f + kHallGroupOffsetY;
    static constexpr float kHallPanelWidth = 780.0f;
    static constexpr float kHallPanelHeight = 700.0f;
    static constexpr float kHallTitleX = 120.0f + kHallGroupOffsetX;
    static constexpr float kHallTitleY = 170.0f + kHallGroupOffsetY;
    static constexpr float kHallEmptyX = 130.0f + kHallGroupOffsetX;
    static constexpr float kHallEmptyY = 240.0f + kHallGroupOffsetY;
    static constexpr float kHallEmptyWidth = 650.0f;

    static constexpr float kExhibitCardX = 120.0f + kHallGroupOffsetX;
    static constexpr float kExhibitCardStartY = 230.0f + kHallGroupOffsetY;
    static constexpr float kExhibitCardWidth = 200.0f;
    static constexpr float kExhibitCardHeight = 185.0f;
    static constexpr float kExhibitCardStepX = 235.0f;
    static constexpr float kExhibitCardStepY = 215.0f;

    static constexpr float kDropPanelX = 900.0f + kSideGroupOffsetX;
    static constexpr float kDropPanelY = 140.0f + kSideGroupOffsetY;
    static constexpr float kDropPanelWidth = 450.0f;
    static constexpr float kDropPanelHeight = 380.0f;
    static constexpr float kDropTitleX = 930.0f + kSideGroupOffsetX;
    static constexpr float kDropTitleY = 170.0f + kSideGroupOffsetY;
    static constexpr float kDropEmptyX = 930.0f + kSideGroupOffsetX;
    static constexpr float kDropEmptyY = 240.0f + kSideGroupOffsetY;
    static constexpr float kDropEmptyWidth = 350.0f;

    static constexpr float kDropCardX = 922.0f + kSideGroupOffsetX;
    static constexpr float kDropCardStartY = 220.0f + kSideGroupOffsetY;
    static constexpr float kDropCardWidth = 82.0f;
    static constexpr float kDropCardHeight = 104.0f;
    static constexpr float kDropCardStepX = 98.0f;
    static constexpr float kDropCardStepY = 108.0f;

    static constexpr float kMilestonePanelX = 900.0f + kSideGroupOffsetX;
    static constexpr float kMilestonePanelY = 540.0f + kSideGroupOffsetY;
    static constexpr float kMilestonePanelWidth = 450.0f;
    static constexpr float kMilestonePanelHeight = 120.0f;
    static constexpr float kMilestoneTitleX = 930.0f + kSideGroupOffsetX;
    static constexpr float kMilestoneTitleY = 576.0f + kSideGroupOffsetY;
    static constexpr float kRewardsTextX = 930.0f + kSideGroupOffsetX;
    static constexpr float kRewardsTextY = 620.0f + kSideGroupOffsetY;

    static constexpr float kDonateButtonX = 1000.0f + kButtonGroupOffsetX;
    static constexpr float kDonateButtonY = 712.0f + kButtonGroupOffsetY;
    static constexpr float kDonateButtonWidth = 250.0f;
    static constexpr float kDonateButtonHeight = 55.0f;
    static constexpr float kBackButtonX = 1000.0f + kButtonGroupOffsetX;
    static constexpr float kBackButtonY = 785.0f + kButtonGroupOffsetY;
    static constexpr float kBackButtonWidth = 250.0f;
    static constexpr float kBackButtonHeight = 55.0f;
    static constexpr float kHallPageIndicatorX = 590.0f + kHallGroupOffsetX;
    static constexpr float kHallPageIndicatorY = 176.0f + kHallGroupOffsetY;
    static constexpr float kHallPrevButtonX = 650.0f + kHallGroupOffsetX;
    static constexpr float kHallPrevButtonY = 166.0f + kHallGroupOffsetY;
    static constexpr float kHallPrevButtonWidth = 88.0f;
    static constexpr float kHallPrevButtonHeight = 34.0f;
    static constexpr float kHallNextButtonX = 748.0f + kHallGroupOffsetX;
    static constexpr float kHallNextButtonY = 166.0f + kHallGroupOffsetY;
    static constexpr float kHallNextButtonWidth = 88.0f;
    static constexpr float kHallNextButtonHeight = 34.0f;
    static constexpr float kDropPageIndicatorX = 1090.0f + kSideGroupOffsetX;
    static constexpr float kDropPageIndicatorY = 176.0f + kSideGroupOffsetY;
    static constexpr float kDropPrevButtonX = 1166.0f + kSideGroupOffsetX;
    static constexpr float kDropPrevButtonY = 166.0f + kSideGroupOffsetY;
    static constexpr float kDropPrevButtonWidth = 72.0f;
    static constexpr float kDropPrevButtonHeight = 34.0f;
    static constexpr float kDropNextButtonX = 1244.0f + kSideGroupOffsetX;
    static constexpr float kDropNextButtonY = 166.0f + kSideGroupOffsetY;
    static constexpr float kDropNextButtonWidth = 72.0f;
    static constexpr float kDropNextButtonHeight = 34.0f;

    static sf::FloatRect hall_panel_rect() {
        return make_rect(kHallPanelX, kHallPanelY, kHallPanelWidth, kHallPanelHeight);
    }

    static sf::FloatRect drop_panel_rect() {
        return make_rect(kDropPanelX, kDropPanelY, kDropPanelWidth, kDropPanelHeight);
    }

    static sf::FloatRect milestone_panel_rect() {
        return make_rect(kMilestonePanelX, kMilestonePanelY, kMilestonePanelWidth, kMilestonePanelHeight);
    }

    static sf::FloatRect first_exhibit_card_rect() {
        return make_rect(kExhibitCardX, kExhibitCardStartY, kExhibitCardWidth, kExhibitCardHeight);
    }

    static sf::FloatRect exhibit_card(const size_t index) {
        return grid_rect(first_exhibit_card_rect(), index, 3, kExhibitCardStepX, kExhibitCardStepY);
    }

    static sf::FloatRect first_drop_card_rect() {
        return make_rect(kDropCardX, kDropCardStartY, kDropCardWidth, kDropCardHeight);
    }

    static sf::FloatRect drop_card(const size_t index) {
        return grid_rect(first_drop_card_rect(), index, 4, kDropCardStepX, kDropCardStepY);
    }

    static sf::FloatRect donate_button_rect() {
        return make_rect(kDonateButtonX, kDonateButtonY, kDonateButtonWidth, kDonateButtonHeight);
    }

    static sf::FloatRect back_button_rect() {
        return make_rect(kBackButtonX, kBackButtonY, kBackButtonWidth, kBackButtonHeight);
    }

    static sf::FloatRect hall_prev_button_rect() {
        return make_rect(kHallPrevButtonX, kHallPrevButtonY, kHallPrevButtonWidth, kHallPrevButtonHeight);
    }

    static sf::FloatRect hall_next_button_rect() {
        return make_rect(kHallNextButtonX, kHallNextButtonY, kHallNextButtonWidth, kHallNextButtonHeight);
    }

    static sf::FloatRect drop_prev_button_rect() {
        return make_rect(kDropPrevButtonX, kDropPrevButtonY, kDropPrevButtonWidth, kDropPrevButtonHeight);
    }

    static sf::FloatRect drop_next_button_rect() {
        return make_rect(kDropNextButtonX, kDropNextButtonY, kDropNextButtonWidth, kDropNextButtonHeight);
    }
};
}

#endif // MUSEUM_LAYOUT_H
