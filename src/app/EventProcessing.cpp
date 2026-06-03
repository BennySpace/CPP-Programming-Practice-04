#include "Application.h"

#include <optional>

void Application::processEvents() {
#ifndef NDEBUG
    if (mDebugLayoutEditor.enabled()) {
        rebuildDebugLayoutEditor();
    }
#endif

    while (const std::optional event = mWindow.pollEvent()) {
        if (event->is<sf::Event::Closed>()) {
            handleWindowClosed();
        } else if (const auto* mouseMoved = event->getIf<sf::Event::MouseMoved>()) {
            handleMouseMoved(*mouseMoved);
        } else if (const auto* mousePressed = event->getIf<sf::Event::MouseButtonPressed>()) {
            handleMouseButtonPressed(*mousePressed);
        } else if (const auto* mouseReleased = event->getIf<sf::Event::MouseButtonReleased>()) {
            handleMouseButtonReleased(*mouseReleased);
        } else if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>()) {
            handleKeyPressed(*keyPressed);
        }
    }
}

void Application::handleWindowClosed() {
    applyNavigation(app_navigation::exit_application());
}

void Application::handleMouseButtonPressed(const sf::Event::MouseButtonPressed& pEvent) {
#ifndef NDEBUG
    if (handleDebugMousePressed(pEvent)) {
        return;
    }
#endif

    if (pEvent.button == sf::Mouse::Button::Left) {
        handleMouseClick(mWindow.mapPixelToCoords(pEvent.position));
    }
}

void Application::handleMouseButtonReleased(const sf::Event::MouseButtonReleased& pEvent) {
#ifndef NDEBUG
    handleDebugMouseReleased(pEvent);
#else
    (void)pEvent;
#endif
}

void Application::handleMouseMoved(const sf::Event::MouseMoved& pEvent) {
#ifndef NDEBUG
    handleDebugMouseMoved(pEvent);
#else
    (void)pEvent;
#endif
}

void Application::handleKeyPressed(const sf::Event::KeyPressed& pEvent) {
#ifndef NDEBUG
    if (pEvent.code == sf::Keyboard::Key::F8) {
        mDebugLayoutEditor.toggle();
        rebuildDebugLayoutEditor();
        return;
    }

    if (mDebugLayoutEditor.enabled() && pEvent.code == sf::Keyboard::Key::Tab) {
        mDebugLayoutEditor.cycleMode();
        rebuildDebugLayoutEditor();
        return;
    }

    handleDebugKeyPressed(pEvent);
#endif

    if (pEvent.code == sf::Keyboard::Key::Escape) {
        applyNavigation(app_navigation::handle_escape(mUiState));
    }
}
