#include "Application.h"
#include "layout/Layouts.h"
#include "rendering/RenderHelpers.h"
#include "sfml/SfmlUtils.h"
#include "text/UiText.h"
#include "BitmapText.h"
#include <algorithm>

void Application::drawMuseum() {
    using layout = app_layout::MuseumLayout;

    // Museum screen layout anchors for panels and labels.
    const sf::FloatRect hallPanelRect = debugRectOverride("museum.hall_panel", layout::hall_panel_rect());
    const sf::FloatRect dropPanelRect = debugRectOverride("museum.drop_panel", layout::drop_panel_rect());
    const sf::FloatRect milestonePanelRect = debugRectOverride("museum.milestone_panel", layout::milestone_panel_rect());
    const sf::FloatRect hallTitleRect = debugRectOverride("museum.hall_title_text", {{layout::kHallTitleX, layout::kHallTitleY}, {260.0f, 28.0f}});
    const sf::FloatRect hallEmptyRect = debugRectOverride("museum.hall_empty_text", {{layout::kHallEmptyX, layout::kHallEmptyY}, {layout::kHallEmptyWidth, 90.0f}});
    const sf::FloatRect dropTitleRect = debugRectOverride("museum.drop_title_text", {{layout::kDropTitleX, layout::kDropTitleY}, {240.0f, 28.0f}});
    const sf::FloatRect dropEmptyRect = debugRectOverride("museum.drop_empty_text", {{layout::kDropEmptyX, layout::kDropEmptyY}, {layout::kDropEmptyWidth, 90.0f}});
    const sf::FloatRect milestoneTitleRect = debugRectOverride("museum.milestone_title_text", {{layout::kMilestoneTitleX, layout::kMilestoneTitleY}, {240.0f, 28.0f}});
    const sf::FloatRect rewardsRect = debugRectOverride("museum.rewards_text", {{layout::kRewardsTextX, layout::kRewardsTextY}, {320.0f, 24.0f}});
    // Exhibit hall panel with donated collection cards.
    drawPanel(hallPanelRect, sf::Color(32, 24, 18), sf::Color(186, 146, 78), 3.0f);
    bitmap_text::draw_text(mWindow, app_text::kMuseumTitle, hallTitleRect.position, 3.0f, sf::Color(245, 235, 214));

    const auto& exhibits = mGame.player().museumCollection();
    const size_t exhibitPageStart = app_state::page_start(mUiState.mMuseumExhibitPage, layout::kVisibleExhibitCardCount);
    if (exhibits.empty()) {
        drawWrapped(app_text::kMuseumEmptyHint, hallEmptyRect.position, 2.1f, hallEmptyRect.size.x, sf::Color(210, 200, 184));
    } else {
        const size_t visibleExhibitCount = app_state::visible_item_count(exhibits.size(), exhibitPageStart, layout::kVisibleExhibitCardCount);
        for (size_t displayIndex = 0; displayIndex < visibleExhibitCount; ++displayIndex) {
            drawItemCard(
                exhibits[exhibitPageStart + displayIndex],
                debugRectOverride("museum.exhibit_card_" + std::to_string(displayIndex), layout::exhibit_card(displayIndex)),
                false,
                true);
        }
    }

    // Drop-off panel with loot ready for donation.
    drawPanel(dropPanelRect, sf::Color(28, 22, 19), sf::Color(160, 88, 74), 3.0f);
    app_render_helpers::draw_text_if_not_empty(mWindow, app_text::kMuseumDropOffTitle, dropTitleRect.position, 3.0f, sf::Color(239, 241, 247));

    const auto lootIndices = mGame.player().lootIndices();
    const size_t dropPageStart = app_state::page_start(mUiState.mMuseumDropPage, layout::kVisibleDropCardCount);
    if (lootIndices.empty()) {
        drawWrapped(app_text::kMuseumDropOffEmpty, dropEmptyRect.position, 1.9f, dropEmptyRect.size.x, sf::Color(186, 194, 206));
    } else {
        const size_t visibleDropCount = app_state::visible_item_count(lootIndices.size(), dropPageStart, layout::kVisibleDropCardCount);
        for (size_t displayIndex = 0; displayIndex < visibleDropCount; ++displayIndex) {
            const size_t inventoryIndex = lootIndices[dropPageStart + displayIndex];
            drawItemCard(
                mGame.player().inventory()[inventoryIndex],
                debugRectOverride("museum.drop_card_" + std::to_string(displayIndex), layout::drop_card(displayIndex)),
                app_state::has_selected_inventory(mUiState, mGame.player().inventory().size()) && *mUiState.mSelectedInventoryIndex == inventoryIndex,
                false);
        }
    }

    // Milestones and rewards summary panel.
    drawPanel(milestonePanelRect, sf::Color(30, 24, 20), sf::Color(188, 154, 92), 3.0f);
    app_render_helpers::draw_text_if_not_empty(mWindow, app_text::kMuseumMilestones, milestoneTitleRect.position, 2.5f, sf::Color(255, 223, 150));
    bitmap_text::draw_text(mWindow, app_text::kMuseumRewards, rewardsRect.position, 2.0f, sf::Color(195, 204, 220));
}
