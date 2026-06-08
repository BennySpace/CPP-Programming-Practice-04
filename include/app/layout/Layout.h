#ifndef APP_LAYOUT_SHARED_H
#define APP_LAYOUT_SHARED_H

#include <SFML/Graphics.hpp>
#include <cstddef>

namespace app_layout {
// Builds a rectangle from absolute position and size values.
inline sf::FloatRect make_rect(const float x, const float y, const float width, const float height) {
    return {{x, y}, {width, height}};
}

// Moves an existing rectangle without changing its size.
inline sf::FloatRect offset_rect(const sf::FloatRect& pRect, const float pOffsetX, const float pOffsetY) {
    return {{
        pRect.position.x + pOffsetX,
        pRect.position.y + pOffsetY
    }, pRect.size};
}

// Places repeated UI rectangles on a simple row/column grid.
inline sf::FloatRect grid_rect(
    const sf::FloatRect& pFirstRect,
    const size_t pIndex,
    const size_t pColumnCount,
    const float pStepX,
    const float pStepY) {
    const float column = static_cast<float>(pIndex % pColumnCount);
    const float row = static_cast<float>(pIndex / pColumnCount);
    return offset_rect(pFirstRect, column * pStepX, row * pStepY);
}

struct WidgetLayout {
    // Accent strip height for reusable framed panels.
    static constexpr float kPanelAccentBarHeight = 8.0f;

    // Vertical alignment factor for the "no photo" placeholder label.
    static constexpr float kPhotoPlaceholderBaselineFactor = 4.0f;

    // Decorative stripe and image area inside reusable item cards.
    static constexpr float kItemCardStripeInsetX = 10.0f;
    static constexpr float kItemCardStripeY = 14.0f;
    static constexpr float kItemCardStripeHeight = 6.0f;
    static constexpr float kItemCardPhotoInsetX = 18.0f;
    static constexpr float kItemCardPhotoInsetY = 14.0f;
    static constexpr float kItemCardPhotoInsetWidth = 36.0f;
    static constexpr float kItemCardBottomInset = 72.0f;

    // Text and meta-information anchors inside reusable item cards.
    static constexpr float kItemCardTextInsetX = 12.0f;
    static constexpr float kItemCardTextWidthInset = 24.0f;
    static constexpr float kItemCardEquipmentNameOffsetY = 56.0f;
    static constexpr float kItemCardLootNameOffsetY = 60.0f;
    static constexpr float kItemCardMetaOffsetY = 22.0f;

    // Vertical offset for centered button captions.
    static constexpr float kButtonLabelOffsetY = 22.0f;
};

struct SceneLayout {
    // Base application window size.
    static constexpr float kWindowWidth = 1440.0f;
    static constexpr float kWindowHeight = 900.0f;

    // Shared outer rhythm for all main screens below the status bar.
    static constexpr float kOuterMarginX = 60.0f;
    static constexpr float kOuterMarginTop = 156.0f;
    static constexpr float kOuterMarginBottom = 90.0f;
    static constexpr float kPanelGap = 30.0f;
    static constexpr float kSectionGap = 20.0f;
    static constexpr float kActionRowGap = 24.0f;

    // Full-screen asphalt background.
    static constexpr float kAsphaltWidth = 1440.0f;
    static constexpr float kAsphaltHeight = 900.0f;

    // Repeating grain bands over the asphalt backdrop.
    static constexpr int kGrainCount = 16;
    static constexpr float kGrainWidth = 1440.0f;
    static constexpr float kGrainHeight = 24.0f;
    static constexpr float kGrainStepY = 58.0f;

    // Pit lane strip near the bottom edge of the scene.
    static constexpr float kPitLaneX = 0.0f;
    static constexpr float kPitLaneY = 814.0f;
    static constexpr float kPitLaneWidth = 1440.0f;
    static constexpr float kPitLaneHeight = 86.0f;

    // White dash markers drawn across the pit lane.
    static constexpr int kDashCount = 18;
    static constexpr float kDashX = 55.0f;
    static constexpr float kDashY = 858.0f;
    static constexpr float kDashWidth = 46.0f;
    static constexpr float kDashHeight = 8.0f;
    static constexpr float kDashStepX = 78.0f;

    // Red-white curb pattern near the upper part of the scene.
    static constexpr int kCurbCount = 21;
    static constexpr float kCurbX = 40.0f;
    static constexpr float kCurbY = 136.0f;
    static constexpr float kCurbWidth = 32.0f;
    static constexpr float kCurbHeight = 14.0f;
    static constexpr float kCurbStepX = 64.0f;

    // Ambient glow circles layered over the background.
    static constexpr float kPrimaryGlowRadius = 240.0f;
    static constexpr float kPrimaryGlowX = 1020.0f;
    static constexpr float kPrimaryGlowY = -80.0f;
    static constexpr float kSecondaryGlowRadius = 190.0f;
    static constexpr float kSecondaryGlowX = -40.0f;
    static constexpr float kSecondaryGlowY = 610.0f;

    // Full-screen flash shown for race feedback.
    static constexpr float kFeedbackFlashWidth = 1440.0f;
    static constexpr float kFeedbackFlashHeight = 900.0f;
    static constexpr float kFeedbackFlashX = 0.0f;
    static constexpr float kFeedbackFlashY = 0.0f;
};

struct StatusBarLayout {
    // Outer frame of the top status bar.
    static constexpr float kPanelX = 42.0f;
    static constexpr float kPanelY = 24.0f;
    static constexpr float kPanelWidth = 1356.0f;
    static constexpr float kPanelHeight = 112.0f;

    // App title area on the left side of the status bar.
    static constexpr float kTitleX = 72.0f;
    static constexpr float kTitleY = 48.0f;
    static constexpr float kSubtitleX = 74.0f;
    static constexpr float kSubtitleY = 91.0f;

    // Player resource counters in the middle of the status bar.
    static constexpr float kCounterRightX = 944.0f;
    static constexpr float kCreditsY = 48.0f;
    static constexpr float kFuelY = 82.0f;

    // Notification banner area on the right side of the status bar.
    static constexpr float kBannerTitleX = 962.0f;
    static constexpr float kBannerTitleY = 62.0f;
    static constexpr float kBannerTextX = 962.0f;
    static constexpr float kBannerTextY = 88.0f;
    static constexpr float kBannerTextWidth = 386.0f;

    // Rectangle helper for the status bar container.
    static sf::FloatRect panel_rect() {
        return make_rect(kPanelX, kPanelY, kPanelWidth, kPanelHeight);
    }
};

}

#endif // APP_LAYOUT_SHARED_H
