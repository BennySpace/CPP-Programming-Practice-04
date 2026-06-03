#ifndef RACE_LAYOUT_H
#define RACE_LAYOUT_H

#include "layout/Layout.h"

namespace app_layout {
struct RaceLayout {
    // Left-side board panel with the list of available races.
    static constexpr float kBoardPanelX = SceneLayout::kOuterMarginX;
    static constexpr float kBoardPanelY = SceneLayout::kOuterMarginTop;
    static constexpr float kBoardPanelWidth = 340.0f;
    static constexpr float kBoardPanelHeight = 654.0f;
    static constexpr float kBoardTitleX = kBoardPanelX + 28.0f;
    static constexpr float kBoardTitleY = kBoardPanelY + 24.0f;

    // Race selection cards stacked inside the board panel.
    static constexpr float kRaceCardX = kBoardPanelX + 18.0f;
    static constexpr float kRaceCardStartY = kBoardPanelY + 28.0f;
    static constexpr float kRaceCardWidth = kBoardPanelWidth - 36.0f;
    static constexpr float kRaceCardHeight = 140.0f;
    static constexpr float kRaceCardStepY = 158.0f;
    static constexpr float kRaceCardTextX = kRaceCardX + 12.0f;
    static constexpr float kRaceCardTitleOffsetY = 24.0f;
    static constexpr float kRaceCardTypeOffsetY = 62.0f;
    static constexpr float kRaceCardFeeOffsetY = 96.0f;

    // Middle control panel with map and mod details.
    static constexpr float kControlPanelX = kBoardPanelX + kBoardPanelWidth + SceneLayout::kPanelGap;
    static constexpr float kControlPanelY = kBoardPanelY;
    static constexpr float kControlPanelWidth = 480.0f;
    static constexpr float kControlPanelHeight = kBoardPanelHeight;
    static constexpr float kControlTitleX = kControlPanelX + 28.0f;
    static constexpr float kControlTitleY = kControlPanelY + 24.0f;

    // Track map preview inside the control panel.
    static constexpr float kTrackMapX = kControlPanelX + 28.0f;
    static constexpr float kTrackMapY = kControlPanelY + 44.0f;
    static constexpr float kTrackMapWidth = kControlPanelWidth - 56.0f;
    static constexpr float kTrackMapHeight = 310.0f;

    // Installed mod labels and values below the map preview.
    static constexpr float kModTextX = kControlPanelX + 34.0f;
    static constexpr float kAeroLabelY = kTrackMapY + kTrackMapHeight + 48.0f;
    static constexpr float kAeroValueY = kAeroLabelY + 24.0f;
    static constexpr float kPowerLabelY = kAeroValueY + 42.0f;
    static constexpr float kPowerValueY = kPowerLabelY + 24.0f;
    static constexpr float kWetLabelY = kPowerValueY + 42.0f;
    static constexpr float kWetValueY = kWetLabelY + 24.0f;

    // Temporary race result banner shown after an action.
    static constexpr float kResultX = kControlPanelX + 100.0f;
    static constexpr float kResultY = kControlPanelY + 478.0f;
    static constexpr float kResultWidth = 280.0f;
    static constexpr float kResultHeight = 60.0f;
    static constexpr float kResultCenterX = kResultX + kResultWidth * 0.5f;
    static constexpr float kResultTextY = kResultY + 15.0f;

    // Right-side radio panel with race briefing text.
    static constexpr float kRadioPanelX = kControlPanelX + kControlPanelWidth + SceneLayout::kPanelGap;
    static constexpr float kRadioPanelY = kBoardPanelY + 248.0f;
    static constexpr float kRadioPanelWidth = SceneLayout::kWindowWidth - SceneLayout::kOuterMarginX - kRadioPanelX;
    static constexpr float kRadioPanelHeight = 356.0f;
    static constexpr float kRadioTitleX = kRadioPanelX + 28.0f;
    static constexpr float kRadioTitleY = kRadioPanelY + 24.0f;
    static constexpr float kRadioNameY = kRadioPanelY + 58.0f;
    static constexpr float kRadioBodyY = kRadioPanelY + 114.0f;
    static constexpr float kRadioFallbackY = kRadioPanelY + 72.0f;
    static constexpr float kRadioBodyWidth = kRadioPanelWidth - 56.0f;

