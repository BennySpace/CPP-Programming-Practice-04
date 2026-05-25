#ifndef SFML_UTILS_H
#define SFML_UTILS_H

#include "ApplicationState.h"
#include <algorithm>
#include <cctype>
#include <cstdint>

inline sf::FloatRect rect_xywh(const float x, const float y, const float width, const float height) {
    return {{x, y}, {width, height}};
}

inline sf::Vector2f rect_center(const sf::FloatRect& rect) {
    return {rect.position.x + rect.size.x * 0.5f, rect.position.y + rect.size.y * 0.5f};
}

inline bool rect_contains(const sf::FloatRect& rect, const sf::Vector2f& point) {
    return rect.contains(point);
}

inline sf::Color with_alpha(const sf::Color& color, const std::uint8_t alpha) {
    return sf::Color(color.r, color.g, color.b, alpha);
}

inline sf::Vector2f half_size(const sf::Vector2f& value) {
    return {value.x * 0.5f, value.y * 0.5f};
}

inline std::string to_upper_copy(const std::string& text) {
    std::string transformed = text;
    std::transform(transformed.begin(), transformed.end(), transformed.begin(), [](const unsigned char character) {
        return static_cast<char>(std::toupper(character));
    });
    return transformed;
}

inline UiButton make_button(
    const AppCommand action,
    const std::string& label,
    const sf::FloatRect& rect,
    const sf::Color& fill,
    const sf::Color& accent,
    const bool enabled) {
    UiButton result;
    result.mAction = action;
    result.mLabel = label;
    result.mRect = rect;
    result.mFill = fill;
    result.mAccent = accent;
    result.mEnabled = enabled;
    return result;
}

#endif // SFML_UTILS_H
