#include "Application.h"
#include "layout/Layouts.h"
#include "platform/WindowIcon.h"
#include "sfml/SfmlUtils.h"
#include "text/UiText.h"
#include <algorithm>

namespace {
void tick_timer(float& pTimer, const float pDeltaTime) {
    pTimer = std::max(0.0f, pTimer - pDeltaTime);
}
}

#ifndef NDEBUG
#include "debug/DebugLayoutRegistry.h"

namespace {
constexpr float kDebugNudgeStep = 10.0f;
constexpr float kDebugFineNudgeStep = 1.0f;
}
#endif

Application::Application()
    : mWindow(
        sf::VideoMode({1440u, 900u}),
        app_text::kWindowTitle,
        sf::Style::Titlebar | sf::Style::Close,
        sf::State::Windowed) {
    platform::apply_window_icon(mWindow);
    mWindow.setFramerateLimit(60);
    showBanner(app_text::kBannerGarageOnlineTitle, true);
    showPendingSessionAlert();
}

void Application::run() {
    sf::Clock frameClock;
    while (mWindow.isOpen()) {
        processEvents();
        update(frameClock.restart().asSeconds());
        render();
    }
}

void Application::update(const float deltaTime) {
    if (mUiState.mBanner.mTimer > 0.0f) {
        tick_timer(mUiState.mBanner.mTimer, deltaTime);
    }

    if (mUiState.mRaceFeedback.mTimer > 0.0f) {
        tick_timer(mUiState.mRaceFeedback.mTimer, deltaTime);
    }
}

void Application::render() {
    refreshScreenInteractions();
#ifndef NDEBUG
    rebuildDebugLayoutEditor();
#endif
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
#ifndef NDEBUG
    mDebugLayoutEditor.draw(mWindow);
#endif
    mWindow.display();
}

void Application::syncPagedUiState() {
    const auto& inventory = mGame.player().inventory();
    const auto& museumCollection = mGame.player().museumCollection();
    const std::vector<size_t> garageLootIndices = mGame.player().lootIndices();
    const std::vector<size_t> lootIndices = mGame.player().lootIndices();

    app_state::clamp_page(mUiState.mGarageInventoryPage, garageLootIndices.size(), app_layout::GarageLayout::kVisibleInventoryCardCount);
    app_state::clamp_page(mUiState.mMuseumExhibitPage, museumCollection.size(), app_layout::MuseumLayout::kVisibleExhibitCardCount);
    app_state::clamp_page(mUiState.mMuseumDropPage, lootIndices.size(), app_layout::MuseumLayout::kVisibleDropCardCount);

    if (!app_state::has_selected_inventory(mUiState, inventory.size())) {
        app_state::clear_selected_inventory(mUiState);
    }
}

void Application::refreshScreenInteractions() {
    syncPagedUiState();
    mScreenInteractions = build_screen_interactions(
        mGame,
        mUiState,
        [&](const std::string& pName, const sf::FloatRect& pFallbackRect) {
#ifndef NDEBUG
            return mDebugLayoutEditor.rectOverride(pName).value_or(pFallbackRect);
#else
            return pFallbackRect;
#endif
        });
}

