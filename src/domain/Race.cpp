#include "DomainText.h"
#include "Race.h"
#include <algorithm>

Race::Race(const std::string& pName, const std::string& pCircuitType, int pFee)
    : mName(pName), mCircuitType(pCircuitType), mFee(pFee) {}

RaceDriveResult Race::perform_drive(
    PlayerProfile& pPlayer,
    const ModType pModType,
    const int pWearChance,
    const int pWearAmount,
    const int pAwLootChance,
    const int pHpLootChance,
    const int pWgLootChance,
    const Item& pAwLoot,
    const Item& pHpLoot,
    const Item& pWgLoot) {
    if (!pPlayer.hasMod(pModType)) {
        return {
            false,
            false,
            false,
            false,
            0,
            domain_text::kRunAbortedTitle,
            domain_text::run_aborted_missing_mod(PlayerProfile::modLabel(pModType)),
            ""
        };
    }

    pPlayer.spendFuel();

    RaceDriveResult result;
    result.mSuccess = true;
    result.mTitle = domain_text::kEmptySectorTitle;
    result.mMessage = domain_text::empty_sector_message();

    std::uniform_int_distribution<int> wearDistribution(1, 100);
    if (wearDistribution(mRandomNumberGenerator) <= pWearChance) {
        int durability = 0;
        bool broken = false;
        if (pPlayer.applyModWear(pModType, pWearAmount, durability, broken)) {
            result.mModWorn = true;
            result.mDurability = durability;
            result.mModBroken = broken;
        }
    }

    std::uniform_int_distribution<int> lootDistribution(1, 100);
    const int chance = lootDistribution(mRandomNumberGenerator);

    if (pModType == ModType::aero_wing && chance <= pAwLootChance) {
        pPlayer.addItem(pAwLoot);
        result.mFoundLoot = true;
        result.mLootName = pAwLoot.mName;
    } else if (pModType == ModType::high_power && chance <= pHpLootChance) {
        pPlayer.addItem(pHpLoot);
        result.mFoundLoot = true;
        result.mLootName = pHpLoot.mName;
    } else if (pModType == ModType::wet_grip && chance <= pWgLootChance) {
        pPlayer.addItem(pWgLoot);
        result.mFoundLoot = true;
        result.mLootName = pWgLoot.mName;
    }

    if (result.mFoundLoot) {
        result.mTitle = domain_text::kSuccessfulDigTitle;
        result.mMessage = domain_text::loot_recovered(result.mLootName);
    }

    if (result.mModBroken) {
        result.mMessage += " " + domain_text::mod_broke_during_run(PlayerProfile::modLabel(pModType));
    } else if (result.mModWorn) {
        result.mMessage += " " + domain_text::durability_now_at(result.mDurability);
    }

    return result;
}

std::string Race::get_name() const {
    return mName;
}

std::string Race::get_circuit_type() const {
    return mCircuitType;
}

int Race::get_fee() const {
    return mFee;
}
