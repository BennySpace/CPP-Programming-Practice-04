#include "GameSession.h"
#include "GameBalance.h"
#include "DomainText.h"
#include "text/UiText.h"
#include "PlayerSaveRepository.h"
#include "PlayerSaveData.h"
#include "RaceFactory.h"
#include <algorithm>

namespace {
int repair_cost_for_mod(const ModType pModType) {
    const int modValue = game_balance::mod_cost(pModType);
    return std::max(1, modValue * game_balance::kRepairCostNumerator / game_balance::kRepairCostDenominator);
}
}

GameSession::GameSession() {
    mRaces = race_factory::create_default_races();
    PlayerSaveData loadedData;
    const PlayerSaveLoadStatus loadStatus = PlayerSaveRepository::load(loadedData, mSaveFile);

    if (loadStatus == PlayerSaveLoadStatus::success) {
        mPlayer.applySaveData(loadedData);

        if (loadedData.mActiveRaceIndex >= 0
            && loadedData.mActiveRaceIndex < static_cast<int>(mRaces.size())) {
            mActiveRaceIndex = loadedData.mActiveRaceIndex;
        }
    }

    if (loadStatus == PlayerSaveLoadStatus::invalid_data) {
        mPendingAlert = {false, app_text::kBannerLoadFailedTitle, app_text::load_invalid_message()};
    } else if (loadStatus == PlayerSaveLoadStatus::io_error) {
        mPendingAlert = {false, app_text::kBannerLoadFailedTitle, app_text::load_io_error_message()};
    }
}

PlayerProfile& GameSession::player() {
    return mPlayer;
}

const PlayerProfile& GameSession::player() const {
    return mPlayer;
}

const std::vector<std::unique_ptr<Race>>& GameSession::races() const {
    return mRaces;
}

const Race* GameSession::activeRace() const {
    if (mActiveRaceIndex < 0 || mActiveRaceIndex >= static_cast<int>(mRaces.size())) {
        return nullptr;
    }

    return mRaces[static_cast<size_t>(mActiveRaceIndex)].get();
}

std::optional<size_t> GameSession::activeRaceIndex() const {
    if (mActiveRaceIndex < 0 || mActiveRaceIndex >= static_cast<int>(mRaces.size())) {
        return std::nullopt;
    }

    return static_cast<size_t>(mActiveRaceIndex);
}

GameCommandResult GameSession::startRace(size_t pRaceIndex) {
    if (pRaceIndex >= mRaces.size()) {
        return {false, false, domain_text::kRaceErrorTitle, domain_text::selected_race_unavailable()};
    }

    if (activeRace() != nullptr) {
        return {false, false, domain_text::kEntryDeniedTitle, domain_text::finish_active_race_first()};
    }

    Race* selectedRace = mRaces[pRaceIndex].get();

    if (mPlayer.money() < selectedRace->get_fee()) {
        return {false, false, domain_text::kEntryDeniedTitle, domain_text::not_enough_credits_for_entry()};
    }

    if (mPlayer.fuel() <= 0) {
        return {false, false, domain_text::kEntryDeniedTitle, domain_text::fuel_reserves_empty()};
    }

    mPlayer.spendMoney(selectedRace->get_fee());
    mActiveRaceIndex = static_cast<int>(pRaceIndex);

    const RaceEntryResult entryResult = selectedRace->apply_entry_effect(mPlayer);
    (void)save();

    return {
        true,
        !entryResult.mPenaltyApplied,
        domain_text::kRaceStartedTitle,
        domain_text::race_started_message(entryResult.mIntro, entryResult.mEventText)
    };
}

RaceDriveResult GameSession::driveActiveRace(const ModType pModType) {
    if (activeRace() == nullptr) {
        return {false, false, false, false, 0, domain_text::kNoActiveRaceTitle, domain_text::startRace_before_sector(), ""};
    }

    if (mPlayer.fuel() <= 0) {
        return {false, false, false, false, 0, domain_text::kOutOfFuelTitle, domain_text::buy_more_fuel_before_run(), ""};
    }

    RaceDriveResult result = mRaces[static_cast<size_t>(mActiveRaceIndex)]->drive(mPlayer, pModType);
    (void)save();
    return result;
}

void GameSession::leaveRace() {
    mActiveRaceIndex = -1;
    (void)save();
}

PlayerCommandResult GameSession::buyFuel() {
    if (mPlayer.money() < game_balance::kFuelPackageCost) {
        return {false, domain_text::kNotEnoughMoneyTitle, domain_text::fuel_package_costs(game_balance::kFuelPackageCost)};
    }

    mPlayer.spendMoney(game_balance::kFuelPackageCost);
    mPlayer.addFuel(game_balance::kFuelPackageUnits);
    (void)save();
    return {true, domain_text::kFuelRestockedTitle, domain_text::garage_reserves_increased(game_balance::kFuelPackageUnits)};
}

PlayerCommandResult GameSession::repairMod(const ModType pModType) {
    PlayerCommandResult result = mPlayer.repairMod(pModType, repair_cost_for_mod(pModType));
    if (result.mSuccess) {
        (void)save();
    }

    return result;
}

PlayerCommandResult GameSession::sellLoot(size_t pInventoryIndex) {
    PlayerCommandResult result = mPlayer.sellItem(pInventoryIndex);
    if (result.mSuccess) {
        (void)save();
    }

    return result;
}

PlayerCommandResult GameSession::donateLoot(size_t pInventoryIndex) {
    PlayerCommandResult result = mPlayer.donateToMuseum(pInventoryIndex);
    if (result.mSuccess) {
        (void)save();
    }

    return result;
}

PlayerCommandResult GameSession::restart() {
    mPlayer.resetProgress();
    mActiveRaceIndex = -1;
    (void)save();
    return {true, domain_text::kNewGameTitle, domain_text::new_game_reset()};
}

bool GameSession::save() {
    PlayerSaveData saveData = mPlayer.toSaveData();
    saveData.mActiveRaceIndex = mActiveRaceIndex;
    const PlayerSaveWriteStatus saveStatus = PlayerSaveRepository::save(saveData, mSaveFile);
    if (saveStatus != PlayerSaveWriteStatus::success) {
        mPendingAlert = {false, app_text::kBannerSaveFailedTitle, app_text::save_failed_message()};
        return false;
    }

    return true;
}

std::optional<SessionAlert> GameSession::consumePendingAlert() {
    std::optional<SessionAlert> alert = mPendingAlert;
    mPendingAlert.reset();
    return alert;
}
