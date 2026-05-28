#ifndef UI_TEXT_H
#define UI_TEXT_H

#include <string>

namespace app_text {
inline constexpr const char* kPhotoPlaceholder = "PHOTO";

inline constexpr const char* kAppTitle = "FORMULA ONE SIMULATOR 2";
inline constexpr const char* kWindowTitle = "Formula One Simulator 2";
inline constexpr const char* kCreditsLabel = "CREDITS";
inline constexpr const char* kFuelLabel = "FUEL";
inline constexpr const char* kEntryLabel = "ENTRY";
inline constexpr const char* kDurabilityLabel = "DUR";
inline constexpr const char* kValueLabel = "VALUE";
inline constexpr const char* kBrokenLabel = "BROKEN";
inline constexpr const char* kNotFittedLabel = "NOT FITTED";

inline constexpr const char* kMainMenuTitle = "START LIGHTS OUT. ALL SYSTEMS GO.";
inline constexpr const char* kConfirmNewGameTitle = "START NEW GAME?";
inline constexpr const char* kConfirmNewGameBody =
    "THIS WILL ERASE MONEY FUEL INVENTORY AND MUSEUM PROGRESS. CONTINUE?";

inline constexpr const char* kRaceHubPitRadioTitle = "PIT RADIO";
inline constexpr const char* kRaceHubAeroWing = "AERO WING";
inline constexpr const char* kRaceHubHighPower = "HIGH POWER";
inline constexpr const char* kRaceHubWetGrip = "WET GRIP";
inline constexpr const char* kRaceHubRadioFallback = "SELECT A TRACK.";

inline constexpr const char* kGarageMenuFuel = "FUEL PLUS 6 FOR 40";
inline constexpr const char* kGarageMenuAero = "AERO WING 15";
inline constexpr const char* kGarageMenuPower = "HIGH POWER 30";
inline constexpr const char* kGarageMenuWet = "WET GRIP 45";
inline constexpr const char* kGarageSelectedPart = "PIT BENCH";
inline constexpr const char* kGarageSelectedHint = "SELECT A CARD TO CHECK ITS STATUS.";
inline constexpr const char* kGarageSelectedLootHint = "LOOT CAN BE SOLD OR SAVED FOR THE MUSEUM.";
inline constexpr const char* kGarageSelectedBrokenHint = "BROKEN PARTS CAN BE REPAIRED HERE.";
inline constexpr const char* kGarageSelectedWorkingHint = "THIS PART IS READY TO RACE.";

inline constexpr const char* kMuseumTitle = "PODIUM TROPHY HALL";
inline constexpr const char* kMuseumEmptyHint =
    "DONATE LOOT TO FILL THE HALL.";
inline constexpr const char* kMuseumDropOffTitle = "DONATION BAY";
inline constexpr const char* kMuseumDropOffEmpty =
    "WIN LOOT TO DONATE.";
inline constexpr const char* kMuseumMilestones = "REWARD TIERS";
inline constexpr const char* kMuseumRewards = "180 / 320 / 520 CREDITS";

inline constexpr const char* kButtonConfirmReset = "RESET";
inline constexpr const char* kButtonCancel = "CANCEL";
inline constexpr const char* kButtonGoRace = "GRID";
inline constexpr const char* kButtonGoGarage = "GARAGE";
inline constexpr const char* kButtonGoMuseum = "MUSEUM";
inline constexpr const char* kButtonNewGame = "NEW GAME";
inline constexpr const char* kButtonExit = "EXIT";
inline constexpr const char* kButtonStartRace = "LIGHTS OUT";
inline constexpr const char* kButtonDriveAero = "AERO";
inline constexpr const char* kButtonDrivePower = "POWER";
inline constexpr const char* kButtonDriveWet = "WET";
inline constexpr const char* kButtonLeaveRace = "BOX";
inline constexpr const char* kButtonBackMain = "BACK";
inline constexpr const char* kButtonBuyFuel = "REFUEL";
inline constexpr const char* kButtonBuyAero = "AERO";
inline constexpr const char* kButtonBuyPower = "POWER";
inline constexpr const char* kButtonBuyWet = "WET";
inline constexpr const char* kButtonPrevPage = "PREV";
inline constexpr const char* kButtonNextPage = "NEXT";
inline constexpr const char* kButtonSellSelected = "SELL";
inline constexpr const char* kButtonRepairSelected = "REPAIR";
inline constexpr const char* kButtonDonateSelected = "DONATE";

inline constexpr const char* kBannerGarageOnlineTitle = "GARAGE ONLINE";
inline constexpr const char* kBannerReturnedTitle = "RETURNED TO HQ";
inline constexpr const char* kBannerRaceDeckTitle = "RACE DECK";
inline constexpr const char* kBannerGarageTitle = "GARAGE";
inline constexpr const char* kBannerMuseumHallTitle = "MUSEUM HALL";
inline constexpr const char* kBannerConfirmResetTitle = "CONFIRM RESET";
inline constexpr const char* kBannerResetCanceledTitle = "RESET CANCELED";
inline constexpr const char* kBannerHqOnlineTitle = "HQ ONLINE";
inline constexpr const char* kBannerRaceCompleteTitle = "RACE COMPLETE";
inline constexpr const char* kBannerRaceSelectedTitle = "RACE SELECTED";
inline constexpr const char* kBannerItemSelectedTitle = "ITEM SELECTED";
inline constexpr const char* kBannerDonationSlotTitle = "DONATION SLOT";
inline constexpr const char* kBannerSaveFailedTitle = "SAVE FAILED";
inline constexpr const char* kBannerLoadFailedTitle = "SAVE RECOVERY";

inline constexpr const char* kFeedbackCleanStart = "CLEAN START";
inline constexpr const char* kFeedbackRoughStart = "ROUGH START";
inline constexpr const char* kFeedbackEntryFailed = "ENTRY FAILED";
inline constexpr const char* kFeedbackSectorCleared = "SECTOR CLEARED";
inline constexpr const char* kFeedbackEmptyRun = "EMPTY RUN";
inline constexpr const char* kFeedbackRunFailed = "RUN FAILED";

inline std::string save_failed_message() {
    return "Progress changed in memory, but savegame.json could not be updated.";
}

inline std::string load_invalid_message() {
    return "savegame.json is damaged or incompatible. Default garage state loaded.";
}

inline std::string load_io_error_message() {
    return "savegame.json could not be opened. Default garage state loaded.";
}

inline std::string format_page_indicator(const size_t currentPage, const size_t totalPages) {
    return "PAGE " + std::to_string(currentPage + 1) + "/" + std::to_string(totalPages);
}

inline std::string format_labeled_value(const char* label, const int value) {
    return std::string(label) + " " + std::to_string(value);
}

inline std::string format_entry_fee(const int fee) {
    return format_labeled_value(kEntryLabel, fee);
}

inline std::string format_credits(const int credits) {
    return format_labeled_value(kCreditsLabel, credits);
}

inline std::string format_fuel(const int fuel) {
    return format_labeled_value(kFuelLabel, fuel);
}

inline std::string format_item_value(const int value) {
    return format_labeled_value(kValueLabel, value);
}

inline std::string format_durability(const int durability) {
    return format_labeled_value(kDurabilityLabel, durability);
}

inline std::string format_mod_broken(const std::string& code) {
    return code + " " + kBrokenLabel;
}

inline std::string format_mod_durability(const std::string& code, const int durability) {
    return code + " " + format_durability(durability);
}
}

#endif // UI_TEXT_H
