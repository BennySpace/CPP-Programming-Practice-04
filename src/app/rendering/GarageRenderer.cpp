#include "Application.h"
#include "layout/Layouts.h"
#include "rendering/RenderHelpers.h"
#include "sfml/SfmlUtils.h"
#include "text/UiText.h"
#include "BitmapText.h"
#include <algorithm>

void Application::drawGarage() {
    using layout = app_layout::GarageLayout;

    drawPanel(layout::inventory_panel_rect(), sf::Color(25, 22, 19), sf::Color(178, 98, 58), 3.0f);

    const auto& inventory = mGame.player().inventory();
    const size_t visibleInventoryCount = std::min(inventory.size(), layout::kVisibleInventoryCardCount);
    for (size_t index = 0; index < visibleInventoryCount; ++index) {
        drawItemCard(
            inventory[index],
            layout::inventory_card(index),
            mUiState.mSelectedInventoryIndex.has_value() && *mUiState.mSelectedInventoryIndex == index,
            false);
    }

    drawPanel(layout::menu_panel_rect(), sf::Color(32, 27, 22), sf::Color(196, 142, 74), 3.0f);
    bitmap_text::draw_text(mWindow, app_text::kGarageMenuFuel, {layout::kMenuLineX, layout::kMenuFuelY}, 1.95f, sf::Color(240, 205, 142));
    bitmap_text::draw_text(mWindow, app_text::kGarageMenuAero, {layout::kMenuLineX, layout::kMenuAeroY}, 1.95f, sf::Color(171, 232, 204));
    bitmap_text::draw_text(mWindow, app_text::kGarageMenuPower, {layout::kMenuLineX, layout::kMenuPowerY}, 1.95f, sf::Color(232, 196, 188));
    bitmap_text::draw_text(mWindow, app_text::kGarageMenuWet, {layout::kMenuLineX, layout::kMenuWetY}, 1.95f, sf::Color(184, 204, 232));

    drawPanel(layout::selected_panel_rect(), sf::Color(31, 28, 24), sf::Color(152, 136, 118), 3.0f);
    app_render_helpers::draw_text_if_not_empty(mWindow, app_text::kGarageSelectedPart, {layout::kSelectedTitleX, layout::kSelectedTitleY}, 3.0f, sf::Color(239, 241, 247));
    if (mUiState.mSelectedInventoryIndex.has_value() && *mUiState.mSelectedInventoryIndex < inventory.size()) {
        const Item& selectedItem = inventory[*mUiState.mSelectedInventoryIndex];
        drawItemCard(selectedItem, layout::selected_card_rect(), true, false);
        const char* statusText = app_text::kGarageSelectedWorkingHint;
        if (selectedItem.mType == ItemType::loot) {
            statusText = app_text::kGarageSelectedLootHint;
        } else if (selectedItem.mIsBroken) {
            statusText = app_text::kGarageSelectedBrokenHint;
        }
        drawWrapped(statusText, {layout::kSelectedStatusX, layout::kSelectedStatusY}, 1.35f, layout::kSelectedStatusWidth, sf::Color(195, 204, 216));
    } else {
        drawWrapped(app_text::kGarageSelectedHint, {layout::kSelectedHintX, layout::kSelectedHintY}, 1.8f, layout::kSelectedHintWidth, sf::Color(185, 193, 206));
    }
}
