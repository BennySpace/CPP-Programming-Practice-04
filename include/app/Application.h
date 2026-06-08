#ifndef APPLICATION_H
#define APPLICATION_H

#include "ApplicationState.h"
#include "assets/AssetManager.h"
#include "GameSession.h"
#include "screens/ScreenInteractions.h"
#include "screens/ScreenNavigation.h"
#ifndef NDEBUG
#include "debug/DebugLayoutEditor.h"
#endif
#include <SFML/Graphics.hpp>
#include <string>

struct CommandExecutionResult;

class Application {
public:
    Application();
    void run();

private:
    GameSession mGame;
    sf::RenderWindow mWindow;
    ApplicationState mUiState;
    ScreenInteractions mScreenInteractions;
    AssetManager mAssets;
#ifndef NDEBUG
    DebugLayoutEditor mDebugLayoutEditor;
#endif

    void processEvents();
    void update(float pDeltaTime);
    void render();
    void syncPagedUiState();
    void refreshScreenInteractions();
    void handleWindowClosed();
    void handleMouseButtonPressed(const sf::Event::MouseButtonPressed& pEvent);
    void handleMouseButtonReleased(const sf::Event::MouseButtonReleased& pEvent);
    void handleMouseMoved(const sf::Event::MouseMoved& pEvent);
    void handleKeyPressed(const sf::Event::KeyPressed& pEvent);
    void applyCommandExecutionResult(const CommandExecutionResult& pResult);
    void executeCommand(AppCommand pAction);
    void handleMouseClick(sf::Vector2f pMousePosition);
    void applyNavigation(const NavigationCommandResult& pResult);
    void applySelectionHotspot(const ScreenSelectionHotspot& pHotspot);
    void showPendingSessionAlert();
    void showBanner(const std::string& pTitle, const std::string& pMessage, bool pSuccess);
    void showBanner(const std::string& pTitle, bool pSuccess);
    void showRaceFeedback(const std::string& pLabel, bool pSuccess);
#ifndef NDEBUG
    void rebuildDebugLayoutEditor();
    void handleDebugKeyPressed(const sf::Event::KeyPressed& pEvent);
    [[nodiscard]] bool handleDebugMousePressed(const sf::Event::MouseButtonPressed& pEvent);
    void handleDebugMouseReleased(const sf::Event::MouseButtonReleased& pEvent);
    void handleDebugMouseMoved(const sf::Event::MouseMoved& pEvent);
#endif
    [[nodiscard]] sf::FloatRect debugRectOverride(const std::string& pName, const sf::FloatRect& pFallbackRect) const;

    void drawBackground();
    void drawStatusBar();
    void drawMainMenu();
    void drawNewGameConfirmation();
    void drawRaceHub();
    void drawGarage();
    void drawMuseum();
    void drawButtons();

    void drawPanel(const sf::FloatRect& pRect, const sf::Color& pFill, const sf::Color& pOutline, float pOutlineThickness = 2.0f);
    void drawPhotoFit(const sf::Texture& pTexture, const sf::FloatRect& pRect);
    void drawPhotoPlaceholder(const sf::FloatRect& pRect, float pTextScale = 2.4f);
    void drawItemCard(const Item& pItem, const sf::FloatRect& pRect, bool pSelected, bool pMuseumStyle);
    void drawWrapped(const std::string& pText, sf::Vector2f pPosition, float pScale, float pWidth, const sf::Color& pColor);
    void drawWrappedClamped(
        const std::string& pText,
        sf::Vector2f pPosition,
        float pScale,
        float pWidth,
        size_t pMaxLines,
        const sf::Color& pColor);
    void drawTextRightAligned(
        const std::string& pText,
        sf::Vector2f pPosition,
        float pScale,
        const sf::Color& pColor);
    [[nodiscard]] const sf::Texture* trackPreviewTexture(size_t pIndex) const;
    [[nodiscard]] const sf::Texture* trackMapTexture(size_t pIndex) const;
    [[nodiscard]] const sf::Texture* itemTexture(const Item& pItem) const;

    [[nodiscard]] std::string modStatusText(ModType pModType) const;
    [[nodiscard]] sf::Color modStatusColor(ModType pModType) const;
};

#endif // APPLICATION_H
