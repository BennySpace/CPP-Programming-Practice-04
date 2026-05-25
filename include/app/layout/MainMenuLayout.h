#ifndef MAIN_MENU_LAYOUT_H
#define MAIN_MENU_LAYOUT_H

#include "layout/Layout.h"

namespace app_layout {
struct MainMenuLayout {
    static constexpr float kHeroGroupOffsetX = 0.0f;
    static constexpr float kHeroGroupOffsetY = 0.0f;
    static constexpr float kTrackRowOffsetX = 0.0f;
    static constexpr float kTrackRowOffsetY = 8.0f;
    static constexpr float kActionRowOffsetX = 0.0f;
    static constexpr float kActionRowOffsetY = 4.0f;

    static constexpr float kPanelX = 60.0f;
    static constexpr float kPanelY = 170.0f;
    static constexpr float kPanelWidth = 1320.0f;
    static constexpr float kPanelHeight = 450.0f;
    static constexpr float kTitleX = 404.0f + kHeroGroupOffsetX;
    static constexpr float kTitleY = 210.0f + kHeroGroupOffsetY;
    static constexpr float kFooterX = 110.0f;
    static constexpr float kFooterY = 570.0f;

    static constexpr float kTrackCardX = 130.0f + kTrackRowOffsetX;
    static constexpr float kTrackCardY = 280.0f + kTrackRowOffsetY;
    static constexpr float kTrackCardWidth = 360.0f;
    static constexpr float kTrackCardHeight = 250.0f;
    static constexpr float kTrackCardStepX = 410.0f;
    static constexpr float kTrackPhotoInsetX = 20.0f;
    static constexpr float kTrackPhotoInsetY = 24.0f;
    static constexpr float kTrackPhotoWidth = 320.0f;
    static constexpr float kTrackPhotoHeight = 150.0f;
    static constexpr float kTrackLabelCenterOffsetX = 180.0f;
    static constexpr float kTrackLabelY = 478.0f + kTrackRowOffsetY;
    static constexpr float kTrackPhotoPlaceholderY = 365.0f;

    static constexpr float kStartLightX = 112.0f + kHeroGroupOffsetX;
    static constexpr float kStartLightY = 204.0f + kHeroGroupOffsetY;
    static constexpr float kStartLightStepX = 56.0f;
    static constexpr float kStartLightRadius = 20.0f;

    static constexpr float kConfirmModalX = 420.0f;
    static constexpr float kConfirmModalY = 300.0f;
    static constexpr float kConfirmModalWidth = 600.0f;
    static constexpr float kConfirmModalHeight = 260.0f;
    static constexpr float kConfirmTitleCenterX = 720.0f;
    static constexpr float kConfirmTitleY = 336.0f;
    static constexpr float kConfirmTextX = 470.0f;
    static constexpr float kConfirmTextY = 390.0f;
    static constexpr float kConfirmTextWidth = 500.0f;

    static constexpr float kGoRaceButtonX = 115.0f + kActionRowOffsetX;
    static constexpr float kGoRaceButtonY = 670.0f + kActionRowOffsetY;
    static constexpr float kGoRaceButtonWidth = 270.0f;
    static constexpr float kGoRaceButtonHeight = 82.0f;
    static constexpr float kGoGarageButtonX = 415.0f + kActionRowOffsetX;
    static constexpr float kGoGarageButtonY = 670.0f + kActionRowOffsetY;
    static constexpr float kGoGarageButtonWidth = 220.0f;
    static constexpr float kGoGarageButtonHeight = 82.0f;
    static constexpr float kGoMuseumButtonX = 665.0f + kActionRowOffsetX;
    static constexpr float kGoMuseumButtonY = 670.0f + kActionRowOffsetY;
    static constexpr float kGoMuseumButtonWidth = 220.0f;
    static constexpr float kGoMuseumButtonHeight = 82.0f;
    static constexpr float kNewGameButtonX = 915.0f + kActionRowOffsetX;
    static constexpr float kNewGameButtonY = 670.0f + kActionRowOffsetY;
    static constexpr float kNewGameButtonWidth = 220.0f;
    static constexpr float kNewGameButtonHeight = 82.0f;
    static constexpr float kExitButtonX = 1165.0f + kActionRowOffsetX;
    static constexpr float kExitButtonY = 670.0f + kActionRowOffsetY;
    static constexpr float kExitButtonWidth = 160.0f;
    static constexpr float kExitButtonHeight = 82.0f;

    static constexpr float kConfirmYesButtonX = 500.0f;
    static constexpr float kConfirmYesButtonY = 450.0f;
    static constexpr float kConfirmYesButtonWidth = 190.0f;
    static constexpr float kConfirmYesButtonHeight = 66.0f;
    static constexpr float kConfirmCancelButtonX = 750.0f;
    static constexpr float kConfirmCancelButtonY = 450.0f;
    static constexpr float kConfirmCancelButtonWidth = 190.0f;
    static constexpr float kConfirmCancelButtonHeight = 66.0f;

    static sf::FloatRect panel_rect() {
        return make_rect(kPanelX, kPanelY, kPanelWidth, kPanelHeight);
    }

    static sf::FloatRect confirm_modal_rect() {
        return make_rect(kConfirmModalX, kConfirmModalY, kConfirmModalWidth, kConfirmModalHeight);
    }

    static sf::FloatRect track_card(const size_t index) {
        return make_rect(kTrackCardX + static_cast<float>(index) * kTrackCardStepX, kTrackCardY, kTrackCardWidth, kTrackCardHeight);
    }

    static sf::FloatRect track_photo(const size_t index) {
        return make_rect(kTrackCardX + static_cast<float>(index) * kTrackCardStepX + kTrackPhotoInsetX, kTrackCardY + kTrackPhotoInsetY, kTrackPhotoWidth, kTrackPhotoHeight);
    }

    static sf::FloatRect go_race_button_rect() {
        return make_rect(kGoRaceButtonX, kGoRaceButtonY, kGoRaceButtonWidth, kGoRaceButtonHeight);
    }

    static sf::FloatRect go_garage_button_rect() {
        return make_rect(kGoGarageButtonX, kGoGarageButtonY, kGoGarageButtonWidth, kGoGarageButtonHeight);
    }

    static sf::FloatRect go_museum_button_rect() {
        return make_rect(kGoMuseumButtonX, kGoMuseumButtonY, kGoMuseumButtonWidth, kGoMuseumButtonHeight);
    }

    static sf::FloatRect new_game_button_rect() {
        return make_rect(kNewGameButtonX, kNewGameButtonY, kNewGameButtonWidth, kNewGameButtonHeight);
    }

    static sf::FloatRect exit_button_rect() {
        return make_rect(kExitButtonX, kExitButtonY, kExitButtonWidth, kExitButtonHeight);
    }

    static sf::FloatRect confirm_yes_button_rect() {
        return make_rect(kConfirmYesButtonX, kConfirmYesButtonY, kConfirmYesButtonWidth, kConfirmYesButtonHeight);
    }

    static sf::FloatRect confirm_cancel_button_rect() {
        return make_rect(kConfirmCancelButtonX, kConfirmCancelButtonY, kConfirmCancelButtonWidth, kConfirmCancelButtonHeight);
    }
};

}

#endif // MAIN_MENU_LAYOUT_H
