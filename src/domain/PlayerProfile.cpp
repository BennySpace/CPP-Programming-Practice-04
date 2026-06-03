#include "PlayerProfile.h"
#include "DomainText.h"
#include "GameBalance.h"
#include "LootCatalog.h"
#include "PlayerSaveData.h"
#include <algorithm>

namespace {
size_t mod_slot_index(const ModType pModType) {
    switch (pModType) {
        case ModType::aero_wing:
            return 0;
        case ModType::high_power:
            return 1;
        case ModType::wet_grip:
            return 2;
    }

    return 0;
}

Item make_default_mod(const ModType pModType) {
    return Item(
        to_code(pModType),
        ItemType::equipment,
        game_balance::mod_cost(pModType),
        to_full_label(pModType),
        100,
        false,
        true);
}

std::array<Item, 3> make_default_mods() {
    return {
        make_default_mod(ModType::aero_wing),
        make_default_mod(ModType::high_power),
        make_default_mod(ModType::wet_grip)
    };
}

int clamp_to_non_negative(const int pValue) {
    return std::max(0, pValue);
}

int clamp_mod_durability(const int pValue) {
    return std::clamp(pValue, 0, 100);
}
}

PlayerProfile::PlayerProfile()
    : mMoney(game_balance::kStartingMoney),
      mFuel(game_balance::kStartingFuel),
      mGarageMods(make_default_mods()) {}

void PlayerProfile::resetProgress() {
    mMoney = game_balance::kStartingMoney;
    mFuel = game_balance::kStartingFuel;
    mInventory.clear();
    mGarageMods = make_default_mods();
    mMuseumCollection.clear();
    mMuseumRewards.clear();
}

int PlayerProfile::money() const {
    return mMoney;
}

int PlayerProfile::fuel() const {
    return mFuel;
}

void PlayerProfile::addMoney(int pAmount) {
    mMoney += pAmount;
}

void PlayerProfile::spendMoney(int pAmount) {
    mMoney = std::max(0, mMoney - pAmount);
}

void PlayerProfile::addFuel(int pAmount) {
    mFuel += pAmount;
}

void PlayerProfile::spendFuel() {
    if (mFuel > 0) {
        --mFuel;
    }
}

void PlayerProfile::addItem(const Item& pItem) {
    if (pItem.mType == ItemType::loot) {
        mInventory.push_back(pItem);
    }
}

bool PlayerProfile::hasMod(const ModType pModType) const {
    return !garageMod(pModType).mIsBroken;
}

bool PlayerProfile::hasBrokenMod(const ModType pModType) const {
    return garageMod(pModType).mIsBroken;
}

const Item& PlayerProfile::garageMod(const ModType pModType) const {
    return mGarageMods[mod_slot_index(pModType)];
}

const std::vector<Item>& PlayerProfile::inventory() const {
    return mInventory;
}

const std::vector<Item>& PlayerProfile::museumCollection() const {
    return mMuseumCollection;
}

const std::vector<int>& PlayerProfile::museumRewards() const {
    return mMuseumRewards;
}

std::vector<size_t> PlayerProfile::lootIndices() const {
    std::vector<size_t> indices;

    for (size_t index = 0; index < mInventory.size(); ++index) {
        if (mInventory[index].mType == ItemType::loot) {
            indices.push_back(index);
        }
    }

    return indices;
}

bool PlayerProfile::isGameOver() const {
    return mMoney <= 0 && mFuel <= 0;
}

bool PlayerProfile::applyModWear(const ModType pModType, const int pWearAmount, int& pDurability, bool& pBroken) {
    Item& mod = mGarageMods[mod_slot_index(pModType)];
    if (mod.mIsBroken) {
        return false;
    }

    mod.mDurability = std::max(0, mod.mDurability - pWearAmount);
    mod.mIsBroken = mod.mDurability <= 0;
    pDurability = mod.mDurability;
    pBroken = mod.mIsBroken;
    return true;
}

std::optional<Item> PlayerProfile::removeInventoryItem(const size_t pIndex) {
    if (pIndex >= mInventory.size()) {
        return std::nullopt;
    }

    Item removedItem = mInventory[pIndex];
    mInventory.erase(mInventory.begin() + static_cast<long long>(pIndex));
    return removedItem;
}

PlayerCommandResult PlayerProfile::sellItem(size_t pIndex) {
    if (pIndex >= mInventory.size() || mInventory[pIndex].mType != ItemType::loot) {
        return {false, domain_text::kSellFailedTitle, domain_text::sellItem_invalid()};
    }

    const Item soldItem = mInventory[pIndex];
    addMoney(soldItem.mValue);
    (void)removeInventoryItem(pIndex);

    return {
        true,
        domain_text::kLootSoldTitle,
        domain_text::loot_sold(soldItem.mName, soldItem.mValue)
    };
}

