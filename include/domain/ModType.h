#ifndef MOD_TYPE_H
#define MOD_TYPE_H

#include <optional>
#include <string>

enum class ModType {
    aero_wing,
    high_power,
    wet_grip
};

[[nodiscard]] std::string to_code(ModType pModType);
[[nodiscard]] std::string to_short_label(ModType pModType);
[[nodiscard]] std::string to_full_label(ModType pModType);
[[nodiscard]] std::optional<ModType> try_mod_type_from_code(const std::string& pValue);

#endif // MOD_TYPE_H