    // Race action buttons on the right side of the screen.
    static constexpr float kStartRaceButtonX = kRadioPanelX;
    static constexpr float kStartRaceButtonY = kBoardPanelY;
    static constexpr float kStartRaceButtonWidth = kRadioPanelWidth;
    static constexpr float kStartRaceButtonHeight = 56.0f;
    static constexpr float kDriveButtonY = kStartRaceButtonY + kStartRaceButtonHeight + 18.0f;
    static constexpr float kDriveButtonGap = 16.0f;
    static constexpr float kDriveButtonWidth = (kRadioPanelWidth - kDriveButtonGap * 2.0f) / 3.0f;
    static constexpr float kDriveButtonHeight = 56.0f;
    static constexpr float kDriveAeroX = kRadioPanelX;
    static constexpr float kDrivePowerX = kDriveAeroX + kDriveButtonWidth + kDriveButtonGap;
    static constexpr float kDriveWetX = kDrivePowerX + kDriveButtonWidth + kDriveButtonGap;
    static constexpr float kLeaveRaceButtonX = kRadioPanelX;
    static constexpr float kLeaveRaceButtonY = kDriveButtonY + kDriveButtonHeight + 18.0f;
    static constexpr float kLeaveRaceButtonWidth = kRadioPanelWidth;
    static constexpr float kLeaveRaceButtonHeight = 56.0f;
    static constexpr float kBackButtonX = kRadioPanelX;
    static constexpr float kBackButtonY = kBoardPanelY + kBoardPanelHeight - 56.0f;
    static constexpr float kBackButtonWidth = kRadioPanelWidth;
    static constexpr float kBackButtonHeight = 56.0f;

    // Rectangle helper for the race list container.
    static sf::FloatRect board_panel_rect() {
        return make_rect(kBoardPanelX, kBoardPanelY, kBoardPanelWidth, kBoardPanelHeight);
    }

    // Rectangle helper for the control panel container.
    static sf::FloatRect control_panel_rect() {
        return make_rect(kControlPanelX, kControlPanelY, kControlPanelWidth, kControlPanelHeight);
    }

    // Rectangle helper for a race card by index in the vertical list.
    static sf::FloatRect race_card(const size_t index) {
        return make_rect(kRaceCardX, kRaceCardStartY + static_cast<float>(index) * kRaceCardStepY, kRaceCardWidth, kRaceCardHeight);
    }

    // Rectangle helper for the track map preview.
    static sf::FloatRect track_map_rect() {
        return make_rect(kTrackMapX, kTrackMapY, kTrackMapWidth, kTrackMapHeight);
    }

    // Rectangle helper for the race feedback banner.
    static sf::FloatRect result_rect() {
        return make_rect(kResultX, kResultY, kResultWidth, kResultHeight);
    }

    // Rectangle helper for the radio briefing container.
    static sf::FloatRect radio_panel_rect() {
        return make_rect(kRadioPanelX, kRadioPanelY, kRadioPanelWidth, kRadioPanelHeight);
    }

    // Rectangle helper for the button that starts the selected race.
    static sf::FloatRect start_race_button_rect() {
        return make_rect(kStartRaceButtonX, kStartRaceButtonY, kStartRaceButtonWidth, kStartRaceButtonHeight);
    }

    // Rectangle helper for the aero drive action button.
    static sf::FloatRect drive_aero_button_rect() {
        return make_rect(kDriveAeroX, kDriveButtonY, kDriveButtonWidth, kDriveButtonHeight);
    }

    // Rectangle helper for the power drive action button.
    static sf::FloatRect drive_power_button_rect() {
        return make_rect(kDrivePowerX, kDriveButtonY, kDriveButtonWidth, kDriveButtonHeight);
    }

    // Rectangle helper for the wet drive action button.
    static sf::FloatRect drive_wet_button_rect() {
        return make_rect(kDriveWetX, kDriveButtonY, kDriveButtonWidth, kDriveButtonHeight);
    }

    // Rectangle helper for the button that leaves the active race.
    static sf::FloatRect leave_race_button_rect() {
        return make_rect(kLeaveRaceButtonX, kLeaveRaceButtonY, kLeaveRaceButtonWidth, kLeaveRaceButtonHeight);
    }

    // Rectangle helper for the button that returns to the main menu.
    static sf::FloatRect back_button_rect() {
        return make_rect(kBackButtonX, kBackButtonY, kBackButtonWidth, kBackButtonHeight);
    }
};

}

#endif // RACE_LAYOUT_H
