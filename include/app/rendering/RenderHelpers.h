#ifndef RENDER_HELPERS_H
#define RENDER_HELPERS_H

#include "BitmapText.h"
#include <SFML/Graphics.hpp>
#include <cstddef>
#include <string>

namespace app_render_helpers {
std::string display_track_name(size_t pIndex);

inline void draw_text_if_not_empty(
    sf::RenderTarget& pTarget,
    const std::string& pText,
    const sf::Vector2f pPosition,
    const float pScale,
    const sf::Color& pColor,
    const bool pCentered = false) {
    if (!pText.empty()) {
        bitmap_text::draw_text(pTarget, pText, pPosition, pScale, pColor, pCentered);
    }
}
}

#endif // RENDER_HELPERS_H
