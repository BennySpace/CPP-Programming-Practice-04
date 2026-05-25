#ifndef DOMAIN_TEXT_H
#define DOMAIN_TEXT_H

#include <string>

namespace domain_text {
inline constexpr const char* kSellFailedTitle = "SELL FAILED";
inline constexpr const char* kLootSoldTitle = "LOOT SOLD";
inline constexpr const char* kDonationFailedTitle = "DONATION FAILED";
inline constexpr const char* kAlreadyDisplayedTitle = "ALREADY DISPLAYED";
inline constexpr const char* kNewExhibitTitle = "NEW EXHIBIT";
inline constexpr const char* kPurchaseBlockedTitle = "PURCHASE BLOCKED";
inline constexpr const char* kNotEnoughMoneyTitle = "NOT ENOUGH MONEY";
inline constexpr const char* kModPurchasedTitle = "MOD PURCHASED";
inline constexpr const char* kRepairFailedTitle = "REPAIR FAILED";
inline constexpr const char* kRepairCompleteTitle = "REPAIR COMPLETE";
inline constexpr const char* kFuelRestockedTitle = "FUEL RESTOCKED";
inline constexpr const char* kNewGameTitle = "NEW GAME";
inline constexpr const char* kRaceErrorTitle = "RACE ERROR";
inline constexpr const char* kEntryDeniedTitle = "ENTRY DENIED";
inline constexpr const char* kRaceStartedTitle = "RACE STARTED";
inline constexpr const char* kNoActiveRaceTitle = "NO ACTIVE RACE";
inline constexpr const char* kOutOfFuelTitle = "OUT OF FUEL";
inline constexpr const char* kRunAbortedTitle = "RUN ABORTED";
inline constexpr const char* kEmptySectorTitle = "EMPTY SECTOR";
inline constexpr const char* kSuccessfulDigTitle = "SUCCESSFUL DIG";

inline constexpr const char* kMuseumMilestonePrefix = "Museum milestone: +";
inline constexpr const char* kCreditsSuffix = " credits.";
inline constexpr const char* kDurabilityPrefix = "Durability now at ";
inline constexpr const char* kDisplaySuffix = " is now on display.";
inline constexpr const char* kRecoveredSuffix = " recovered from the circuit cache.";
inline constexpr const char* kBrokeDuringRunSuffix = " broke during the run.";

inline std::string sellItem_invalid() {
    return "Choose a loot item before selling.";
}

inline std::string loot_sold(const std::string& pName, const int pValue) {
    return pName + " brought " + std::to_string(pValue) + kCreditsSuffix;
}

inline std::string donate_only_loot() {
    return "Only loot can be donated to the museum.";
}

inline std::string already_displayed() {
    return "This exhibit is already in the museum.";
}

inline std::string exhibit_displayed(const std::string& pName) {
    return pName + kDisplaySuffix;
}

inline std::string museum_milestone_reward(const int pCredits) {
    return std::string(kMuseumMilestonePrefix) + std::to_string(pCredits) + kCreditsSuffix;
}

inline std::string mod_already_installed(const std::string& pLabel) {
    return pLabel + " is already installed and working.";
}

inline std::string earn_more_credits_for_mod(const std::string& pLabel) {
    return "Earn more credits before buying " + pLabel + ".";
}

inline std::string mod_race_ready_again(const std::string& pLabel) {
    return pLabel + " is race-ready again.";
}

inline std::string mod_added_to_garage(const std::string& pLabel) {
    return pLabel + " added to the garage.";
}

inline std::string repair_choose_damaged() {
    return "Choose a damaged mod before repairing.";
}

inline std::string repair_already_working() {
    return "This mod is already in working condition.";
}

inline std::string repair_requires_credits(const int pCost) {
    return "Repair bay requires " + std::to_string(pCost) + " credits.";
}

inline std::string mod_restored_full_durability(const std::string& pLabel) {
    return pLabel + " restored to full durability.";
}

inline std::string mod_repaired_for_next_stint(const std::string& pLabel, const int pDurability) {
    return pLabel + " patched up for the next stint. Durability now at " + std::to_string(pDurability) + ".";
}

inline std::string fuel_package_costs(const int pCost) {
    return "Fuel package costs " + std::to_string(pCost) + " credits.";
}

inline std::string garage_reserves_increased(const int pFuelUnits) {
    return "Garage reserves increased by " + std::to_string(pFuelUnits) + " fuel units.";
}

inline std::string new_game_reset() {
    return "Progress reset. Garage, loot and museum restored to default state.";
}

inline std::string selected_race_unavailable() {
    return "Selected race is unavailable.";
}

inline std::string not_enough_credits_for_entry() {
    return "Not enough credits for the entry fee.";
}

inline std::string fuel_reserves_empty() {
    return "Fuel reserves are empty. Visit the garage first.";
}

inline std::string race_started_message(const std::string& pIntro, const std::string& pEventText) {
    return pIntro + " " + pEventText;
}

inline std::string startRace_before_sector() {
    return "Start a Grand Prix before running a sector.";
}

inline std::string buy_more_fuel_before_run() {
    return "Buy more fuel before continuing the run.";
}

inline std::string run_aborted_missing_mod(const std::string& pLabel) {
    return pLabel + " is missing or broken.";
}

inline std::string empty_sector_message() {
    return "No collectible this run. Change setup and try again.";
}

inline std::string loot_recovered(const std::string& pLootName) {
    return pLootName + kRecoveredSuffix;
}

inline std::string mod_broke_during_run(const std::string& pLabel) {
    return pLabel + kBrokeDuringRunSuffix;
}

inline std::string durability_now_at(const int pDurability) {
    return std::string(kDurabilityPrefix) + std::to_string(pDurability) + ".";
}
}

#endif // DOMAIN_TEXT_H
