#ifndef GAME_BALANCE_H
#define GAME_BALANCE_H

#include <array>

namespace game_balance {
inline constexpr int kStartingMoney = 500;
inline constexpr int kStartingFuel = 10;

inline constexpr int kFuelPackageCost = 40;
inline constexpr int kFuelPackageUnits = 6;

inline constexpr int kAeroModCost = 15;
inline constexpr int kHighPowerModCost = 30;
inline constexpr int kWetGripModCost = 45;

inline constexpr int kRepairCostNumerator = 1;
inline constexpr int kRepairCostDenominator = 2;
inline constexpr int kRepairRestoreDurability = 70;

inline constexpr std::array<int, 3> kMuseumMilestones = {3, 6, 9};
inline constexpr std::array<int, 3> kMuseumRewards = {180, 320, 520};
}

#endif // GAME_BALANCE_H
