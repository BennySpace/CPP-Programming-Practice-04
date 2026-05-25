#include "Application.h"
#include "sfml/SfmlUtils.h"

void Application::handleMouseClick(const sf::Vector2f mousePosition) {
    for (const auto& currentHotspot : mScreenInteractions.mHotspots) {
        if (rect_contains(currentHotspot.mRect, mousePosition)) {
            applySelectionHotspot(currentHotspot);
            return;
        }
    }

    for (const auto& currentButton : mScreenInteractions.mButtons) {
        if (currentButton.mEnabled && rect_contains(currentButton.mRect, mousePosition)) {
            executeCommand(currentButton.mAction);
            return;
        }
    }
}
