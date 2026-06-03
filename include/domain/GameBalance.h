#ifndef GAME_BALANCE_H
#define GAME_BALANCE_H

#include "ModType.h"
#include <array>

namespace game_balance {
inline constexpr int kStartingMoney = 300;
inline constexpr int kStartingFuel = 8;

inline constexpr int kFuelPackageCost = 40;
inline constexpr int kFuelPackageUnits = 6;

inline constexpr int kAeroModCost = 15;
inline constexpr int kHighPowerModCost = 30;
inline constexpr int kWetGripModCost = 45;

inline constexpr int mod_cost(const ModType pModType) {
    switch (pModType) {
        case ModType::aero_wing:
            return kAeroModCost;
        case ModType::high_power:
            return kHighPowerModCost;
        case ModType::wet_grip:
            return kWetGripModCost;
    }

    return kAeroModCost;
}

inline constexpr int kRepairCostNumerator = 1;
inline constexpr int kRepairCostDenominator = 1;
inline constexpr int kRepairRestoreDurability = 60;

inline constexpr std::array<int, 3> kMuseumMilestones = {3, 6, 9};
inline constexpr std::array<int, 3> kMuseumRewards = {220, 360, 620};
}

#endif // GAME_BALANCE_H
