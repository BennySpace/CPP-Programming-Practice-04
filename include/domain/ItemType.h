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

#endif // ITEM_TYPE_H
