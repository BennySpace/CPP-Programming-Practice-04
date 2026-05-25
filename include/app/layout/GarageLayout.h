#ifndef GARAGE_LAYOUT_H
#define GARAGE_LAYOUT_H

#include "layout/Layout.h"

namespace app_layout {
struct GarageLayout {
    static constexpr size_t kVisibleInventoryCardCount = 12;

    static constexpr float kInventoryGroupOffsetX = 0.0f;
    static constexpr float kInventoryGroupOffsetY = 6.0f;
    static constexpr float kActionsGroupOffsetX = 0.0f;
    static constexpr float kActionsGroupOffsetY = 2.0f;
    static constexpr float kSideGroupOffsetX = 0.0f;
    static constexpr float kSideGroupOffsetY = -4.0f;

    static constexpr float kInventoryPanelX = 100.0f + kInventoryGroupOffsetX;
    static constexpr float kInventoryPanelY = 140.0f + kInventoryGroupOffsetY;
    static constexpr float kInventoryPanelWidth = 870.0f;
    static constexpr float kInventoryPanelHeight = 700.0f;
    static constexpr float kInventoryTitleX = 125.0f + kInventoryGroupOffsetX;
    static constexpr float kInventoryTitleY = 250.0f + kInventoryGroupOffsetY;

    static constexpr float kInventoryCardX = 150.0f + kInventoryGroupOffsetX;
    static constexpr float kInventoryCardStartY = 286.0f + kInventoryGroupOffsetY;
    static constexpr float kInventoryCardWidth = 176.0f;
    static constexpr float kInventoryCardHeight = 190.0f;
    static constexpr float kInventoryCardStepX = 198.0f;
    static constexpr float kInventoryCardStepY = 220.0f;

    static constexpr float kMenuPanelX = 1000.0f + kSideGroupOffsetX;
    static constexpr float kMenuPanelY = 140.0f + kSideGroupOffsetY;
    static constexpr float kMenuPanelWidth = 340.0f;
    static constexpr float kMenuPanelHeight = 220.0f;
    static constexpr float kMenuTitleX = 1030.0f + kSideGroupOffsetX;
    static constexpr float kMenuTitleY = 368.0f + kSideGroupOffsetY;
    static constexpr float kMenuLineX = 1030.0f + kSideGroupOffsetX;
    static constexpr float kMenuFuelY = 382.0f + kSideGroupOffsetY;
    static constexpr float kMenuAeroY = 416.0f + kSideGroupOffsetY;
    static constexpr float kMenuPowerY = 450.0f + kSideGroupOffsetY;
    static constexpr float kMenuWetY = 484.0f + kSideGroupOffsetY;

    static constexpr float kSelectedPanelX = 1000.0f + kSideGroupOffsetX;
    static constexpr float kSelectedPanelY = 374.0f + kSideGroupOffsetY;
    static constexpr float kSelectedPanelWidth = 340.0f;
    static constexpr float kSelectedPanelHeight = 340.0f;
    static constexpr float kSelectedTitleX = 1030.0f + kSideGroupOffsetX;
    static constexpr float kSelectedTitleY = 410.0f + kSideGroupOffsetY;
    static constexpr float kSelectedCardX = 1065.0f + kSideGroupOffsetX;
    static constexpr float kSelectedCardY = 452.0f + kSideGroupOffsetY;
    static constexpr float kSelectedCardWidth = 210.0f;
    static constexpr float kSelectedCardHeight = 210.0f;
    static constexpr float kSelectedHintX = 1030.0f + kSideGroupOffsetX;
    static constexpr float kSelectedHintY = 458.0f + kSideGroupOffsetY;
    static constexpr float kSelectedHintWidth = 280.0f;
    static constexpr float kSelectedStatusX = 1030.0f + kSideGroupOffsetX;
    static constexpr float kSelectedStatusY = 680.0f + kSideGroupOffsetY;
    static constexpr float kSelectedStatusWidth = 280.0f;

