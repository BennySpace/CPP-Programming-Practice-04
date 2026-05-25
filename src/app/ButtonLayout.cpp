#include "Application.h"
#include "layout/Layouts.h"
#include "sfml/SfmlUtils.h"
#include "text/UiText.h"

void Application::rebuildButtons() {
    mButtons.clear();

    if (mUiState.mConfirmingNewGame) {
        using layout = app_layout::MainMenuLayout;
        mButtons.push_back(make_button(AppCommand::confirm_new_game, app_text::kButtonConfirmReset, layout::confirm_yes_button_rect(), {140, 34, 30}, {255, 185, 185}, true));
        mButtons.push_back(make_button(AppCommand::cancel_new_game, app_text::kButtonCancel, layout::confirm_cancel_button_rect(), {56, 60, 68}, {226, 230, 236}, true));
        return;
    }

    if (mUiState.mScreen == ApplicationScreen::main_menu) {
        using layout = app_layout::MainMenuLayout;
        mButtons.push_back(make_button(AppCommand::go_race, app_text::kButtonGoRace, layout::go_race_button_rect(), {223, 43, 37}, {255, 216, 97}, true));
        mButtons.push_back(make_button(AppCommand::go_garage, app_text::kButtonGoGarage, layout::go_garage_button_rect(), {54, 57, 64}, {239, 241, 233}, true));
        mButtons.push_back(make_button(AppCommand::go_museum, app_text::kButtonGoMuseum, layout::go_museum_button_rect(), {161, 122, 40}, {255, 222, 119}, true));
        mButtons.push_back(make_button(AppCommand::new_game, app_text::kButtonNewGame, layout::new_game_button_rect(), {89, 24, 22}, {255, 184, 184}, true));
        mButtons.push_back(make_button(AppCommand::exit_app, app_text::kButtonExit, layout::exit_button_rect(), {40, 42, 46}, {209, 213, 216}, true));
    } else if (mUiState.mScreen == ApplicationScreen::race_hub) {
        using layout = app_layout::RaceLayout;
        const bool activeRace = mGame.activeRace() != nullptr;
        const PlayerProfile& player = mGame.player();
        mButtons.push_back(make_button(AppCommand::start_race, app_text::kButtonStartRace, layout::start_race_button_rect(), {198, 74, 48}, {255, 216, 128}, !activeRace));
        mButtons.push_back(make_button(AppCommand::drive_aero, app_text::kButtonDriveAero, layout::drive_aero_button_rect(), {40, 130, 122}, {197, 242, 229}, activeRace && player.hasMod(ModType::aero_wing) && player.fuel() > 0));
        mButtons.push_back(make_button(AppCommand::drive_power, app_text::kButtonDrivePower, layout::drive_power_button_rect(), {158, 82, 60}, {241, 211, 198}, activeRace && player.hasMod(ModType::high_power) && player.fuel() > 0));
        mButtons.push_back(make_button(AppCommand::drive_wet, app_text::kButtonDriveWet, layout::drive_wet_button_rect(), {54, 92, 158}, {202, 220, 246}, activeRace && player.hasMod(ModType::wet_grip) && player.fuel() > 0));
        mButtons.push_back(make_button(AppCommand::leave_race, app_text::kButtonLeaveRace, layout::leave_race_button_rect(), {48, 64, 82}, {196, 210, 228}, activeRace));
        mButtons.push_back(make_button(AppCommand::back_main, app_text::kButtonBackMain, layout::back_button_rect(), {56, 72, 96}, {205, 220, 240}, true));
    } else if (mUiState.mScreen == ApplicationScreen::garage) {
        using layout = app_layout::GarageLayout;
        const PlayerProfile& player = mGame.player();
        const auto& inventory = player.inventory();
        bool canSellSelected = false;
        bool canRepairSelected = false;

        if (mUiState.mSelectedInventoryIndex.has_value() && *mUiState.mSelectedInventoryIndex < inventory.size()) {
            const Item& selectedItem = inventory[*mUiState.mSelectedInventoryIndex];
            canSellSelected = selectedItem.mType == ItemType::loot;
            canRepairSelected = selectedItem.mType == ItemType::equipment && selectedItem.mIsBroken;
        }

        mButtons.push_back(make_button(AppCommand::buy_fuel, app_text::kButtonBuyFuel, layout::buy_fuel_button_rect(), {224, 132, 42}, {255, 218, 164}, true));
        mButtons.push_back(make_button(AppCommand::buy_aero, app_text::kButtonBuyAero, layout::buy_aero_button_rect(), {56, 142, 114}, {210, 245, 226}, !player.hasMod(ModType::aero_wing)));
        mButtons.push_back(make_button(AppCommand::buy_power, app_text::kButtonBuyPower, layout::buy_power_button_rect(), {170, 94, 68}, {244, 214, 198}, !player.hasMod(ModType::high_power)));
        mButtons.push_back(make_button(AppCommand::buy_wet, app_text::kButtonBuyWet, layout::buy_wet_button_rect(), {78, 112, 172}, {207, 222, 247}, !player.hasMod(ModType::wet_grip)));
        mButtons.push_back(make_button(AppCommand::sell_selected, app_text::kButtonSellSelected, layout::sell_button_rect(), {128, 112, 46}, {239, 226, 162}, canSellSelected));
        mButtons.push_back(make_button(AppCommand::repair_selected, app_text::kButtonRepairSelected, layout::repair_button_rect(), {126, 92, 74}, {230, 202, 188}, canRepairSelected));
        mButtons.push_back(make_button(AppCommand::back_main, app_text::kButtonBackMain, layout::back_button_rect(), {88, 78, 70}, {214, 204, 194}, true));
    } else if (mUiState.mScreen == ApplicationScreen::museum) {
        using layout = app_layout::MuseumLayout;
        bool canDonateSelected = false;
        const auto& inventory = mGame.player().inventory();
        const auto& museumCollection = mGame.player().museumCollection();

        if (mUiState.mSelectedInventoryIndex.has_value() && *mUiState.mSelectedInventoryIndex < inventory.size()) {
            const Item& selectedItem = inventory[*mUiState.mSelectedInventoryIndex];
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

        mButtons.push_back(make_button(AppCommand::donate_selected, app_text::kButtonDonateSelected, layout::donate_button_rect(), {164, 126, 62}, {241, 220, 162}, canDonateSelected));
        mButtons.push_back(make_button(AppCommand::back_main, app_text::kButtonBackMain, layout::back_button_rect(), {84, 72, 62}, {218, 206, 190}, true));
    }
}
