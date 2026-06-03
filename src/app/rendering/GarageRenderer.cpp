#include "Application.h"
#include "layout/Layouts.h"
#include "rendering/RenderHelpers.h"
#include "sfml/SfmlUtils.h"
#include "text/UiText.h"
#include "BitmapText.h"
#include <algorithm>

void Application::drawGarage() {
    using layout = app_layout::GarageLayout;
    const PlayerProfile& player = mGame.player();

    // Garage screen layout anchors for the main panels and text blocks.
    const sf::FloatRect inventoryPanelRect = debugRectOverride("garage.inventory_panel", layout::inventory_panel_rect());
    const sf::FloatRect menuPanelRect = debugRectOverride("garage.menu_panel", layout::menu_panel_rect());
    const sf::FloatRect selectedPanelRect = debugRectOverride("garage.selected_panel", layout::selected_panel_rect());
    const sf::FloatRect menuFuelRect = debugRectOverride("garage.menu_fuel_text", {{layout::kMenuLineX, layout::kMenuFuelY}, {180.0f, 24.0f}});
    const sf::FloatRect menuAeroRect = debugRectOverride("garage.menu_aero_text", {{layout::kMenuLineX, layout::kMenuAeroY}, {180.0f, 24.0f}});
    const sf::FloatRect menuPowerRect = debugRectOverride("garage.menu_power_text", {{layout::kMenuLineX, layout::kMenuPowerY}, {180.0f, 24.0f}});
    const sf::FloatRect menuWetRect = debugRectOverride("garage.menu_wet_text", {{layout::kMenuLineX, layout::kMenuWetY}, {180.0f, 24.0f}});
    const sf::FloatRect selectedTitleRect = debugRectOverride("garage.selected_title_text", {{layout::kSelectedTitleX, layout::kSelectedTitleY}, {220.0f, 28.0f}});
    const sf::FloatRect selectedHintRect = debugRectOverride("garage.selected_hint_text", {{layout::kSelectedHintX, layout::kSelectedHintY}, {layout::kSelectedHintWidth, 90.0f}});
    const sf::FloatRect selectedStatusRect = debugRectOverride("garage.selected_status_text", {{layout::kSelectedStatusX, layout::kSelectedStatusY}, {layout::kSelectedStatusWidth, 90.0f}});
    // Inventory panel with paged item cards.
    drawPanel(inventoryPanelRect, sf::Color(25, 22, 19), sf::Color(178, 98, 58), 3.0f);

    const auto& inventory = player.inventory();
    const auto lootIndices = player.lootIndices();
    const size_t pageStart = app_state::page_start(mUiState.mGarageInventoryPage, layout::kVisibleInventoryCardCount);
    const size_t visibleInventoryCount = app_state::visible_item_count(lootIndices.size(), pageStart, layout::kVisibleInventoryCardCount);
    for (size_t displayIndex = 0; displayIndex < visibleInventoryCount; ++displayIndex) {
        const size_t inventoryIndex = lootIndices[pageStart + displayIndex];
        drawItemCard(
            inventory[inventoryIndex],
            debugRectOverride("garage.inventory_card_" + std::to_string(displayIndex), layout::inventory_card(displayIndex)),
            app_state::has_selected_inventory(mUiState, inventory.size()) && *mUiState.mSelectedInventoryIndex == inventoryIndex,
            false);
    }

    // Repair summary panel for the permanent race modules.
    drawPanel(menuPanelRect, sf::Color(32, 27, 22), sf::Color(196, 142, 74), 3.0f);
    bitmap_text::draw_text(mWindow, app_text::kGarageMenuFuel, menuFuelRect.position, 1.95f, sf::Color(240, 205, 142));
    bitmap_text::draw_text(mWindow, app_text::kGarageMenuAero, menuAeroRect.position, 1.95f, player.hasBrokenMod(ModType::aero_wing) ? sf::Color(255, 166, 166) : sf::Color(171, 232, 204));
    bitmap_text::draw_text(mWindow, app_text::kGarageMenuPower, menuPowerRect.position, 1.95f, player.hasBrokenMod(ModType::high_power) ? sf::Color(255, 166, 166) : sf::Color(232, 196, 188));
    bitmap_text::draw_text(mWindow, app_text::kGarageMenuWet, menuWetRect.position, 1.95f, player.hasBrokenMod(ModType::wet_grip) ? sf::Color(255, 166, 166) : sf::Color(184, 204, 232));

    // Selected loot details panel.
    drawPanel(selectedPanelRect, sf::Color(31, 28, 24), sf::Color(152, 136, 118), 3.0f);
    app_render_helpers::draw_text_if_not_empty(mWindow, app_text::kGarageSelectedPart, selectedTitleRect.position, 3.0f, sf::Color(239, 241, 247));
    if (app_state::has_selected_inventory(mUiState, inventory.size())) {
        const Item& selectedItem = inventory[*mUiState.mSelectedInventoryIndex];
        drawItemCard(selectedItem, debugRectOverride("garage.selected_card", layout::selected_card_rect()), true, false);
        drawWrapped(app_text::kGarageSelectedLootHint, selectedStatusRect.position, 1.35f, selectedStatusRect.size.x, sf::Color(195, 204, 216));
    } else {
        drawWrapped(app_text::kGarageSelectedHint, selectedHintRect.position, 1.8f, selectedHintRect.size.x, sf::Color(185, 193, 206));
    }

}
