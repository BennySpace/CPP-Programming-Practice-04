#include "PlayerSaveCodec.h"
#include "ItemType.h"
#include "ModType.h"
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
    if (!pInput.is_object()
        || !pInput.contains("name") || !pInput.at("name").is_string()
        || !pInput.contains("type") || !pInput.at("type").is_string()
        || !pInput.contains("value") || !pInput.at("value").is_number_integer()
        || !pInput.contains("description") || !pInput.at("description").is_string()) {
        return false;
    }

    const auto type = parse_item_type(pInput.at("type").get<std::string>());
    if (!type.has_value()) {
        return false;
    }

    std::string loadedName = pInput.at("name").get<std::string>();
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
        clamp_to_non_negative(pInput.at("value").get<int>()),
        pInput.at("description").get<std::string>());

    if (*type == ItemType::equipment) {
        if (!pInput.contains("durability") || !pInput.at("durability").is_number_integer()
            || !pInput.contains("isBroken") || !pInput.at("isBroken").is_boolean()
            || !pInput.contains("isEquipped") || !pInput.at("isEquipped").is_boolean()) {
            return false;
        }

        pOutput.mDurability = clamp_mod_durability(pInput.at("durability").get<int>());
        pOutput.mIsBroken = pOutput.mDurability <= 0 || pInput.at("isBroken").get<bool>();
        pOutput.mIsEquipped = pInput.at("isEquipped").get<bool>();
    }

    return true;
}
}

bool PlayerSaveCodec::encode(const PlayerSaveData& pSaveData, json& pOutput) {
    pOutput = json::object();
    pOutput["money"] = pSaveData.mMoney;
    pOutput["fuel"] = pSaveData.mFuel;
    pOutput["activeRaceIndex"] = pSaveData.mActiveRaceIndex;
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
    if (!pInput.is_object()
        || !pInput.contains("money") || !pInput.at("money").is_number_integer()
        || !pInput.contains("fuel") || !pInput.at("fuel").is_number_integer()
        || !pInput.contains("activeRaceIndex") || !pInput.at("activeRaceIndex").is_number_integer()
        || !pInput.contains("inventory") || !pInput.at("inventory").is_array()
        || !pInput.contains("mods") || !pInput.at("mods").is_array()
        || !pInput.contains("museum") || !pInput.at("museum").is_array()
        || !pInput.contains("museumRewards") || !pInput.at("museumRewards").is_array()) {
        return false;
    }

    PlayerSaveData loadedData;
    loadedData.mMoney = clamp_to_non_negative(pInput.at("money").get<int>());
    loadedData.mFuel = clamp_to_non_negative(pInput.at("fuel").get<int>());
    loadedData.mActiveRaceIndex = std::max(-1, pInput.at("activeRaceIndex").get<int>());

    for (const auto& itemJson : pInput.at("inventory")) {
        Item loadedItem("", ItemType::loot, 0);
        if (!decode_item(itemJson, loadedItem) || loadedItem.mType != ItemType::loot) {
            return false;
        }

        loadedData.mInventory.push_back(loadedItem);
    }

    for (const auto& itemJson : pInput.at("mods")) {
        Item loadedMod("", ItemType::loot, 0);
        if (!decode_item(itemJson, loadedMod) || loadedMod.mType != ItemType::equipment) {
            return false;
        }

        loadedData.mGarageMods.push_back(loadedMod);
    }

    for (const auto& exhibitJson : pInput.at("museum")) {
        Item loadedExhibit("", ItemType::loot, 0);
        if (!decode_item(exhibitJson, loadedExhibit) || loadedExhibit.mType != ItemType::loot) {
            return false;
        }

        loadedData.mMuseumCollection.push_back(loadedExhibit);
    }

    for (const auto& rewardJson : pInput.at("museumRewards")) {
        if (!rewardJson.is_number_integer()) {
            return false;
        }

        loadedData.mMuseumRewards.push_back(rewardJson.get<int>());
    }

    pOutput = loadedData;
    return true;
}
