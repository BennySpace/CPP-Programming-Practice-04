#include "RaceFactory.h"
#include "LootCatalog.h"
#include "RaceBalance.h"
#include "RaceCatalog.h"
#include <array>

namespace {
enum class EntryEventType {
    money_penalty,
    fuel_penalty,
    loot_loss
};

struct RaceConfig {
    const race_catalog::RaceDefinition* mDefinition;
    DriveBalance mDriveBalance;
    int mEntryEventChance;
    EntryEventType mEntryEventType;
};

class CatalogRace final : public Race {
public:
    explicit CatalogRace(const RaceConfig& pConfig)
        : Race(pConfig.mDefinition->mName, pConfig.mDefinition->mCircuitType, pConfig.mDefinition->mEntryFee),
          mConfig(pConfig) {
        std::random_device randomDevice;
        mRandomNumberGenerator.seed(randomDevice());
    }

    RaceDriveResult drive(PlayerProfile& pPlayer, const ModType pModType) override {
        const auto& lootNames = mConfig.mDefinition->mLootNames;

        return perform_drive(
            pPlayer,
            pModType,
            mConfig.mDriveBalance.mModWearChance,
            mConfig.mDriveBalance.mWearAmount,
            mConfig.mDriveBalance.mLootChances.mAeroWing,
            mConfig.mDriveBalance.mLootChances.mHighPower,
            mConfig.mDriveBalance.mLootChances.mWetGrip,
            loot_catalog::make_loot_item(lootNames[0]),
            loot_catalog::make_loot_item(lootNames[1]),
            loot_catalog::make_loot_item(lootNames[2]));
    }

    RaceEntryResult apply_entry_effect(PlayerProfile& pPlayer) override {
        RaceEntryResult result;
        result.mIntro = get_intro_text();
        result.mEventText = mConfig.mDefinition->mBaseEventText;

        std::uniform_int_distribution<int> distribution(1, 100);
        if (distribution(mRandomNumberGenerator) > mConfig.mEntryEventChance) {
            return result;
        }

        switch (mConfig.mEntryEventType) {
            case EntryEventType::money_penalty:
                pPlayer.spendMoney(mConfig.mDefinition->mMoneyPenalty);
                result.mPenaltyApplied = true;
                result.mMoneyPenalty = mConfig.mDefinition->mMoneyPenalty;
                result.mEventText += " ";
                result.mEventText += mConfig.mDefinition->mPenaltyText;
                return result;

            case EntryEventType::fuel_penalty:
                pPlayer.spendFuel();
                result.mPenaltyApplied = true;
                result.mFuelPenalty = mConfig.mDefinition->mFuelPenalty;
                result.mEventText += " ";
                result.mEventText += mConfig.mDefinition->mPenaltyText;
                return result;

            case EntryEventType::loot_loss: {
                auto lootIndices = pPlayer.lootIndices();
                if (lootIndices.empty()) {
                    return result;
                }

                std::uniform_int_distribution<size_t> lootDistribution(0, lootIndices.size() - 1);
                const size_t lootIndex = lootIndices[lootDistribution(mRandomNumberGenerator)];
                const auto lostItem = pPlayer.removeInventoryItem(lootIndex);
                if (!lostItem.has_value()) {
                    return result;
                }

                result.mPenaltyApplied = true;
                result.mEventText += " ";
                result.mEventText += mConfig.mDefinition->mLootLossPrefix;
                result.mEventText += lostItem->mName;
                result.mEventText += ".";
                return result;
            }
        }

        return result;
    }

    [[nodiscard]] std::string get_intro_text() const override {
        return mConfig.mDefinition->mIntroText;
    }

    [[nodiscard]] std::string get_strategy_text() const override {
        return mConfig.mDefinition->mStrategyText;
    }

    [[nodiscard]] std::string get_best_mod_text() const override {
        return mConfig.mDefinition->mBestModText;
    }

private:
    RaceConfig mConfig;
};

constexpr std::array<RaceConfig, 3> kDefaultRaceConfigs = {{
    {&race_catalog::kMonaco, MonacoBalance::kDrive, MonacoBalance::kCrashChance, EntryEventType::money_penalty},
    {&race_catalog::kSpa, SpaBalance::kDrive, SpaBalance::kRainFuelChance, EntryEventType::fuel_penalty},
    {&race_catalog::kMonza, MonzaBalance::kDrive, MonzaBalance::kItemLossChance, EntryEventType::loot_loss}
}};
}

namespace race_factory {
std::vector<std::unique_ptr<Race>> create_default_races() {
    std::vector<std::unique_ptr<Race>> races;
    races.reserve(kDefaultRaceConfigs.size());

    for (const auto& currentConfig : kDefaultRaceConfigs) {
        races.push_back(std::make_unique<CatalogRace>(currentConfig));
    }

    return races;
}
}
