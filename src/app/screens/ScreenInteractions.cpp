#include "screens/ScreenInteractions.h"
#include "layout/Layouts.h"
#include "sfml/SfmlUtils.h"
#include "text/UiText.h"
#include <algorithm>

namespace {
size_t page_count(const size_t itemCount, const size_t pageSize) {
    return std::max<size_t>(1, (itemCount + pageSize - 1) / pageSize);
}

void append_confirmation_buttons(ScreenInteractions& pInteractions) {
    using layout = app_layout::MainMenuLayout;

    pInteractions.mButtons.push_back(make_button(
        AppCommand::confirm_new_game,
        app_text::kButtonConfirmReset,
        layout::confirm_yes_button_rect(),
        {140, 34, 30},
        {255, 185, 185},
        true));
    pInteractions.mButtons.push_back(make_button(
        AppCommand::cancel_new_game,
        app_text::kButtonCancel,
        layout::confirm_cancel_button_rect(),
        {56, 60, 68},
        {226, 230, 236},
        true));
}

void append_main_menu_buttons(ScreenInteractions& pInteractions) {
    using layout = app_layout::MainMenuLayout;

    pInteractions.mButtons.push_back(make_button(AppCommand::go_race, app_text::kButtonGoRace, layout::go_race_button_rect(), {223, 43, 37}, {255, 216, 97}, true));
    pInteractions.mButtons.push_back(make_button(AppCommand::go_garage, app_text::kButtonGoGarage, layout::go_garage_button_rect(), {54, 57, 64}, {239, 241, 233}, true));
    pInteractions.mButtons.push_back(make_button(AppCommand::go_museum, app_text::kButtonGoMuseum, layout::go_museum_button_rect(), {161, 122, 40}, {255, 222, 119}, true));
    pInteractions.mButtons.push_back(make_button(AppCommand::new_game, app_text::kButtonNewGame, layout::new_game_button_rect(), {89, 24, 22}, {255, 184, 184}, true));
    pInteractions.mButtons.push_back(make_button(AppCommand::exit_app, app_text::kButtonExit, layout::exit_button_rect(), {40, 42, 46}, {209, 213, 216}, true));
}

void append_race_hub_interactions(const GameSession& pGame, ScreenInteractions& pInteractions) {
    using layout = app_layout::RaceLayout;

    const bool activeRace = pGame.activeRace() != nullptr;
    const PlayerProfile& player = pGame.player();

    for (size_t index = 0; index < pGame.races().size(); ++index) {
        pInteractions.mHotspots.push_back({
            layout::race_card(index),
            ScreenSelectionKind::race,
            index,
            app_text::kBannerRaceSelectedTitle,
            pGame.races()[index]->get_name(),
            true});
    }

    pInteractions.mButtons.push_back(make_button(AppCommand::start_race, app_text::kButtonStartRace, layout::start_race_button_rect(), {198, 74, 48}, {255, 216, 128}, !activeRace));
    pInteractions.mButtons.push_back(make_button(AppCommand::drive_aero, app_text::kButtonDriveAero, layout::drive_aero_button_rect(), {40, 130, 122}, {197, 242, 229}, activeRace && player.hasMod(ModType::aero_wing) && player.fuel() > 0));
    pInteractions.mButtons.push_back(make_button(AppCommand::drive_power, app_text::kButtonDrivePower, layout::drive_power_button_rect(), {158, 82, 60}, {241, 211, 198}, activeRace && player.hasMod(ModType::high_power) && player.fuel() > 0));
    pInteractions.mButtons.push_back(make_button(AppCommand::drive_wet, app_text::kButtonDriveWet, layout::drive_wet_button_rect(), {54, 92, 158}, {202, 220, 246}, activeRace && player.hasMod(ModType::wet_grip) && player.fuel() > 0));
    pInteractions.mButtons.push_back(make_button(AppCommand::leave_race, app_text::kButtonLeaveRace, layout::leave_race_button_rect(), {48, 64, 82}, {196, 210, 228}, activeRace));
    pInteractions.mButtons.push_back(make_button(AppCommand::back_main, app_text::kButtonBackMain, layout::back_button_rect(), {56, 72, 96}, {205, 220, 240}, true));
}

void append_garage_interactions(const GameSession& pGame, const ApplicationState& pUiState, ScreenInteractions& pInteractions) {
    using layout = app_layout::GarageLayout;

    const PlayerProfile& player = pGame.player();
    const auto& inventory = player.inventory();
    const size_t pageCount = page_count(inventory.size(), layout::kVisibleInventoryCardCount);
    const size_t pageStart = pUiState.mGarageInventoryPage * layout::kVisibleInventoryCardCount;
    const size_t visibleCount = std::min(layout::kVisibleInventoryCardCount, inventory.size() - std::min(pageStart, inventory.size()));
    bool canSellSelected = false;
    bool canRepairSelected = false;

    for (size_t displayIndex = 0; displayIndex < visibleCount; ++displayIndex) {
        const size_t inventoryIndex = pageStart + displayIndex;
        pInteractions.mHotspots.push_back({
            layout::inventory_card(displayIndex),
            ScreenSelectionKind::inventory,
            inventoryIndex,
            app_text::kBannerItemSelectedTitle,
            inventory[inventoryIndex].mName,
            true});
    }

    if (pUiState.mSelectedInventoryIndex.has_value() && *pUiState.mSelectedInventoryIndex < inventory.size()) {
        const Item& selectedItem = inventory[*pUiState.mSelectedInventoryIndex];
        canSellSelected = selectedItem.mType == ItemType::loot;
        canRepairSelected = selectedItem.mType == ItemType::equipment && selectedItem.mIsBroken;
    }

    pInteractions.mButtons.push_back(make_button(AppCommand::buy_fuel, app_text::kButtonBuyFuel, layout::buy_fuel_button_rect(), {224, 132, 42}, {255, 218, 164}, true));
    pInteractions.mButtons.push_back(make_button(AppCommand::buy_aero, app_text::kButtonBuyAero, layout::buy_aero_button_rect(), {56, 142, 114}, {210, 245, 226}, !player.hasMod(ModType::aero_wing)));
    pInteractions.mButtons.push_back(make_button(AppCommand::buy_power, app_text::kButtonBuyPower, layout::buy_power_button_rect(), {170, 94, 68}, {244, 214, 198}, !player.hasMod(ModType::high_power)));
    pInteractions.mButtons.push_back(make_button(AppCommand::buy_wet, app_text::kButtonBuyWet, layout::buy_wet_button_rect(), {78, 112, 172}, {207, 222, 247}, !player.hasMod(ModType::wet_grip)));
    pInteractions.mButtons.push_back(make_button(AppCommand::sell_selected, app_text::kButtonSellSelected, layout::sell_button_rect(), {128, 112, 46}, {239, 226, 162}, canSellSelected));
    pInteractions.mButtons.push_back(make_button(AppCommand::repair_selected, app_text::kButtonRepairSelected, layout::repair_button_rect(), {126, 92, 74}, {230, 202, 188}, canRepairSelected));
    pInteractions.mButtons.push_back(make_button(AppCommand::garage_prev_page, app_text::kButtonPrevPage, layout::prev_page_button_rect(), {66, 72, 80}, {205, 213, 224}, pUiState.mGarageInventoryPage > 0));
    pInteractions.mButtons.push_back(make_button(AppCommand::garage_next_page, app_text::kButtonNextPage, layout::next_page_button_rect(), {66, 72, 80}, {205, 213, 224}, pUiState.mGarageInventoryPage + 1 < pageCount));
    pInteractions.mButtons.push_back(make_button(AppCommand::back_main, app_text::kButtonBackMain, layout::back_button_rect(), {88, 78, 70}, {214, 204, 194}, true));
}

void append_museum_interactions(const GameSession& pGame, const ApplicationState& pUiState, ScreenInteractions& pInteractions) {
    using layout = app_layout::MuseumLayout;

    bool canDonateSelected = false;
    const auto& inventory = pGame.player().inventory();
    const auto& museumCollection = pGame.player().museumCollection();
    const auto lootIndices = pGame.player().lootIndices();
    const size_t exhibitPageCount = page_count(museumCollection.size(), layout::kVisibleExhibitCardCount);
    const size_t dropPageCount = page_count(lootIndices.size(), layout::kVisibleDropCardCount);
    const size_t dropPageStart = pUiState.mMuseumDropPage * layout::kVisibleDropCardCount;
    const size_t visibleCount = std::min(layout::kVisibleDropCardCount, lootIndices.size() - std::min(dropPageStart, lootIndices.size()));

    for (size_t displayIndex = 0; displayIndex < visibleCount; ++displayIndex) {
        const size_t inventoryIndex = lootIndices[dropPageStart + displayIndex];
        pInteractions.mHotspots.push_back({
            layout::drop_card(displayIndex),
            ScreenSelectionKind::inventory,
            inventoryIndex,
            app_text::kBannerDonationSlotTitle,
            inventory[inventoryIndex].mName,
            true});
    }

    if (pUiState.mSelectedInventoryIndex.has_value() && *pUiState.mSelectedInventoryIndex < inventory.size()) {
        const Item& selectedItem = inventory[*pUiState.mSelectedInventoryIndex];
        canDonateSelected = selectedItem.mType == ItemType::loot;

        if (canDonateSelected) {
            for (const auto& exhibit : museumCollection) {
                if (exhibit.mName == selectedItem.mName) {
                    canDonateSelected = false;
                    break;
                }
            }
        }
    }

    pInteractions.mButtons.push_back(make_button(AppCommand::museum_exhibit_prev_page, app_text::kButtonPrevPage, layout::hall_prev_button_rect(), {82, 72, 58}, {221, 205, 170}, pUiState.mMuseumExhibitPage > 0));
    pInteractions.mButtons.push_back(make_button(AppCommand::museum_exhibit_next_page, app_text::kButtonNextPage, layout::hall_next_button_rect(), {82, 72, 58}, {221, 205, 170}, pUiState.mMuseumExhibitPage + 1 < exhibitPageCount));
    pInteractions.mButtons.push_back(make_button(AppCommand::museum_drop_prev_page, app_text::kButtonPrevPage, layout::drop_prev_button_rect(), {78, 64, 60}, {214, 189, 184}, pUiState.mMuseumDropPage > 0));
    pInteractions.mButtons.push_back(make_button(AppCommand::museum_drop_next_page, app_text::kButtonNextPage, layout::drop_next_button_rect(), {78, 64, 60}, {214, 189, 184}, pUiState.mMuseumDropPage + 1 < dropPageCount));
    pInteractions.mButtons.push_back(make_button(AppCommand::donate_selected, app_text::kButtonDonateSelected, layout::donate_button_rect(), {164, 126, 62}, {241, 220, 162}, canDonateSelected));
    pInteractions.mButtons.push_back(make_button(AppCommand::back_main, app_text::kButtonBackMain, layout::back_button_rect(), {84, 72, 62}, {218, 206, 190}, true));
}
}

ScreenInteractions build_screen_interactions(const GameSession& pGame, const ApplicationState& pUiState) {
    ScreenInteractions interactions;

    if (pUiState.mConfirmingNewGame) {
        append_confirmation_buttons(interactions);
        return interactions;
    }

    switch (pUiState.mScreen) {
        case ApplicationScreen::main_menu:
            append_main_menu_buttons(interactions);
            break;
        case ApplicationScreen::race_hub:
            append_race_hub_interactions(pGame, interactions);
            break;
        case ApplicationScreen::garage:
            append_garage_interactions(pGame, pUiState, interactions);
            break;
        case ApplicationScreen::museum:
            append_museum_interactions(pGame, pUiState, interactions);
            break;
    }

    return interactions;
}
