#ifndef ITEM_TYPE_H
#define ITEM_TYPE_H

#include <string>

enum class ItemType {
    loot,
    equipment
};

[[nodiscard]] inline std::string to_string(const ItemType pItemType) {
    return pItemType == ItemType::equipment ? "equipment" : "loot";
}

[[nodiscard]] inline ItemType item_type_from_string(const std::string& pValue) {
    return pValue == "equipment" ? ItemType::equipment : ItemType::loot;
}

#endif // ITEM_TYPE_H
