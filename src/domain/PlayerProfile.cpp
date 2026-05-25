#include "PlayerProfile.h"
#include "GameBalance.h"
#include "DomainText.h"
#include "LootCatalog.h"
#include "PlayerSaveData.h"
#include <algorithm>

namespace {
Item make_default_mod(const ModType pModType) {
    return Item(
        to_code(pModType),
        ItemType::equipment,
        pModType == ModType::aero_wing
            ? game_balance::kAeroModCost
            : (pModType == ModType::high_power ? game_balance::kHighPowerModCost : game_balance::kWetGripModCost),
        to_full_label(pModType),
        100,
        false);
}

std::vector<Item> make_default_inventory() {
    return {
        make_default_mod(ModType::aero_wing),
        make_default_mod(ModType::high_power),
        make_default_mod(ModType::wet_grip)
    };
}
}

PlayerProfile::PlayerProfile() : mMoney(game_balance::kStartingMoney), mFuel(game_balance::kStartingFuel) {
    mInventory = make_default_inventory();
}

void PlayerProfile::resetProgress() {
    mMoney = game_balance::kStartingMoney;
    mFuel = game_balance::kStartingFuel;
    mInventory = make_default_inventory();
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
    mInventory.push_back(pItem);
}

bool PlayerProfile::hasMod(const ModType pModType) const {
    for (const auto& inventoryItem : mInventory) {
        const auto inventoryModType = normalizeModName(inventoryItem.mName);
        if (inventoryItem.mType == ItemType::equipment
            && inventoryModType.has_value()
            && *inventoryModType == pModType
            && !inventoryItem.mIsBroken) {
            return true;
        }
    }

    return false;
}

bool PlayerProfile::hasBrokenMod(const ModType pModType) const {
    for (const auto& inventoryItem : mInventory) {
        const auto inventoryModType = normalizeModName(inventoryItem.mName);
        if (inventoryItem.mType == ItemType::equipment
            && inventoryModType.has_value()
            && *inventoryModType == pModType
            && inventoryItem.mIsBroken) {
            return true;
        }
    }

    return false;
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

std::vector<size_t> PlayerProfile::brokenEquipmentIndices() const {
    std::vector<size_t> indices;

    for (size_t index = 0; index < mInventory.size(); ++index) {
        if (mInventory[index].mType == ItemType::equipment && mInventory[index].mIsBroken) {
            indices.push_back(index);
        }
    }

    return indices;
}

bool PlayerProfile::isGameOver() const {
    return mMoney <= 0 && mFuel <= 0;
}

bool PlayerProfile::applyModWear(const ModType pModType, const int pWearAmount, int& pDurability, bool& pBroken) {
    for (auto& inventoryItem : mInventory) {
        const auto inventoryModType = normalizeModName(inventoryItem.mName);
        if (inventoryItem.mType == ItemType::equipment
            && inventoryModType.has_value()
            && *inventoryModType == pModType
            && !inventoryItem.mIsBroken) {
            inventoryItem.mDurability = std::max(0, inventoryItem.mDurability - pWearAmount);
            inventoryItem.mIsBroken = inventoryItem.mDurability <= 0;
            pDurability = inventoryItem.mDurability;
            pBroken = inventoryItem.mIsBroken;
            return true;
        }
    }

    return false;
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

PlayerCommandResult PlayerProfile::buyMod(const ModType pModType, const int pCost) {
    if (hasMod(pModType)) {
        return {false, domain_text::kPurchaseBlockedTitle, domain_text::mod_already_installed(modLabel(pModType))};
    }

    if (money() < pCost) {
        return {false, domain_text::kNotEnoughMoneyTitle, domain_text::earn_more_credits_for_mod(modLabel(pModType))};
    }

    spendMoney(pCost);

    for (auto& inventoryItem : mInventory) {
        const auto inventoryModType = normalizeModName(inventoryItem.mName);
        if (inventoryItem.mType == ItemType::equipment
            && inventoryModType.has_value()
            && *inventoryModType == pModType) {
            inventoryItem.mIsBroken = false;
            inventoryItem.mDurability = 100;
            inventoryItem.mValue = pCost;
            inventoryItem.mDescription = modLabel(pModType);
            return {true, domain_text::kModPurchasedTitle, domain_text::mod_race_ready_again(modLabel(pModType))};
        }
    }

    addItem(Item(to_code(pModType), ItemType::equipment, pCost, to_full_label(pModType), 100, false));

    return {true, domain_text::kModPurchasedTitle, domain_text::mod_added_to_garage(modLabel(pModType))};
}

PlayerCommandResult PlayerProfile::repairEquipment(size_t pIndex, int pCost) {
    if (pIndex >= mInventory.size() || mInventory[pIndex].mType != ItemType::equipment) {
        return {false, domain_text::kRepairFailedTitle, domain_text::repair_choose_damaged()};
    }

    if (!mInventory[pIndex].mIsBroken) {
        return {false, domain_text::kRepairFailedTitle, domain_text::repair_already_working()};
    }

    if (money() < pCost) {
        return {false, domain_text::kNotEnoughMoneyTitle, domain_text::repair_requires_credits(pCost)};
    }

    spendMoney(pCost);
    mInventory[pIndex].mIsBroken = false;
    mInventory[pIndex].mDurability = game_balance::kRepairRestoreDurability;
    const auto repairedModType = normalizeModName(mInventory[pIndex].mName);
    const std::string repairedModLabel = repairedModType.has_value()
        ? modLabel(*repairedModType)
        : mInventory[pIndex].mName;

    return {
        true,
        domain_text::kRepairCompleteTitle,
        domain_text::mod_repaired_for_next_stint(
            repairedModLabel,
            mInventory[pIndex].mDurability)
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
    return {mMoney, mFuel, mInventory, mMuseumCollection, mMuseumRewards};
}

void PlayerProfile::applySaveData(const PlayerSaveData& pSaveData) {
    mMoney = pSaveData.mMoney;
    mFuel = pSaveData.mFuel;
    mInventory = pSaveData.mInventory;
    mMuseumCollection = pSaveData.mMuseumCollection;
    mMuseumRewards = pSaveData.mMuseumRewards;
}
