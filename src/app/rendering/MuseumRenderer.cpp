#include "Application.h"
#include "layout/Layouts.h"
#include "rendering/RenderHelpers.h"
#include "sfml/SfmlUtils.h"
#include "text/UiText.h"
#include "BitmapText.h"
#include <algorithm>

namespace {
size_t page_count(const size_t itemCount, const size_t pageSize) {
    return std::max<size_t>(1, (itemCount + pageSize - 1) / pageSize);
}
}

void Application::drawMuseum() {
    using layout = app_layout::MuseumLayout;

    drawPanel(layout::hall_panel_rect(), sf::Color(32, 24, 18), sf::Color(186, 146, 78), 3.0f);
    bitmap_text::draw_text(mWindow, app_text::kMuseumTitle, {layout::kHallTitleX, layout::kHallTitleY}, 3.0f, sf::Color(245, 235, 214));

    const auto& exhibits = mGame.player().museumCollection();
    const size_t exhibitPageStart = mUiState.mMuseumExhibitPage * layout::kVisibleExhibitCardCount;
    if (exhibits.empty()) {
        drawWrapped(app_text::kMuseumEmptyHint, {layout::kHallEmptyX, layout::kHallEmptyY}, 2.1f, layout::kHallEmptyWidth, sf::Color(210, 200, 184));
    } else {
        const size_t visibleExhibitCount = std::min(layout::kVisibleExhibitCardCount, exhibits.size() - std::min(exhibitPageStart, exhibits.size()));
        for (size_t displayIndex = 0; displayIndex < visibleExhibitCount; ++displayIndex) {
            drawItemCard(exhibits[exhibitPageStart + displayIndex], layout::exhibit_card(displayIndex), false, true);
        }
    }
    drawPanel(layout::drop_panel_rect(), sf::Color(28, 22, 19), sf::Color(160, 88, 74), 3.0f);
    app_render_helpers::draw_text_if_not_empty(mWindow, app_text::kMuseumDropOffTitle, {layout::kDropTitleX, layout::kDropTitleY}, 3.0f, sf::Color(239, 241, 247));

    const auto lootIndices = mGame.player().lootIndices();
    const size_t dropPageStart = mUiState.mMuseumDropPage * layout::kVisibleDropCardCount;
    if (lootIndices.empty()) {
        drawWrapped(app_text::kMuseumDropOffEmpty, {layout::kDropEmptyX, layout::kDropEmptyY}, 1.9f, layout::kDropEmptyWidth, sf::Color(186, 194, 206));
    } else {
        const size_t visibleDropCount = std::min(layout::kVisibleDropCardCount, lootIndices.size() - std::min(dropPageStart, lootIndices.size()));
        for (size_t displayIndex = 0; displayIndex < visibleDropCount; ++displayIndex) {
            const size_t inventoryIndex = lootIndices[dropPageStart + displayIndex];
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
