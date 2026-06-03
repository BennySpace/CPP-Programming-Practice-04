#ifndef GARAGE_LAYOUT_H
#define GARAGE_LAYOUT_H

#include "layout/Layout.h"

namespace app_layout {
struct GarageLayout {
    // Number of inventory cards visible on one garage page.
    static constexpr size_t kVisibleInventoryCardCount = 12;

    // Unified purchase action band across the top of the garage.
    static constexpr float kBuyButtonY = SceneLayout::kOuterMarginTop;
    static constexpr float kBuyButtonHeight = 58.0f;
    static constexpr float kBuyButtonGap = 20.0f;
    static constexpr float kBuyButtonWidth = (SceneLayout::kWindowWidth - SceneLayout::kOuterMarginX * 2.0f - kBuyButtonGap * 3.0f) / 4.0f;

    // Main inventory panel and its title area.
    static constexpr float kInventoryPanelX = SceneLayout::kOuterMarginX;
    static constexpr float kInventoryPanelY = kBuyButtonY + kBuyButtonHeight + SceneLayout::kPanelGap;
    static constexpr float kInventoryPanelWidth = 852.0f;
    static constexpr float kInventoryPanelHeight = 544.0f;
    static constexpr float kInventoryTitleX = kInventoryPanelX + 32.0f;
    static constexpr float kInventoryTitleY = kInventoryPanelY + 36.0f;

    // Inventory card grid inside the left panel.
    static constexpr float kInventoryCardX = kInventoryPanelX + 30.0f;
    static constexpr float kInventoryCardStartY = kInventoryPanelY + 38.0f;
    static constexpr float kInventoryCardWidth = 174.0f;
    static constexpr float kInventoryCardHeight = 148.0f;
    static constexpr float kInventoryCardStepX = 192.0f;
    static constexpr float kInventoryCardStepY = 166.0f;

    // Upgrade summary panel with fuel and mod labels.
    static constexpr float kMenuPanelX = kInventoryPanelX + kInventoryPanelWidth + SceneLayout::kPanelGap;
    static constexpr float kMenuPanelY = kInventoryPanelY;
    static constexpr float kMenuPanelWidth = SceneLayout::kWindowWidth - SceneLayout::kOuterMarginX - kMenuPanelX;
    static constexpr float kMenuPanelHeight = 206.0f;
    static constexpr float kMenuTitleX = kMenuPanelX + 28.0f;
    static constexpr float kMenuTitleY = kMenuPanelY + 34.0f;
    static constexpr float kMenuLineX = kMenuPanelX + 28.0f;
    static constexpr float kMenuFuelY = kMenuPanelY + 52.0f;
    static constexpr float kMenuAeroY = kMenuPanelY + 88.0f;
    static constexpr float kMenuPowerY = kMenuPanelY + 124.0f;
    static constexpr float kMenuWetY = kMenuPanelY + 160.0f;

    // Selected item details panel on the right side.
    static constexpr float kSelectedPanelX = kMenuPanelX;
    static constexpr float kSelectedPanelY = kMenuPanelY + kMenuPanelHeight + SceneLayout::kSectionGap;
    static constexpr float kSelectedPanelWidth = kMenuPanelWidth;
    static constexpr float kSelectedPanelHeight = kInventoryPanelHeight - kMenuPanelHeight - SceneLayout::kSectionGap;
    static constexpr float kSelectedTitleX = kSelectedPanelX + 28.0f;
    static constexpr float kSelectedTitleY = kSelectedPanelY + 28.0f;
    static constexpr float kSelectedCardWidth = 230.0f;
    static constexpr float kSelectedCardHeight = 210.0f;
    static constexpr float kSelectedCardX = kSelectedPanelX + (kSelectedPanelWidth - kSelectedCardWidth) * 0.5f;
    static constexpr float kSelectedCardY = kSelectedPanelY + 62.0f;
    static constexpr float kSelectedHintX = kSelectedPanelX + 28.0f;
    static constexpr float kSelectedHintY = kSelectedPanelY + 76.0f;
    static constexpr float kSelectedHintWidth = kSelectedPanelWidth - 56.0f;
    static constexpr float kSelectedStatusX = kSelectedPanelX + 28.0f;
    static constexpr float kSelectedStatusY = kSelectedCardY + kSelectedCardHeight + 18.0f;
    static constexpr float kSelectedStatusWidth = kSelectedPanelWidth - 56.0f;

