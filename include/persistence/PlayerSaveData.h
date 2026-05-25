#ifndef PLAYER_SAVE_DATA_H
#define PLAYER_SAVE_DATA_H

#include "Item.h"
#include <vector>

struct PlayerSaveData {
    int mMoney = 0;
    int mFuel = 0;
    std::vector<Item> mInventory;
    std::vector<Item> mMuseumCollection;
    std::vector<int> mMuseumRewards;
};

#endif // PLAYER_SAVE_DATA_H
