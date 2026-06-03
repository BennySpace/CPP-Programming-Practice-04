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
    "Street / Precision",
    90,
    "Tight barriers and low-speed corners reward precision, traction, and maximum downforce.",
    "Best when you can stay clean and let the aero car rotate through the slow section.",
    "Best fit: Aero Wing.",
    "The harbor circuit offers prestige, but the walls leave no room for error.",
    "A barrier scrape cost 25 credits in emergency repairs.",
    25,
    0,
    "",
    {"Podium Hat", "Engine Part", "Tire Compound"}
};

inline constexpr RaceDefinition kSpa = {
    "Belgian Grand Prix at Spa",
    "Ardennes / Weather Swing",
    125,
    "Long straights, elevation changes, and sudden rain make Spa the most variable all-round test.",
    "Wet-weather confidence pays off here when the weather flips mid-run.",
    "Best fit: Wet Grip.",
    "The team braces for changing grip across a long lap.",
    "Sudden rain burned 1 extra fuel unit.",
    0,
    1,
    "",
    {"Trophy Cap", "Suspension Part", "Gearbox Component"}
};

inline constexpr RaceDefinition kMonza = {
    "Italian Grand Prix at Monza",
    "Speed / Low Downforce",
    180,
    "Flat-out straights and brutal braking zones make Monza the purest power track in the calendar.",
    "Best once you can afford the entry and lean into outright speed for premium salvage.",
    "Best fit: High Power.",
    "The Temple of Speed rewards top-end power, but every mistake arrives at full velocity.",
    "",
    0,
    0,
    "High-speed vibrations destroyed stored loot: ",
    {"Trophy Medal", "Aero Wing Part", "Brake System"}
};
}

#endif // RACE_CATALOG_H
