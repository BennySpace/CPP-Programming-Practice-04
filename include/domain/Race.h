#ifndef RACE_H
#define RACE_H

#include "ModType.h"
#include "PlayerProfile.h"
#include "RaceBalance.h"
#include <random>
#include <string>

struct RaceDriveResult {
    bool mSuccess = false;
    bool mFoundLoot = false;
    bool mModWorn = false;
    bool mModBroken = false;
    int mDurability = 0;
    std::string mTitle;
    std::string mMessage;
    std::string mLootName;
};

struct RaceEntryResult {
    bool mPenaltyApplied = false;
    int mMoneyPenalty = 0;
    int mFuelPenalty = 0;
    std::string mIntro;
    std::string mEventText;
};

class Race {
protected:
    std::string mName;
    std::string mCircuitType;
    int mFee;
    std::mt19937 mRandomNumberGenerator;

    [[nodiscard]] RaceDriveResult perform_drive(
        PlayerProfile& pPlayer,
        ModType pModType,
        int pWearChance,
        int pWearAmount,
        int pAwLootChance,
        int pHpLootChance,
        int pWgLootChance,
        const Item& pAwLoot,
        const Item& pHpLoot,
        const Item& pWgLoot);

public:
    Race(const std::string& pName, const std::string& pCircuitType, int pFee);
    virtual ~Race() = default;

    virtual RaceDriveResult drive(PlayerProfile& pPlayer, ModType pModType) = 0;
    virtual RaceEntryResult apply_entry_effect(PlayerProfile& pPlayer) = 0;
    virtual std::string get_intro_text() const = 0;
    virtual std::string get_strategy_text() const = 0;
    virtual std::string get_best_mod_text() const = 0;

    [[nodiscard]] std::string get_name() const;
    [[nodiscard]] std::string get_circuit_type() const;
    [[nodiscard]] int get_fee() const;
};

#endif // RACE_H
