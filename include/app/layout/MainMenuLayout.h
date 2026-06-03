#ifndef MAIN_MENU_LAYOUT_H
#define MAIN_MENU_LAYOUT_H

#include "layout/Layout.h"

namespace app_layout {
struct MainMenuLayout {
    // High-level offsets for moving grouped main menu blocks together.
    static constexpr float kHeroGroupOffsetX = 0.0f;
    static constexpr float kHeroGroupOffsetY = 0.0f;
    static constexpr float kTrackRowOffsetX = 0.0f;
    static constexpr float kTrackRowOffsetY = 0.0f;
    static constexpr float kActionRowOffsetX = 0.0f;
    static constexpr float kActionRowOffsetY = 0.0f;

    // Main menu content panel and title area.
    static constexpr float kPanelX = SceneLayout::kOuterMarginX;
    static constexpr float kPanelY = SceneLayout::kOuterMarginTop;
    static constexpr float kPanelWidth = SceneLayout::kWindowWidth - SceneLayout::kOuterMarginX * 2.0f;
    static constexpr float kPanelHeight = 448.0f;
    static constexpr float kTitleX = SceneLayout::kWindowWidth * 0.5f + kHeroGroupOffsetX;
    static constexpr float kTitleY = kPanelY + 34.0f + kHeroGroupOffsetY;
    static constexpr float kFooterX = kPanelX + 44.0f;
    static constexpr float kFooterY = kPanelY + kPanelHeight - 46.0f;

    // Track preview card row inside the main panel.
    static constexpr float kTrackCardX = kPanelX + 60.0f + kTrackRowOffsetX;
    static constexpr float kTrackCardY = kPanelY + 118.0f + kTrackRowOffsetY;
    static constexpr float kTrackCardWidth = 380.0f;
    static constexpr float kTrackCardHeight = 248.0f;
    static constexpr float kTrackCardStepX = 410.0f;
    static constexpr float kTrackPhotoInsetX = 20.0f;
    static constexpr float kTrackPhotoInsetY = 20.0f;
    static constexpr float kTrackPhotoWidth = 340.0f;
    static constexpr float kTrackPhotoHeight = 152.0f;
    static constexpr float kTrackLabelCenterOffsetX = kTrackCardWidth * 0.5f;
    static constexpr float kTrackLabelY = kTrackCardY + kTrackCardHeight - 46.0f;
    static constexpr float kTrackPhotoPlaceholderY = 365.0f;

    // Decorative start lights above the track preview row.
    static constexpr float kStartLightX = kPanelX + 70.0f + kHeroGroupOffsetX;
    static constexpr float kStartLightY = kPanelY + 32.0f + kHeroGroupOffsetY;
    static constexpr float kStartLightStepX = 48.0f;
    static constexpr float kStartLightRadius = 16.0f;

    // New game confirmation modal and its text block.
    static constexpr float kConfirmModalX = 420.0f;
    static constexpr float kConfirmModalY = 300.0f;
    static constexpr float kConfirmModalWidth = 600.0f;
    static constexpr float kConfirmModalHeight = 260.0f;
    static constexpr float kConfirmTitleCenterX = 720.0f;
    static constexpr float kConfirmTitleY = 336.0f;
    static constexpr float kConfirmTextX = 470.0f;
    static constexpr float kConfirmTextY = 390.0f;
    static constexpr float kConfirmTextWidth = 500.0f;

    // Main menu action buttons share one size and are centered as a row.
    static constexpr float kActionButtonY = kPanelY + kPanelHeight + SceneLayout::kActionRowGap + kActionRowOffsetY;
    static constexpr float kActionButtonWidth = 228.0f;
    static constexpr float kActionButtonHeight = 76.0f;
    static constexpr float kActionButtonGap = 18.0f;
    static constexpr float kActionButtonRowWidth = kActionButtonWidth * 5.0f + kActionButtonGap * 4.0f;
    static constexpr float kActionButtonRowStartX = (SceneLayout::kWindowWidth - kActionButtonRowWidth) * 0.5f + kActionRowOffsetX;

