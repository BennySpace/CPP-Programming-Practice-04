#ifndef APPLICATION_H
#define APPLICATION_H

#include "ApplicationState.h"
#include "assets/AssetManager.h"
#include "GameSession.h"
#include <SFML/Graphics.hpp>
#include <string>
#include <vector>

class Application {
public:
    Application();
    void run();

private:
    GameSession mGame;
    sf::RenderWindow mWindow;
    ApplicationState mUiState;
    std::vector<UiButton> mButtons;
    AssetManager mAssets;

    void processEvents();
    void update(float pDeltaTime);
    void render();
    void rebuildButtons();
    void executeCommand(AppCommand pAction);
    void handleMouseClick(sf::Vector2f pMousePosition);
    void showBanner(const std::string& pTitle, const std::string& pMessage, bool pSuccess);
    void showBanner(const std::string& pTitle, bool pSuccess);
    void showRaceFeedback(const std::string& pLabel, bool pSuccess);

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
    [[nodiscard]] const sf::Texture* trackPreviewTexture(size_t pIndex) const;
    [[nodiscard]] const sf::Texture* trackMapTexture(size_t pIndex) const;
    [[nodiscard]] const sf::Texture* itemTexture(const Item& pItem) const;

    [[nodiscard]] std::string modStatusText(ModType pModType) const;
    [[nodiscard]] sf::Color modStatusColor(ModType pModType) const;
};

#endif // APPLICATION_H