PlayerCommandResult PlayerProfile::donateToMuseum(size_t pIndex) {
    if (pIndex >= mInventory.size() || mInventory[pIndex].mType != ItemType::loot) {
        return {false, domain_text::kDonationFailedTitle, domain_text::donate_only_loot()};
    }

    for (const auto& exhibit : mMuseumCollection) {
        if (exhibit.mName == mInventory[pIndex].mName) {
            return {false, domain_text::kAlreadyDisplayedTitle, domain_text::already_displayed()};
        }
    }

    Item exhibit = mInventory[pIndex];
    exhibit.mDescription = lootDescription(exhibit.mName);
    mMuseumCollection.push_back(exhibit);
    (void)removeInventoryItem(pIndex);

    std::string rewardMessage = domain_text::exhibit_displayed(exhibit.mName);
    const size_t exhibitCount = mMuseumCollection.size();

    if (exhibitCount >= static_cast<size_t>(game_balance::kMuseumMilestones[2])
        && std::find(mMuseumRewards.begin(), mMuseumRewards.end(), game_balance::kMuseumMilestones[2]) == mMuseumRewards.end()) {
        addMoney(game_balance::kMuseumRewards[2]);
        mMuseumRewards.push_back(game_balance::kMuseumMilestones[2]);
        rewardMessage += " " + domain_text::museum_milestone_reward(game_balance::kMuseumRewards[2]);
    } else if (exhibitCount >= static_cast<size_t>(game_balance::kMuseumMilestones[1])
        && std::find(mMuseumRewards.begin(), mMuseumRewards.end(), game_balance::kMuseumMilestones[1]) == mMuseumRewards.end()) {
        addMoney(game_balance::kMuseumRewards[1]);
        mMuseumRewards.push_back(game_balance::kMuseumMilestones[1]);
        rewardMessage += " " + domain_text::museum_milestone_reward(game_balance::kMuseumRewards[1]);
    } else if (exhibitCount >= static_cast<size_t>(game_balance::kMuseumMilestones[0])
        && std::find(mMuseumRewards.begin(), mMuseumRewards.end(), game_balance::kMuseumMilestones[0]) == mMuseumRewards.end()) {
        addMoney(game_balance::kMuseumRewards[0]);
        mMuseumRewards.push_back(game_balance::kMuseumMilestones[0]);
        rewardMessage += " " + domain_text::museum_milestone_reward(game_balance::kMuseumRewards[0]);
    }

    return {true, domain_text::kNewExhibitTitle, rewardMessage};
}

PlayerCommandResult PlayerProfile::repairMod(const ModType pModType, const int pCost) {
    Item& mod = mGarageMods[mod_slot_index(pModType)];

    if (!mod.mIsBroken) {
        return {false, domain_text::kRepairFailedTitle, domain_text::repair_already_working()};
    }

    if (money() < pCost) {
        return {false, domain_text::kNotEnoughMoneyTitle, domain_text::repair_requires_credits(pCost)};
    }

    spendMoney(pCost);
    mod.mIsBroken = false;
    mod.mDurability = game_balance::kRepairRestoreDurability;

    return {
        true,
        domain_text::kRepairCompleteTitle,
        domain_text::mod_repaired_for_next_stint(modLabel(pModType), mod.mDurability)
    };
}

std::optional<ModType> PlayerProfile::normalizeModName(const std::string& pName) {
    return try_mod_type_from_code(pName);
}

std::string PlayerProfile::modLabel(const ModType pModType) {
    return to_full_label(pModType);
}

std::string PlayerProfile::lootDescription(const std::string& pLootName) {
    return loot_catalog::description_for(pLootName);
}

PlayerSaveData PlayerProfile::toSaveData() const {
    return {
        mMoney,
        mFuel,
        mInventory,
        std::vector<Item>(mGarageMods.begin(), mGarageMods.end()),
        mMuseumCollection,
        mMuseumRewards
    };
}

void PlayerProfile::applySaveData(const PlayerSaveData& pSaveData) {
    mMoney = clamp_to_non_negative(pSaveData.mMoney);
    mFuel = clamp_to_non_negative(pSaveData.mFuel);
    mInventory.clear();
    for (const auto& item : pSaveData.mInventory) {
        if (item.mType == ItemType::loot) {
            Item normalizedItem = item;
            normalizedItem.mValue = clamp_to_non_negative(normalizedItem.mValue);
            mInventory.push_back(normalizedItem);
        }
    }

    mGarageMods = make_default_mods();
    for (const auto& savedMod : pSaveData.mGarageMods) {
        const auto modType = normalizeModName(savedMod.mName);
        if (!modType.has_value()) {
            continue;
        }

        Item normalizedMod = savedMod;
        normalizedMod.mName = to_code(*modType);
        normalizedMod.mDescription = to_full_label(*modType);
        normalizedMod.mType = ItemType::equipment;
        normalizedMod.mValue = game_balance::mod_cost(*modType);
        normalizedMod.mDurability = clamp_mod_durability(normalizedMod.mDurability);
        normalizedMod.mIsBroken = normalizedMod.mDurability <= 0;
        normalizedMod.mIsEquipped = true;
        mGarageMods[mod_slot_index(*modType)] = normalizedMod;
    }

    mMuseumCollection.clear();
    for (const auto& exhibit : pSaveData.mMuseumCollection) {
        if (exhibit.mType != ItemType::loot) {
            continue;
        }

        Item normalizedExhibit = exhibit;
        normalizedExhibit.mValue = clamp_to_non_negative(normalizedExhibit.mValue);
        normalizedExhibit.mDescription = lootDescription(normalizedExhibit.mName);
        mMuseumCollection.push_back(normalizedExhibit);
    }

    mMuseumRewards.clear();
    for (const int milestone : pSaveData.mMuseumRewards) {
        if (std::find(game_balance::kMuseumMilestones.begin(), game_balance::kMuseumMilestones.end(), milestone)
            == game_balance::kMuseumMilestones.end()) {
            continue;
        }

        if (std::find(mMuseumRewards.begin(), mMuseumRewards.end(), milestone) == mMuseumRewards.end()) {
            mMuseumRewards.push_back(milestone);
        }
    }
}