    // Garage action buttons and inventory page controls.
    static constexpr float kBuyFuelButtonX = SceneLayout::kOuterMarginX;
    static constexpr float kBuyFuelButtonY = kBuyButtonY;
    static constexpr float kBuyFuelButtonWidth = kBuyButtonWidth;
    static constexpr float kBuyFuelButtonHeight = kBuyButtonHeight;
    static constexpr float kBuyAeroButtonX = kBuyFuelButtonX + kBuyButtonWidth + kBuyButtonGap;
    static constexpr float kBuyAeroButtonY = kBuyButtonY;
    static constexpr float kBuyAeroButtonWidth = kBuyButtonWidth;
    static constexpr float kBuyAeroButtonHeight = kBuyButtonHeight;
    static constexpr float kBuyPowerButtonX = kBuyAeroButtonX + kBuyButtonWidth + kBuyButtonGap;
    static constexpr float kBuyPowerButtonY = kBuyButtonY;
    static constexpr float kBuyPowerButtonWidth = kBuyButtonWidth;
    static constexpr float kBuyPowerButtonHeight = kBuyButtonHeight;
    static constexpr float kBuyWetButtonX = kBuyPowerButtonX + kBuyButtonWidth + kBuyButtonGap;
    static constexpr float kBuyWetButtonY = kBuyButtonY;
    static constexpr float kBuyWetButtonWidth = kBuyButtonWidth;
    static constexpr float kBuyWetButtonHeight = kBuyButtonHeight;
    static constexpr float kSellButtonX = kMenuPanelX;
    static constexpr float kSellButtonY = kInventoryPanelY + kInventoryPanelHeight + SceneLayout::kActionRowGap;
    static constexpr float kSellButtonWidth = 132.0f;
    static constexpr float kSellButtonHeight = 52.0f;
    static constexpr float kBackButtonWidth = 132.0f;
    static constexpr float kBackButtonHeight = 52.0f;
    static constexpr float kBackButtonX = kSellButtonX + kSellButtonWidth + 16.0f + kBackButtonWidth + 16.0f;
    static constexpr float kBackButtonY = kSellButtonY;
    static constexpr float kPageIndicatorX = kInventoryPanelX + kInventoryPanelWidth - 220.0f;
    static constexpr float kPageIndicatorY = kSellButtonY + 9.0f;
    static constexpr float kPrevPageButtonX = kInventoryPanelX;
    static constexpr float kPrevPageButtonY = kSellButtonY;
    static constexpr float kPrevPageButtonWidth = 130.0f;
    static constexpr float kPrevPageButtonHeight = 52.0f;
    static constexpr float kNextPageButtonX = kPrevPageButtonX + kPrevPageButtonWidth + 14.0f;
    static constexpr float kNextPageButtonY = kSellButtonY;
    static constexpr float kNextPageButtonWidth = 130.0f;
    static constexpr float kNextPageButtonHeight = 52.0f;

    // Rectangle helper for the garage inventory container.
    static sf::FloatRect inventory_panel_rect() {
        return make_rect(kInventoryPanelX, kInventoryPanelY, kInventoryPanelWidth, kInventoryPanelHeight);
    }

    // Rectangle helper for the upgrade summary container.
    static sf::FloatRect menu_panel_rect() {
        return make_rect(kMenuPanelX, kMenuPanelY, kMenuPanelWidth, kMenuPanelHeight);
    }

    // Rectangle helper for the selected item details container.
    static sf::FloatRect selected_panel_rect() {
        return make_rect(kSelectedPanelX, kSelectedPanelY, kSelectedPanelWidth, kSelectedPanelHeight);
    }

    // Anchor rectangle for the first card in the inventory grid.
    static sf::FloatRect first_inventory_card_rect() {
        return make_rect(kInventoryCardX, kInventoryCardStartY, kInventoryCardWidth, kInventoryCardHeight);
    }

    // Rectangle helper for any inventory card by page-local index.
    static sf::FloatRect inventory_card(const size_t index) {
        return grid_rect(first_inventory_card_rect(), index, 4, kInventoryCardStepX, kInventoryCardStepY);
    }

    // Rectangle helper for the enlarged selected item card.
    static sf::FloatRect selected_card_rect() {
        return make_rect(kSelectedCardX, kSelectedCardY, kSelectedCardWidth, kSelectedCardHeight);
    }

    // Rectangle helper for the fuel purchase button.
    static sf::FloatRect buy_fuel_button_rect() {
        return make_rect(kBuyFuelButtonX, kBuyFuelButtonY, kBuyFuelButtonWidth, kBuyFuelButtonHeight);
    }

    // Rectangle helper for the aero purchase button.
    static sf::FloatRect buy_aero_button_rect() {
        return make_rect(kBuyAeroButtonX, kBuyAeroButtonY, kBuyAeroButtonWidth, kBuyAeroButtonHeight);
    }

    // Rectangle helper for the power purchase button.
    static sf::FloatRect buy_power_button_rect() {
        return make_rect(kBuyPowerButtonX, kBuyPowerButtonY, kBuyPowerButtonWidth, kBuyPowerButtonHeight);
    }

    // Rectangle helper for the wet-grip purchase button.
    static sf::FloatRect buy_wet_button_rect() {
        return make_rect(kBuyWetButtonX, kBuyWetButtonY, kBuyWetButtonWidth, kBuyWetButtonHeight);
    }

    // Rectangle helper for the sell selected item button.
    static sf::FloatRect sell_button_rect() {
        return make_rect(kSellButtonX, kSellButtonY, kSellButtonWidth, kSellButtonHeight);
    }

    // Rectangle helper for the button that returns to the main menu.
    static sf::FloatRect back_button_rect() {
        return make_rect(kBackButtonX, kBackButtonY, kBackButtonWidth, kBackButtonHeight);
    }

    // Rectangle helper for the previous inventory page button.
    static sf::FloatRect prev_page_button_rect() {
        return make_rect(kPrevPageButtonX, kPrevPageButtonY, kPrevPageButtonWidth, kPrevPageButtonHeight);
    }

    // Rectangle helper for the next inventory page button.
    static sf::FloatRect next_page_button_rect() {
        return make_rect(kNextPageButtonX, kNextPageButtonY, kNextPageButtonWidth, kNextPageButtonHeight);
    }
};

}

#endif // GARAGE_LAYOUT_H