    static constexpr float kGoRaceButtonX = kActionButtonRowStartX;
    static constexpr float kGoRaceButtonY = kActionButtonY;
    static constexpr float kGoRaceButtonWidth = kActionButtonWidth;
    static constexpr float kGoRaceButtonHeight = kActionButtonHeight;
    static constexpr float kGoGarageButtonX = kGoRaceButtonX + kActionButtonWidth + kActionButtonGap;
    static constexpr float kGoGarageButtonY = kActionButtonY;
    static constexpr float kGoGarageButtonWidth = kActionButtonWidth;
    static constexpr float kGoGarageButtonHeight = kActionButtonHeight;
    static constexpr float kGoMuseumButtonX = kGoGarageButtonX + kActionButtonWidth + kActionButtonGap;
    static constexpr float kGoMuseumButtonY = kActionButtonY;
    static constexpr float kGoMuseumButtonWidth = kActionButtonWidth;
    static constexpr float kGoMuseumButtonHeight = kActionButtonHeight;
    static constexpr float kNewGameButtonX = kGoMuseumButtonX + kActionButtonWidth + kActionButtonGap;
    static constexpr float kNewGameButtonY = kActionButtonY;
    static constexpr float kNewGameButtonWidth = kActionButtonWidth;
    static constexpr float kNewGameButtonHeight = kActionButtonHeight;
    static constexpr float kExitButtonX = kNewGameButtonX + kActionButtonWidth + kActionButtonGap;
    static constexpr float kExitButtonY = kActionButtonY;
    static constexpr float kExitButtonWidth = kActionButtonWidth;
    static constexpr float kExitButtonHeight = kActionButtonHeight;

    static constexpr float kConfirmYesButtonX = 515.0f;
    static constexpr float kConfirmYesButtonY = 450.0f;
    static constexpr float kConfirmYesButtonWidth = 190.0f;
    static constexpr float kConfirmYesButtonHeight = 66.0f;
    static constexpr float kConfirmCancelButtonX = 735.0f;
    static constexpr float kConfirmCancelButtonY = 450.0f;
    static constexpr float kConfirmCancelButtonWidth = 190.0f;
    static constexpr float kConfirmCancelButtonHeight = 66.0f;

    // Rectangle helper for the main hero panel.
    static sf::FloatRect panel_rect() {
        return make_rect(kPanelX, kPanelY, kPanelWidth, kPanelHeight);
    }

    // Rectangle helper for the new game confirmation modal.
    static sf::FloatRect confirm_modal_rect() {
        return make_rect(kConfirmModalX, kConfirmModalY, kConfirmModalWidth, kConfirmModalHeight);
    }

    // Rectangle helper for a track preview card by index.
    static sf::FloatRect track_card(const size_t index) {
        return make_rect(kTrackCardX + static_cast<float>(index) * kTrackCardStepX, kTrackCardY, kTrackCardWidth, kTrackCardHeight);
    }

    // Rectangle helper for the preview image inside a track card.
    static sf::FloatRect track_photo(const size_t index) {
        return make_rect(kTrackCardX + static_cast<float>(index) * kTrackCardStepX + kTrackPhotoInsetX, kTrackCardY + kTrackPhotoInsetY, kTrackPhotoWidth, kTrackPhotoHeight);
    }

    // Rectangle helper for the button that opens the race hub.
    static sf::FloatRect go_race_button_rect() {
        return make_rect(kGoRaceButtonX, kGoRaceButtonY, kGoRaceButtonWidth, kGoRaceButtonHeight);
    }

    // Rectangle helper for the button that opens the garage.
    static sf::FloatRect go_garage_button_rect() {
        return make_rect(kGoGarageButtonX, kGoGarageButtonY, kGoGarageButtonWidth, kGoGarageButtonHeight);
    }

    // Rectangle helper for the button that opens the museum.
    static sf::FloatRect go_museum_button_rect() {
        return make_rect(kGoMuseumButtonX, kGoMuseumButtonY, kGoMuseumButtonWidth, kGoMuseumButtonHeight);
    }

    // Rectangle helper for the new game button.
    static sf::FloatRect new_game_button_rect() {
        return make_rect(kNewGameButtonX, kNewGameButtonY, kNewGameButtonWidth, kNewGameButtonHeight);
    }

    // Rectangle helper for the exit application button.
    static sf::FloatRect exit_button_rect() {
        return make_rect(kExitButtonX, kExitButtonY, kExitButtonWidth, kExitButtonHeight);
    }

    // Rectangle helper for the confirmation acceptance button.
    static sf::FloatRect confirm_yes_button_rect() {
        return make_rect(kConfirmYesButtonX, kConfirmYesButtonY, kConfirmYesButtonWidth, kConfirmYesButtonHeight);
    }

    // Rectangle helper for the confirmation cancel button.
    static sf::FloatRect confirm_cancel_button_rect() {
        return make_rect(kConfirmCancelButtonX, kConfirmCancelButtonY, kConfirmCancelButtonWidth, kConfirmCancelButtonHeight);
    }
};

}

#endif // MAIN_MENU_LAYOUT_H
