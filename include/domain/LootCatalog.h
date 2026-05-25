#ifndef LOOT_CATALOG_H
#define LOOT_CATALOG_H

#include "Item.h"
#include <array>
#include <cstddef>
#include <string_view>

namespace loot_catalog {
struct LootDefinition {
    const char* mName;
    int mValue;
    const char* mDescription;
    size_t mTextureIndex;
};

inline constexpr std::array<LootDefinition, 9> kLootDefinitions = {{
    {"Podium Hat", 55, "Celebration hat from a Monaco podium finish.", 0},
    {"Engine Part", 80, "Compact power unit fragment recovered after a city race.", 1},
    {"Tire Compound", 110, "Rare soft compound with extra street-circuit grip.", 2},
    {"Trophy Cap", 70, "Winner cap from a chaotic mixed-weather weekend.", 0},
    {"Suspension Part", 105, "Adaptive suspension component tuned for elevation changes.", 1},
    {"Gearbox Component", 145, "Precision gearbox part salvaged from a wet-weather setup.", 1},
    {"Trophy Medal", 90, "A polished medal from a high-speed Italian showdown.", 3},
    {"Aero Wing Part", 180, "Monza-spec wing element built for low drag and fast straights.", 4},
    {"Brake System", 260, "Carbon brake assembly built to survive brutal late braking.", 2}
}};

inline constexpr const char* kFallbackDescription = "Formula One collectible.";

inline const LootDefinition* find_definition(const std::string_view pName) {
    for (const auto& currentDefinition : kLootDefinitions) {
        if (pName == currentDefinition.mName) {
            return &currentDefinition;
        }
    }

    return nullptr;
}

inline std::string description_for(const std::string_view pName) {
    if (const LootDefinition* definition = find_definition(pName); definition != nullptr) {
        return definition->mDescription;
    }

    return kFallbackDescription;
}

inline Item make_loot_item(const std::string_view pName) {
    if (const LootDefinition* definition = find_definition(pName); definition != nullptr) {
        return Item(definition->mName, ItemType::loot, definition->mValue, definition->mDescription);
    }

    return Item(std::string(pName), ItemType::loot, 0, kFallbackDescription);
}
}

#endif // LOOT_CATALOG_H
