#ifndef PLAYER_PROFILE_H
#define PLAYER_PROFILE_H

#include "Item.h"
#include "ModType.h"
#include "PlayerSaveData.h"
#include <array>
#include <optional>
#include <string>
#include <vector>

struct PlayerCommandResult {
    bool mSuccess = false;
    std::string mTitle;
    std::string mMessage;
};

class PlayerProfile {
private:
    int mMoney;
    int mFuel;
    std::vector<Item> mInventory;
    std::array<Item, 3> mGarageMods;
    std::vector<Item> mMuseumCollection;
    std::vector<int> mMuseumRewards;

public:
    PlayerProfile();
    void resetProgress();

    [[nodiscard]] int money() const;
    [[nodiscard]] int fuel() const;
    void addMoney(int pAmount);
    void spendMoney(int pAmount);
    void addFuel(int pAmount);
    void spendFuel();

    void addItem(const Item& pItem);
    [[nodiscard]] bool hasMod(ModType pModType) const;
    [[nodiscard]] bool hasBrokenMod(ModType pModType) const;
    [[nodiscard]] const Item& garageMod(ModType pModType) const;
    [[nodiscard]] const std::vector<Item>& inventory() const;
    [[nodiscard]] const std::vector<Item>& museumCollection() const;
    [[nodiscard]] const std::vector<int>& museumRewards() const;

    [[nodiscard]] std::vector<size_t> lootIndices() const;
    [[nodiscard]] bool isGameOver() const;

    bool applyModWear(ModType pModType, int pWearAmount, int& pDurability, bool& pBroken);
    [[nodiscard]] std::optional<Item> removeInventoryItem(size_t pIndex);
    PlayerCommandResult sellItem(size_t pIndex);
    PlayerCommandResult donateToMuseum(size_t pIndex);
    PlayerCommandResult repairMod(ModType pModType, int pCost);

    [[nodiscard]] static std::optional<ModType> normalizeModName(const std::string& pName);
    [[nodiscard]] static std::string modLabel(ModType pModType);
    [[nodiscard]] static std::string lootDescription(const std::string& pLootName);

    [[nodiscard]] PlayerSaveData toSaveData() const;
    void applySaveData(const PlayerSaveData& pSaveData);
};

#endif // PLAYER_PROFILE_H
