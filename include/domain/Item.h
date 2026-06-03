#ifndef ITEM_H
#define ITEM_H

#include "ItemType.h"
#include <string>
#include <utility>

struct Item {
    std::string mName;
    ItemType mType;
    int mValue;
    std::string mDescription;
    int mDurability;
    bool mIsBroken;
    bool mIsEquipped;

    Item(
        std::string pName,
        const ItemType pType,
        const int pValue,
        std::string pDescription = "",
        const int pDurability = 0,
        const bool pIsBroken = false,
        const bool pIsEquipped = false)
        : mName(std::move(pName)),
          mType(pType),
          mValue(pValue),
          mDescription(std::move(pDescription)),
          mDurability(pDurability),
          mIsBroken(pIsBroken),
          mIsEquipped(pIsEquipped) {}
};

#endif // ITEM_H
