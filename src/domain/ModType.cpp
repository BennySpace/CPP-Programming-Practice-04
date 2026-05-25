#include "ModType.h"

std::string to_code(const ModType pModType) {
    switch (pModType) {
        case ModType::aero_wing:
            return "AW";
        case ModType::high_power:
            return "HP";
        case ModType::wet_grip:
            return "WG";
    }

    return "AW";
}

std::string to_full_label(const ModType pModType) {
    switch (pModType) {
        case ModType::aero_wing:
            return "Apex-25 Aero Wing";
        case ModType::high_power:
            return "Apex-25 High Performance";
        case ModType::wet_grip:
            return "Apex-25 Wet Grip";
    }

    return "Apex-25 Aero Wing";
}

std::optional<ModType> try_mod_type_from_code(const std::string& pValue) {
    if (pValue == "Aerodynamics" || pValue == "AW" || pValue == "Apex-25 Aero Wing") {
        return ModType::aero_wing;
    }

    if (pValue == "Engine" || pValue == "HP" || pValue == "Apex-25 High Performance") {
        return ModType::high_power;
    }

    if (pValue == "Tires" || pValue == "WG" || pValue == "Apex-25 Wet Grip") {
        return ModType::wet_grip;
    }

    return std::nullopt;
}
