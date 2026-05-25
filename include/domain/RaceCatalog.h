#ifndef RACE_CATALOG_H
#define RACE_CATALOG_H

#include <array>
#include <string_view>

namespace race_catalog {
struct RaceDefinition {
    const char* mName;
    const char* mCircuitType;
    int mEntryFee;
    const char* mIntroText;
    const char* mStrategyText;
    const char* mBestModText;
    const char* mBaseEventText;
    const char* mPenaltyText;
    int mMoneyPenalty;
    int mFuelPenalty;
    const char* mLootLossPrefix;
    std::array<const char*, 3> mLootNames;
};

inline constexpr RaceDefinition kMonaco = {
    "Monaco Grand Prix",
    "Street / Low Risk",
    75,
    "Safest starting track with a low fee and light wear.",
    "Good for steady credits and low repair pressure.",
    "Best fit: Aero Wing.",
    "The crew expects a calm opening run.",
    "A wall scrape cost 10 credits in emergency repairs.",
    10,
    0,
    "",
    {"Podium Hat", "Engine Part", "Tire Compound"}
};

inline constexpr RaceDefinition kSpa = {
    "Belgian Grand Prix at Spa",
    "Mixed / Balanced",
    120,
    "Best all-around track for steady mid-season progress.",
    "Balanced cost, payout, and museum progress.",
    "Best fit: Wet Grip.",
    "The team prepares for a steady collection run.",
    "Sudden rain burned 1 extra fuel unit.",
    0,
    1,
    "",
    {"Trophy Cap", "Suspension Part", "Gearbox Component"}
};

inline constexpr RaceDefinition kMonza = {
    "Italian Grand Prix at Monza",
    "Fast / High Risk",
    180,
    "Highest loot ceiling, but the garage takes more damage here.",
    "Best once you can absorb risk for premium drops.",
    "Best fit: High Power.",
    "Premium loot is on the line, but mistakes hurt.",
    "",
    0,
    0,
    "High-speed vibrations destroyed stored loot: ",
    {"Trophy Medal", "Aero Wing Part", "Brake System"}
};
}

#endif // RACE_CATALOG_H
