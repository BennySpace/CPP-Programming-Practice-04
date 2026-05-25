#include "assets/AssetManager.h"
#include "assets/AssetCatalog.h"
#include "LootCatalog.h"
#include "PlayerProfile.h"
#include <string>

namespace {
struct ModTextureRule {
    ModType mModType;
    size_t mTextureIndex;
};

template <size_t N, typename Loader>
void load_texture_group(
    std::array<sf::Texture, N>& pTextures,
    std::array<bool, N>& pLoadedFlags,
    const std::array<const char*, 2>& pBasePaths,
    const std::array<const char*, N>& pFileNames,
    const Loader& pLoader) {
    for (size_t index = 0; index < pFileNames.size(); ++index) {
        pLoadedFlags[index] = pLoader(pTextures[index], pBasePaths, pFileNames[index]);
    }
}

template <size_t N, typename Loader, typename NameAccessor>
void load_catalog_texture_group(
    std::array<sf::Texture, N>& pTextures,
    std::array<bool, N>& pLoadedFlags,
    const std::array<const char*, 2>& pBasePaths,
    const Loader& pLoader,
    const NameAccessor& pNameAccessor) {
    for (size_t index = 0; index < pTextures.size(); ++index) {
        pLoadedFlags[index] = pLoader(pTextures[index], pBasePaths, pNameAccessor(index));
    }
}

constexpr std::array<const char*, 2> kTrackPreviewBasePaths = {
    "assets/circuits/previews/",
    "./assets/circuits/previews/"
};

constexpr std::array<const char*, 2> kTrackMapBasePaths = {
    "assets/circuits/maps/",
    "./assets/circuits/maps/"
};

constexpr std::array<const char*, 2> kItemBasePaths = {
    "assets/items/",
    "./assets/items/"
};

constexpr std::array<ModTextureRule, 3> kEquipmentTextureRules = {{
    {ModType::aero_wing, 4},
    {ModType::high_power, 1},
    {ModType::wet_grip, 2}
}};

constexpr std::array<const char*, 5> kItemPhotoNames = {
    "podium_cap.jpg",
    "powertrain_part.jpg",
    "tire_compound.jpg",
    "trophy_medal.jpg",
    "aero_wing_part.jpg"
};
}

AssetManager::AssetManager() {
    load_track_previews();
    load_track_maps();
    load_items();
}

const sf::Texture* AssetManager::trackPreviewTexture(const size_t pIndex) const {
    if (pIndex >= mTrackPreviewTextures.size() || !mTrackPreviewTextureLoaded[pIndex]) {
        return nullptr;
    }

    return &mTrackPreviewTextures[pIndex];
}

const sf::Texture* AssetManager::trackMapTexture(const size_t pIndex) const {
    if (pIndex >= mTrackMapTextures.size() || !mTrackMapTextureLoaded[pIndex]) {
        return nullptr;
    }

    return &mTrackMapTextures[pIndex];
}

const sf::Texture* AssetManager::itemTexture(const size_t pIndex) const {
    if (pIndex >= mItemTextures.size() || !mItemTextureLoaded[pIndex]) {
        return nullptr;
    }

    return &mItemTextures[pIndex];
}

const sf::Texture* AssetManager::itemTexture(const Item& pItem) const {
    return itemTexture(resolve_item_texture_index(pItem));
}

bool AssetManager::load_texture_from_candidates(
    sf::Texture& pTexture,
    const std::array<const char*, 2>& pBasePaths,
    const char* pFileName) {
    for (const char* currentBasePath : pBasePaths) {
        if (pTexture.loadFromFile(std::string(currentBasePath) + pFileName)) {
            return true;
        }
    }

    return false;
}

size_t AssetManager::resolve_item_texture_index(const Item& pItem) const {
    if (const auto* definition = loot_catalog::find_definition(pItem.mName); definition != nullptr) {
        return definition->mTextureIndex;
    }

    if (pItem.mType == ItemType::equipment) {
        const auto equipmentType = PlayerProfile::normalizeModName(pItem.mName);
        if (!equipmentType.has_value()) {
            return 0;
        }

        for (const auto& currentRule : kEquipmentTextureRules) {
            if (*equipmentType == currentRule.mModType) {
                return currentRule.mTextureIndex;
            }
        }
    }

    return 0;
}

void AssetManager::load_track_previews() {
    load_catalog_texture_group(
        mTrackPreviewTextures,
        mTrackPreviewTextureLoaded,
        kTrackPreviewBasePaths,
        load_texture_from_candidates,
        [](const size_t index) {
            return app_asset_catalog::track_visual(index).mPreviewFile;
        });
}

void AssetManager::load_track_maps() {
    load_catalog_texture_group(
        mTrackMapTextures,
        mTrackMapTextureLoaded,
        kTrackMapBasePaths,
        load_texture_from_candidates,
        [](const size_t index) {
            return app_asset_catalog::track_visual(index).mMapFile;
        });
}

void AssetManager::load_items() {
    load_texture_group(mItemTextures, mItemTextureLoaded, kItemBasePaths, kItemPhotoNames, load_texture_from_candidates);
}
