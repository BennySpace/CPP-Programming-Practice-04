#include "PlayerSaveCodec.h"
#include "GameBalance.h"
#include "ItemType.h"
#include "ModType.h"
#include "PlayerProfile.h"
#include <algorithm>
#include <optional>
#include <string>
#include <vector>

using json = nlohmann::json;

namespace {
int clamp_to_non_negative(const int pValue) {
    return std::max(0, pValue);
}

int clamp_mod_durability(const int pValue) {
    return std::clamp(pValue, 0, 100);
}

std::optional<ItemType> parse_item_type(const std::string& pValue) {
    if (pValue == "loot") {
        return ItemType::loot;
    }

    if (pValue == "equipment") {
        return ItemType::equipment;
    }

    return std::nullopt;
}

bool encode_item(const Item& pItem, json& pOutput) {
    std::string savedName = pItem.mName;
    if (pItem.mType == ItemType::equipment) {
        const auto modType = try_mod_type_from_code(pItem.mName);
        if (!modType.has_value()) {
            return false;
        }

        savedName = to_code(*modType);
    }

    pOutput = {
        {"name", savedName},
        {"type", to_string(pItem.mType)},
        {"value", pItem.mValue},
        {"description", pItem.mDescription}
    };

    if (pItem.mType == ItemType::equipment) {
        pOutput["durability"] = pItem.mDurability;
        pOutput["isBroken"] = pItem.mIsBroken;
        pOutput["isEquipped"] = pItem.mIsEquipped;
    }

    return true;
}

bool decode_item(const json& pInput, Item& pOutput) {
    const auto type = parse_item_type(pInput.value("type", ""));
    if (!type.has_value()) {
        return false;
    }

    std::string loadedName = pInput.value("name", "");
    if (*type == ItemType::equipment) {
        const auto modType = try_mod_type_from_code(loadedName);
        if (!modType.has_value()) {
            return false;
        }

        loadedName = to_code(*modType);
    }

    pOutput = Item(
        loadedName,
        *type,
        clamp_to_non_negative(pInput.value("value", 0)),
        pInput.value("description", ""));

    if (*type == ItemType::equipment) {
        pOutput.mDurability = clamp_mod_durability(pInput.value("durability", 100));
        pOutput.mIsBroken = pOutput.mDurability <= 0 || pInput.value("isBroken", false);
        pOutput.mIsEquipped = pInput.value("isEquipped", false);
    }

    return true;
}
}

bool PlayerSaveCodec::encode(const PlayerSaveData& pSaveData, json& pOutput) {
    pOutput = json::object();
    pOutput["money"] = pSaveData.mMoney;
    pOutput["fuel"] = pSaveData.mFuel;
    pOutput["inventory"] = json::array();

    for (const auto& inventoryItem : pSaveData.mInventory) {
        json itemJson;
        if (!encode_item(inventoryItem, itemJson)) {
            return false;
        }

        pOutput["inventory"].push_back(itemJson);
    }

    pOutput["mods"] = json::array();
    for (const auto& mod : pSaveData.mGarageMods) {
        json itemJson;
        if (!encode_item(mod, itemJson)) {
            return false;
        }

        pOutput["mods"].push_back(itemJson);
    }

    pOutput["museum"] = json::array();
    for (const auto& exhibit : pSaveData.mMuseumCollection) {
        pOutput["museum"].push_back({
            {"name", exhibit.mName},
            {"type", to_string(exhibit.mType)},
            {"value", exhibit.mValue},
            {"description", exhibit.mDescription}
        });
    }

    pOutput["museumRewards"] = pSaveData.mMuseumRewards;
    return true;
}

bool PlayerSaveCodec::decode(const json& pInput, PlayerSaveData& pOutput) {
    PlayerSaveData loadedData;
    loadedData.mMoney = clamp_to_non_negative(pInput.value("money", game_balance::kStartingMoney));
    loadedData.mFuel = clamp_to_non_negative(pInput.value("fuel", game_balance::kStartingFuel));

    for (const auto& itemJson : pInput.value("inventory", json::array())) {
        Item loadedItem("", ItemType::loot, 0);
        if (!decode_item(itemJson, loadedItem)) {
            return false;
        }

        loadedData.mInventory.push_back(loadedItem);
    }

    for (const auto& itemJson : pInput.value("mods", json::array())) {
        Item loadedMod("", ItemType::loot, 0);
        if (!decode_item(itemJson, loadedMod)) {
            return false;
        }

        loadedData.mGarageMods.push_back(loadedMod);
    }

    for (const auto& exhibitJson : pInput.value("museum", json::array())) {
        const auto type = parse_item_type(exhibitJson.value("type", ""));
        if (!type.has_value()) {
            return false;
        }

        loadedData.mMuseumCollection.push_back(Item(
            exhibitJson.value("name", ""),
            *type,
            clamp_to_non_negative(exhibitJson.value("value", 0)),
            exhibitJson.value("description", PlayerProfile::lootDescription(exhibitJson.value("name", "")))));
    }

    loadedData.mMuseumRewards = pInput.value("museumRewards", std::vector<int>{});
    pOutput = loadedData;
    return true;
}
