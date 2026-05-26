#include "Application.h"
#include "platform/WindowIcon.h"
#include "sfml/SfmlUtils.h"
#include "text/UiText.h"
#include <algorithm>
#include <optional>

Application::Application()
    : mWindow(
        sf::VideoMode({1440u, 900u}),
        app_text::kWindowTitle,
        sf::Style::Titlebar | sf::Style::Close,
        sf::State::Windowed) {
    platform::apply_window_icon(mWindow);
    mWindow.setFramerateLimit(60);
    showBanner(app_text::kBannerGarageOnlineTitle, true);
}

void Application::run() {
    sf::Clock frameClock;
    while (mWindow.isOpen()) {
        processEvents();
        update(frameClock.restart().asSeconds());
        render();
    }
}

void Application::processEvents() {
    while (const std::optional event = mWindow.pollEvent()) {
        if (event->is<sf::Event::Closed>()) {
            applyNavigation(app_navigation::exit_application());
            continue;
        }

        if (const auto* mousePressed = event->getIf<sf::Event::MouseButtonPressed>()) {
            if (mousePressed->button == sf::Mouse::Button::Left) {
                handleMouseClick(mWindow.mapPixelToCoords(mousePressed->position));
            }
        }

        if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>()) {
            if (keyPressed->code == sf::Keyboard::Key::Escape) {
                applyNavigation(app_navigation::handle_escape(mUiState));
            }
        }
    }
}

void Application::update(const float deltaTime) {
    if (mUiState.mBanner.mTimer > 0.0f) {
        mUiState.mBanner.mTimer = std::max(0.0f, mUiState.mBanner.mTimer - deltaTime);
    }

    if (mUiState.mRaceFeedback.mTimer > 0.0f) {
        mUiState.mRaceFeedback.mTimer = std::max(0.0f, mUiState.mRaceFeedback.mTimer - deltaTime);
    }
}

void Application::render() {
    refreshScreenInteractions();
    mWindow.clear();
    drawBackground();
    drawStatusBar();

    switch (mUiState.mScreen) {
        case ApplicationScreen::main_menu:
            drawMainMenu();
            break;
        case ApplicationScreen::race_hub:
            drawRaceHub();
            break;
        case ApplicationScreen::garage:
            drawGarage();
            break;
        case ApplicationScreen::museum:
            drawMuseum();
            break;
    }

    if (mUiState.mConfirmingNewGame) {
        drawNewGameConfirmation();
    }

    drawButtons();
    mWindow.display();
}

void Application::refreshScreenInteractions() {
    mScreenInteractions = build_screen_interactions(mGame, mUiState);
}

void Application::applyNavigation(const NavigationCommandResult& result) {
    if (result.mLeaveRace) {
        mGame.leaveRace();
    }

    if (result.mShowBanner) {
        showBanner(result.mBannerTitle, result.mBannerMessage, result.mBannerSuccess);
    }

    if (result.mCloseWindow) {
        mGame.save();
        mWindow.close();
    }
}

void Application::applySelectionHotspot(const ScreenSelectionHotspot& hotspot) {
    switch (hotspot.mKind) {
        case ScreenSelectionKind::race:
            mUiState.mSelectedRace = hotspot.mValue;
            break;
        case ScreenSelectionKind::inventory:
            mUiState.mSelectedInventoryIndex = hotspot.mValue;
            break;
    }

    showBanner(hotspot.mBannerTitle, hotspot.mBannerMessage, hotspot.mBannerSuccess);
}

void Application::showBanner(const std::string& title, const std::string& message, const bool success) {
    mUiState.mBanner.mTitle = title;
    mUiState.mBanner.mMessage = message;
    mUiState.mBanner.mSuccess = success;
    mUiState.mBanner.mTimer = 5.0f;
}

void Application::showBanner(const std::string& title, const bool success) {
    showBanner(title, "", success);
}

void Application::showRaceFeedback(const std::string& label, const bool success) {
    mUiState.mRaceFeedback.mLabel = label;
    mUiState.mRaceFeedback.mSuccess = success;
    mUiState.mRaceFeedback.mTimer = 1.35f;
}

const sf::Texture* Application::trackPreviewTexture(const size_t pIndex) const {
    return mAssets.trackPreviewTexture(pIndex);
}

const sf::Texture* Application::trackMapTexture(const size_t pIndex) const {
    return mAssets.trackMapTexture(pIndex);
}

const sf::Texture* Application::itemTexture(const Item& currentItem) const {
    return mAssets.itemTexture(currentItem);
}

std::string Application::modStatusText(const ModType currentMod) const {
    for (const auto& inventoryItem : mGame.player().inventory()) {
        const auto inventoryModType = PlayerProfile::normalizeModName(inventoryItem.mName);
        if (inventoryItem.mType == ItemType::equipment
            && inventoryModType.has_value()
            && *inventoryModType == currentMod) {
            if (inventoryItem.mIsBroken) {
                return app_text::format_mod_broken(to_code(currentMod));
            }

            return app_text::format_mod_durability(to_code(currentMod), inventoryItem.mDurability);
        }
    }

    return app_text::kNotFittedLabel;
}

sf::Color Application::modStatusColor(const ModType currentMod) const {
    for (const auto& inventoryItem : mGame.player().inventory()) {
        const auto inventoryModType = PlayerProfile::normalizeModName(inventoryItem.mName);
        if (inventoryItem.mType == ItemType::equipment
            && inventoryModType.has_value()
            && *inventoryModType == currentMod) {
            return inventoryItem.mIsBroken ? sf::Color(255, 156, 156) : sf::Color(181, 243, 190);
        }
    }

    return sf::Color(199, 205, 219);
}
