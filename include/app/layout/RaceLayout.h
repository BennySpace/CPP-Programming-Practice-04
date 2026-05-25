#ifndef RACE_LAYOUT_H
#define RACE_LAYOUT_H

#include "layout/Layout.h"

namespace app_layout {
struct RaceLayout {
    static constexpr float kBoardGroupOffsetX = 0.0f;
    static constexpr float kBoardGroupOffsetY = 2.0f;
    static constexpr float kControlGroupOffsetX = 0.0f;
    static constexpr float kControlGroupOffsetY = 2.0f;
    static constexpr float kActionGroupOffsetX = 0.0f;
    static constexpr float kActionGroupOffsetY = -4.0f;

    static constexpr float kBoardPanelX = 110.0f + kBoardGroupOffsetX;
    static constexpr float kBoardPanelY = 150.0f + kBoardGroupOffsetY;
    static constexpr float kBoardPanelWidth = 380.0f;
    static constexpr float kBoardPanelHeight = 680.0f;
    static constexpr float kBoardTitleX = 138.0f + kBoardGroupOffsetX;
    static constexpr float kBoardTitleY = 178.0f + kBoardGroupOffsetY;

    static constexpr float kRaceCardX = 120.0f + kBoardGroupOffsetX;
    static constexpr float kRaceCardStartY = 158.0f + kBoardGroupOffsetY;
    static constexpr float kRaceCardWidth = 360.0f;
    static constexpr float kRaceCardHeight = 140.0f;
    static constexpr float kRaceCardStepY = 170.0f;
    static constexpr float kRaceCardTextX = 132.0f + kBoardGroupOffsetX;
    static constexpr float kRaceCardTitleOffsetY = 25.0f;
    static constexpr float kRaceCardTypeOffsetY = 70.0f;
    static constexpr float kRaceCardFeeOffsetY = 104.0f;

    static constexpr float kControlPanelX = 520.0f + kControlGroupOffsetX;
    static constexpr float kControlPanelY = 150.0f + kControlGroupOffsetY;
    static constexpr float kControlPanelWidth = 470.0f;
    static constexpr float kControlPanelHeight = 680.0f;
    static constexpr float kControlTitleX = 560.0f + kControlGroupOffsetX;
    static constexpr float kControlTitleY = 178.0f + kControlGroupOffsetY;

    static constexpr float kTrackMapX = 545.0f + kControlGroupOffsetX;
    static constexpr float kTrackMapY = 205.0f + kControlGroupOffsetY;
    static constexpr float kTrackMapWidth = 420.0f;
    static constexpr float kTrackMapHeight = 300.0f;

    static constexpr float kModTextX = 568.0f + kControlGroupOffsetX;
    static constexpr float kAeroLabelY = 592.0f + kControlGroupOffsetY;
    static constexpr float kAeroValueY = 612.0f + kControlGroupOffsetY;
    static constexpr float kPowerLabelY = 642.0f + kControlGroupOffsetY;
    static constexpr float kPowerValueY = 662.0f + kControlGroupOffsetY;
    static constexpr float kWetLabelY = 692.0f + kControlGroupOffsetY;
    static constexpr float kWetValueY = 712.0f + kControlGroupOffsetY;

    static constexpr float kResultX = 625.0f + kControlGroupOffsetX;
    static constexpr float kResultY = 508.0f + kControlGroupOffsetY;
    static constexpr float kResultWidth = 260.0f;
    static constexpr float kResultHeight = 54.0f;
    static constexpr float kResultCenterX = 755.0f + kControlGroupOffsetX;
    static constexpr float kResultTextY = 523.0f + kControlGroupOffsetY;

    static constexpr float kRadioPanelX = 1020.0f + kActionGroupOffsetX;
    static constexpr float kRadioPanelY = 450.0f + kActionGroupOffsetY;
    static constexpr float kRadioPanelWidth = 310.0f;
    static constexpr float kRadioPanelHeight = 250.0f;
    static constexpr float kRadioTitleX = 1048.0f + kActionGroupOffsetX;
    static constexpr float kRadioTitleY = 478.0f + kActionGroupOffsetY;
    static constexpr float kRadioNameY = 490.0f + kActionGroupOffsetY;
    static constexpr float kRadioBodyY = 525.0f + kActionGroupOffsetY;
    static constexpr float kRadioFallbackY = 490.0f + kActionGroupOffsetY;
    static constexpr float kRadioBodyWidth = 250.0f;

