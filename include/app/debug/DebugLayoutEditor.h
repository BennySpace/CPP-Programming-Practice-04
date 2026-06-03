#ifndef DEBUG_LAYOUT_EDITOR_H
#define DEBUG_LAYOUT_EDITOR_H

#include "ApplicationState.h"
#include <SFML/Graphics.hpp>
#include <optional>
#include <string>
#include <vector>

struct DebugEditableRect {
    std::string mName;
    sf::FloatRect mRect;
    bool mIsButton = false;
    std::optional<std::string> mParentName;
};

enum class DebugLayoutMode {
    panels,
    buttons
};

class DebugLayoutEditor {
public:
    void toggle();
    [[nodiscard]] bool enabled() const;
    void cycleMode();
    [[nodiscard]] DebugLayoutMode mode() const;

    void rebuild(ApplicationScreen pScreen, const std::vector<DebugEditableRect>& pRects);

    [[nodiscard]] std::optional<size_t> hitTest(sf::Vector2f pPoint) const;
    void select(std::optional<size_t> pIndex);

    void beginDrag(sf::Vector2f pMousePosition);
    void dragTo(sf::Vector2f pMousePosition);
    void endDrag();

    void nudgePosition(float pDx, float pDy);
    void resizeSelected(float pDw, float pDh);

    [[nodiscard]] std::optional<sf::FloatRect> rectOverride(const std::string& pName) const;
    void draw(sf::RenderWindow& pWindow) const;

private:
    void moveRectWithChildren(size_t pIndex, float pDx, float pDy);
    void moveChildrenRecursive(const std::string& pParentName, float pDx, float pDy);
    [[nodiscard]] DebugEditableRect* selectedRect();
    [[nodiscard]] const DebugEditableRect* selectedRect() const;

    bool mEnabled = false;
    ApplicationScreen mScreen = ApplicationScreen::main_menu;
    DebugLayoutMode mMode = DebugLayoutMode::panels;
    std::vector<DebugEditableRect> mRects;
    std::optional<size_t> mSelectedIndex;
    bool mDragging = false;
    sf::Vector2f mDragOffset{};
};

#endif // DEBUG_LAYOUT_EDITOR_H