void Application::applyNavigation(const NavigationCommandResult& result) {
    if (result.mLeaveRace) {
        mGame.leaveRace();
    }

    if (result.mShowBanner) {
        showBanner(result.mBannerTitle, result.mBannerMessage, result.mBannerSuccess);
    }

    if (result.mCloseWindow) {
        (void)mGame.save();
        mWindow.close();
    }

    showPendingSessionAlert();
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

void Application::showPendingSessionAlert() {
    const std::optional<SessionAlert> alert = mGame.consumePendingAlert();
    if (alert.has_value()) {
        showBanner(alert->mTitle, alert->mMessage, alert->mSuccess);
    }
}

void Application::showRaceFeedback(const std::string& label, const bool success) {
    mUiState.mRaceFeedback.mLabel = label;
    mUiState.mRaceFeedback.mSuccess = success;
    mUiState.mRaceFeedback.mTimer = 1.35f;
}

#ifndef NDEBUG
void Application::rebuildDebugLayoutEditor() {
    mDebugLayoutEditor.rebuild(mUiState.mScreen, build_debug_layout_rects(mGame, mUiState, mDebugLayoutEditor));
}

void Application::handleDebugKeyPressed(const sf::Event::KeyPressed& pEvent) {
    if (!mDebugLayoutEditor.enabled()) {
        return;
    }

    const float step = pEvent.shift ? kDebugFineNudgeStep : kDebugNudgeStep;

    switch (pEvent.code) {
        case sf::Keyboard::Key::W:
            mDebugLayoutEditor.nudgePosition(0.0f, -step);
            break;
        case sf::Keyboard::Key::S:
            mDebugLayoutEditor.nudgePosition(0.0f, step);
            break;
        case sf::Keyboard::Key::A:
            mDebugLayoutEditor.nudgePosition(-step, 0.0f);
            break;
        case sf::Keyboard::Key::D:
            mDebugLayoutEditor.nudgePosition(step, 0.0f);
            break;
        case sf::Keyboard::Key::Left:
            mDebugLayoutEditor.resizeSelected(-step, 0.0f);
            break;
        case sf::Keyboard::Key::Right:
            mDebugLayoutEditor.resizeSelected(step, 0.0f);
            break;
        case sf::Keyboard::Key::Up:
            mDebugLayoutEditor.resizeSelected(0.0f, -step);
            break;
        case sf::Keyboard::Key::Down:
            mDebugLayoutEditor.resizeSelected(0.0f, step);
            break;
        default:
            break;
    }
}

bool Application::handleDebugMousePressed(const sf::Event::MouseButtonPressed& pEvent) {
    if (!mDebugLayoutEditor.enabled() || pEvent.button != sf::Mouse::Button::Left) {
        return false;
    }

    const sf::Vector2f mousePosition = mWindow.mapPixelToCoords(pEvent.position);
    const std::optional<size_t> hitIndex = mDebugLayoutEditor.hitTest(mousePosition);
    if (!hitIndex.has_value()) {
        mDebugLayoutEditor.select(std::nullopt);
        return true;
    }

    mDebugLayoutEditor.select(hitIndex);
    mDebugLayoutEditor.beginDrag(mousePosition);
    return true;
}

void Application::handleDebugMouseReleased(const sf::Event::MouseButtonReleased& pEvent) {
    if (!mDebugLayoutEditor.enabled() || pEvent.button != sf::Mouse::Button::Left) {
        return;
    }

    mDebugLayoutEditor.endDrag();
}

void Application::handleDebugMouseMoved(const sf::Event::MouseMoved& pEvent) {
    if (!mDebugLayoutEditor.enabled()) {
        return;
    }

    mDebugLayoutEditor.dragTo(mWindow.mapPixelToCoords(pEvent.position));
}

sf::FloatRect Application::debugRectOverride(const std::string& pName, const sf::FloatRect& pFallbackRect) const {
    return mDebugLayoutEditor.rectOverride(pName).value_or(pFallbackRect);
}
#else
sf::FloatRect Application::debugRectOverride(const std::string&, const sf::FloatRect& pFallbackRect) const {
    return pFallbackRect;
}
#endif

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
    const Item& mod = mGame.player().garageMod(currentMod);
    if (mod.mIsBroken) {
        return app_text::format_mod_broken(to_code(currentMod));
    }

    return app_text::format_mod_durability(to_code(currentMod), mod.mDurability);
}

sf::Color Application::modStatusColor(const ModType currentMod) const {
    return mGame.player().garageMod(currentMod).mIsBroken ? sf::Color(255, 156, 156) : sf::Color(181, 243, 190);
}
