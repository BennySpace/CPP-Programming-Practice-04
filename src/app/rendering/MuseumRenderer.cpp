#include "Application.h"
#include "layout/Layouts.h"
#include "rendering/RenderHelpers.h"
#include "sfml/SfmlUtils.h"
#include "text/UiText.h"
#include "BitmapText.h"
#include <algorithm>

void Application::drawMuseum() {
    using layout = app_layout::MuseumLayout;

    drawPanel(layout::hall_panel_rect(), sf::Color(32, 24, 18), sf::Color(186, 146, 78), 3.0f);
    bitmap_text::draw_text(mWindow, app_text::kMuseumTitle, {layout::kHallTitleX, layout::kHallTitleY}, 3.0f, sf::Color(245, 235, 214));

    const auto& exhibits = mGame.player().museumCollection();
    if (exhibits.empty()) {
        drawWrapped(app_text::kMuseumEmptyHint, {layout::kHallEmptyX, layout::kHallEmptyY}, 2.1f, layout::kHallEmptyWidth, sf::Color(210, 200, 184));
    } else {
        const size_t visibleExhibitCount = std::min(exhibits.size(), layout::kVisibleExhibitCardCount);
        for (size_t index = 0; index < visibleExhibitCount; ++index) {
            drawItemCard(exhibits[index], layout::exhibit_card(index), false, true);
        }
    }

    drawPanel(layout::drop_panel_rect(), sf::Color(28, 22, 19), sf::Color(160, 88, 74), 3.0f);
    app_render_helpers::draw_text_if_not_empty(mWindow, app_text::kMuseumDropOffTitle, {layout::kDropTitleX, layout::kDropTitleY}, 3.0f, sf::Color(239, 241, 247));

    const auto lootIndices = mGame.player().lootIndices();
    if (lootIndices.empty()) {
        drawWrapped(app_text::kMuseumDropOffEmpty, {layout::kDropEmptyX, layout::kDropEmptyY}, 1.9f, layout::kDropEmptyWidth, sf::Color(186, 194, 206));
    } else {
        const size_t visibleDropCount = std::min(lootIndices.size(), layout::kVisibleDropCardCount);
        for (size_t displayIndex = 0; displayIndex < visibleDropCount; ++displayIndex) {
            const size_t inventoryIndex = lootIndices[displayIndex];
            drawItemCard(
                mGame.player().inventory()[inventoryIndex],
                layout::drop_card(displayIndex),
                mUiState.mSelectedInventoryIndex.has_value() && *mUiState.mSelectedInventoryIndex == inventoryIndex,
                false);
        }
    }

    drawPanel(layout::milestone_panel_rect(), sf::Color(30, 24, 20), sf::Color(188, 154, 92), 3.0f);
    app_render_helpers::draw_text_if_not_empty(mWindow, app_text::kMuseumMilestones, {layout::kMilestoneTitleX, layout::kMilestoneTitleY}, 2.5f, sf::Color(255, 223, 150));
    bitmap_text::draw_text(mWindow, app_text::kMuseumRewards, {layout::kRewardsTextX, layout::kRewardsTextY}, 2.0f, sf::Color(195, 204, 220));
}