    static constexpr float kBuyFuelButtonX = 175.0f + kActionsGroupOffsetX;
    static constexpr float kBuyFuelButtonY = 160.0f + kActionsGroupOffsetY;
    static constexpr float kBuyFuelButtonWidth = 180.0f;
    static constexpr float kBuyFuelButtonHeight = 58.0f;
    static constexpr float kBuyAeroButtonX = 375.0f + kActionsGroupOffsetX;
    static constexpr float kBuyAeroButtonY = 160.0f + kActionsGroupOffsetY;
    static constexpr float kBuyAeroButtonWidth = 160.0f;
    static constexpr float kBuyAeroButtonHeight = 58.0f;
    static constexpr float kBuyPowerButtonX = 555.0f + kActionsGroupOffsetX;
    static constexpr float kBuyPowerButtonY = 160.0f + kActionsGroupOffsetY;
    static constexpr float kBuyPowerButtonWidth = 160.0f;
    static constexpr float kBuyPowerButtonHeight = 58.0f;
    static constexpr float kBuyWetButtonX = 735.0f + kActionsGroupOffsetX;
    static constexpr float kBuyWetButtonY = 160.0f + kActionsGroupOffsetY;
    static constexpr float kBuyWetButtonWidth = 160.0f;
    static constexpr float kBuyWetButtonHeight = 58.0f;
    static constexpr float kSellButtonX = 1030.0f + kSideGroupOffsetX;
    static constexpr float kSellButtonY = 160.0f + kSideGroupOffsetY;
    static constexpr float kSellButtonWidth = 260.0f;
    static constexpr float kSellButtonHeight = 58.0f;
    static constexpr float kRepairButtonX = 1030.0f + kSideGroupOffsetX;
    static constexpr float kRepairButtonY = 235.0f + kSideGroupOffsetY;
    static constexpr float kRepairButtonWidth = 260.0f;
    static constexpr float kRepairButtonHeight = 58.0f;
    static constexpr float kBackButtonX = 1030.0f + kSideGroupOffsetX;
    static constexpr float kBackButtonY = 782.0f + kSideGroupOffsetY;
    static constexpr float kBackButtonWidth = 260.0f;
    static constexpr float kBackButtonHeight = 58.0f;

    static sf::FloatRect inventory_panel_rect() {
        return make_rect(kInventoryPanelX, kInventoryPanelY, kInventoryPanelWidth, kInventoryPanelHeight);
    }

    static sf::FloatRect menu_panel_rect() {
        return make_rect(kMenuPanelX, kMenuPanelY, kMenuPanelWidth, kMenuPanelHeight);
    }

    static sf::FloatRect selected_panel_rect() {
        return make_rect(kSelectedPanelX, kSelectedPanelY, kSelectedPanelWidth, kSelectedPanelHeight);
    }

    static sf::FloatRect inventory_card(const size_t index) {
        const float column = static_cast<float>(index % 4);
        const float row = static_cast<float>(index / 4);
        return make_rect(kInventoryCardX + column * kInventoryCardStepX, kInventoryCardStartY + row * kInventoryCardStepY, kInventoryCardWidth, kInventoryCardHeight);
    }

    static sf::FloatRect selected_card_rect() {
        return make_rect(kSelectedCardX, kSelectedCardY, kSelectedCardWidth, kSelectedCardHeight);
    }

    static sf::FloatRect buy_fuel_button_rect() {
        return make_rect(kBuyFuelButtonX, kBuyFuelButtonY, kBuyFuelButtonWidth, kBuyFuelButtonHeight);
    }

    static sf::FloatRect buy_aero_button_rect() {
        return make_rect(kBuyAeroButtonX, kBuyAeroButtonY, kBuyAeroButtonWidth, kBuyAeroButtonHeight);
    }

    static sf::FloatRect buy_power_button_rect() {
        return make_rect(kBuyPowerButtonX, kBuyPowerButtonY, kBuyPowerButtonWidth, kBuyPowerButtonHeight);
    }

    static sf::FloatRect buy_wet_button_rect() {
        return make_rect(kBuyWetButtonX, kBuyWetButtonY, kBuyWetButtonWidth, kBuyWetButtonHeight);
    }

    static sf::FloatRect sell_button_rect() {
        return make_rect(kSellButtonX, kSellButtonY, kSellButtonWidth, kSellButtonHeight);
    }

    static sf::FloatRect repair_button_rect() {
        return make_rect(kRepairButtonX, kRepairButtonY, kRepairButtonWidth, kRepairButtonHeight);
    }

    static sf::FloatRect back_button_rect() {
        return make_rect(kBackButtonX, kBackButtonY, kBackButtonWidth, kBackButtonHeight);
    }
};

}

#endif // GARAGE_LAYOUT_H
