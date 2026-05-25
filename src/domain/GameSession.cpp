#include "GameSession.h"
#include "GameBalance.h"
#include "DomainText.h"
#include "PlayerSaveRepository.h"
#include "RaceFactory.h"
#include <algorithm>

GameSession::GameSession() {
    PlayerSaveRepository::load(mPlayer, mSaveFile);
    mRaces = race_factory::create_default_races();
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

int GameSession::activeRaceIndex() const {
    return mActiveRaceIndex;
}

const Race* GameSession::activeRace() const {
    if (mActiveRaceIndex < 0 || mActiveRaceIndex >= static_cast<int>(mRaces.size())) {
        return nullptr;
    }

    return mRaces[static_cast<size_t>(mActiveRaceIndex)].get();
}

GameCommandResult GameSession::startRace(size_t pRaceIndex) {
    if (pRaceIndex >= mRaces.size()) {
        return {false, false, domain_text::kRaceErrorTitle, domain_text::selected_race_unavailable()};
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
    save();

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
    save();
    return result;
}

void GameSession::leaveRace() {
    mActiveRaceIndex = -1;
    save();
}

PlayerCommandResult GameSession::buyFuel() {
    if (mPlayer.money() < game_balance::kFuelPackageCost) {
        return {false, domain_text::kNotEnoughMoneyTitle, domain_text::fuel_package_costs(game_balance::kFuelPackageCost)};
    }

    mPlayer.spendMoney(game_balance::kFuelPackageCost);
    mPlayer.addFuel(game_balance::kFuelPackageUnits);
    save();
    return {true, domain_text::kFuelRestockedTitle, domain_text::garage_reserves_increased(game_balance::kFuelPackageUnits)};
}

PlayerCommandResult GameSession::buyMod(const ModType pModType, const int pCost) {
    PlayerCommandResult result = mPlayer.buyMod(pModType, pCost);
    if (result.mSuccess) {
        save();
    }

    return result;
}

PlayerCommandResult GameSession::sellLoot(size_t pInventoryIndex) {
    PlayerCommandResult result = mPlayer.sellItem(pInventoryIndex);
    if (result.mSuccess) {
        save();
    }

    return result;
}

PlayerCommandResult GameSession::repairMod(size_t pInventoryIndex) {
    const auto& inventory = mPlayer.inventory();
    const int repairCost =
        (pInventoryIndex < inventory.size())
            ? std::max(1, inventory[pInventoryIndex].mValue * game_balance::kRepairCostNumerator / game_balance::kRepairCostDenominator)
            : 0;
    PlayerCommandResult result = mPlayer.repairEquipment(pInventoryIndex, repairCost);
    if (result.mSuccess) {
        save();
    }

    return result;
}

PlayerCommandResult GameSession::donateLoot(size_t pInventoryIndex) {
    PlayerCommandResult result = mPlayer.donateToMuseum(pInventoryIndex);
    if (result.mSuccess) {
        save();
    }

    return result;
}

PlayerCommandResult GameSession::restart() {
    mPlayer.resetProgress();
    mActiveRaceIndex = -1;
    save();
    return {true, domain_text::kNewGameTitle, domain_text::new_game_reset()};
}

void GameSession::save() {
    (void)PlayerSaveRepository::save(mPlayer, mSaveFile);
}
