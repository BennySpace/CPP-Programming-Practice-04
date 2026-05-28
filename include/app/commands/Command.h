#ifndef COMMAND_H
#define COMMAND_H

#include "ModType.h"
#include <optional>

enum class AppCommand {
    go_race,
    go_garage,
    go_museum,
    new_game,
    confirm_new_game,
    cancel_new_game,
    exit_app,
    back_main,
    start_race,
    drive_aero,
    drive_power,
    drive_wet,
    leave_race,
    buy_fuel,
    buy_aero,
    buy_power,
    buy_wet,
    garage_prev_page,
    garage_next_page,
    sell_selected,
    repair_selected,
    museum_exhibit_prev_page,
    museum_exhibit_next_page,
    museum_drop_prev_page,
    museum_drop_next_page,
    donate_selected
};

[[nodiscard]] inline std::optional<ModType> mod_type_from_action(const AppCommand pAction) {
    if (pAction == AppCommand::drive_aero || pAction == AppCommand::buy_aero) {
        return ModType::aero_wing;
    }

    if (pAction == AppCommand::drive_power || pAction == AppCommand::buy_power) {
        return ModType::high_power;
    }

    if (pAction == AppCommand::drive_wet || pAction == AppCommand::buy_wet) {
        return ModType::wet_grip;
    }

    return std::nullopt;
}

#endif // COMMAND_H
