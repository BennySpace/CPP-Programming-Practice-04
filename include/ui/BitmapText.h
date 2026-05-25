#ifndef BITMAP_TEXT_H
#define BITMAP_TEXT_H

#include <SFML/Graphics.hpp>
#include <string>

namespace bitmap_text {
float measure_text(const std::string& pText, float pScale);
void draw_text(
    sf::RenderTarget& pTarget,
    const std::string& pText,
    sf::Vector2f pPosition,
    float pScale,
    const sf::Color& pColor,
    bool pCentered = false);
}

#endif // BITMAP_TEXT_H
