#ifndef PLAYER_SAVE_DATA_H
#define PLAYER_SAVE_DATA_H

#include "Item.h"
#include <vector>

struct PlayerSaveData {
    int mMoney = 0;
    int mFuel = 0;
    std::vector<Item> mInventory;
    std::vector<Item> mGarageMods;
    std::vector<Item> mMuseumCollection;
    std::vector<int> mMuseumRewards;
    int mActiveRaceIndex = -1;
};

#endif // PLAYER_SAVE_DATA_H