    static constexpr float kStartRaceButtonX = 1020.0f + kActionGroupOffsetX;
    static constexpr float kStartRaceButtonY = 180.0f + kActionGroupOffsetY;
    static constexpr float kStartRaceButtonWidth = 310.0f;
    static constexpr float kStartRaceButtonHeight = 64.0f;
    static constexpr float kDriveButtonY = 270.0f + kActionGroupOffsetY;
    static constexpr float kDriveButtonWidth = 94.0f;
    static constexpr float kDriveButtonHeight = 64.0f;
    static constexpr float kDriveAeroX = 1020.0f + kActionGroupOffsetX;
    static constexpr float kDrivePowerX = 1128.0f + kActionGroupOffsetX;
    static constexpr float kDriveWetX = 1236.0f + kActionGroupOffsetX;
    static constexpr float kLeaveRaceButtonX = 1020.0f + kActionGroupOffsetX;
    static constexpr float kLeaveRaceButtonY = 360.0f + kActionGroupOffsetY;
    static constexpr float kLeaveRaceButtonWidth = 310.0f;
    static constexpr float kLeaveRaceButtonHeight = 64.0f;
    static constexpr float kBackButtonX = 1020.0f + kActionGroupOffsetX;
    static constexpr float kBackButtonY = 770.0f + kActionGroupOffsetY;
    static constexpr float kBackButtonWidth = 310.0f;
    static constexpr float kBackButtonHeight = 60.0f;

    static sf::FloatRect board_panel_rect() {
        return make_rect(kBoardPanelX, kBoardPanelY, kBoardPanelWidth, kBoardPanelHeight);
    }

    static sf::FloatRect control_panel_rect() {
        return make_rect(kControlPanelX, kControlPanelY, kControlPanelWidth, kControlPanelHeight);
    }

    static sf::FloatRect race_card(const size_t index) {
        return make_rect(kRaceCardX, kRaceCardStartY + static_cast<float>(index) * kRaceCardStepY, kRaceCardWidth, kRaceCardHeight);
    }

    static sf::FloatRect track_map_rect() {
        return make_rect(kTrackMapX, kTrackMapY, kTrackMapWidth, kTrackMapHeight);
    }

    static sf::FloatRect result_rect() {
        return make_rect(kResultX, kResultY, kResultWidth, kResultHeight);
    }

    static sf::FloatRect radio_panel_rect() {
        return make_rect(kRadioPanelX, kRadioPanelY, kRadioPanelWidth, kRadioPanelHeight);
    }

    static sf::FloatRect start_race_button_rect() {
        return make_rect(kStartRaceButtonX, kStartRaceButtonY, kStartRaceButtonWidth, kStartRaceButtonHeight);
    }

    static sf::FloatRect drive_aero_button_rect() {
        return make_rect(kDriveAeroX, kDriveButtonY, kDriveButtonWidth, kDriveButtonHeight);
    }

    static sf::FloatRect drive_power_button_rect() {
        return make_rect(kDrivePowerX, kDriveButtonY, kDriveButtonWidth, kDriveButtonHeight);
    }

    static sf::FloatRect drive_wet_button_rect() {
        return make_rect(kDriveWetX, kDriveButtonY, kDriveButtonWidth, kDriveButtonHeight);
    }

    static sf::FloatRect leave_race_button_rect() {
        return make_rect(kLeaveRaceButtonX, kLeaveRaceButtonY, kLeaveRaceButtonWidth, kLeaveRaceButtonHeight);
    }

    static sf::FloatRect back_button_rect() {
        return make_rect(kBackButtonX, kBackButtonY, kBackButtonWidth, kBackButtonHeight);
    }
};

}

#endif // RACE_LAYOUT_H
