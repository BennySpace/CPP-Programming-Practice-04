#ifndef ASSET_MANAGER_H
#define ASSET_MANAGER_H

#include "Item.h"
#include <SFML/Graphics.hpp>
#include <array>
#include <cstddef>

class AssetManager {
public:
    AssetManager();

    [[nodiscard]] const sf::Texture* trackPreviewTexture(size_t pIndex) const;
    [[nodiscard]] const sf::Texture* trackMapTexture(size_t pIndex) const;
    [[nodiscard]] const sf::Texture* itemTexture(size_t pIndex) const;
    [[nodiscard]] const sf::Texture* itemTexture(const Item& pItem) const;

private:
    std::array<sf::Texture, 3> mTrackPreviewTextures;
    std::array<bool, 3> mTrackPreviewTextureLoaded = {false, false, false};
    std::array<sf::Texture, 3> mTrackMapTextures;
    std::array<bool, 3> mTrackMapTextureLoaded = {false, false, false};
    std::array<sf::Texture, 5> mItemTextures;
    std::array<bool, 5> mItemTextureLoaded = {false, false, false, false, false};

    static bool load_texture_from_candidates(
        sf::Texture& pTexture,
        const std::array<const char*, 2>& pBasePaths,
        const char* pFileName);
    [[nodiscard]] size_t resolve_item_texture_index(const Item& pItem) const;

    void load_track_previews();
    void load_track_maps();
    void load_items();
};

#endif // ASSET_MANAGER_H
