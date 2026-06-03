#ifndef RACE_BALANCE_H
#define RACE_BALANCE_H

struct LootChances {
    int mAeroWing = 0;
    int mHighPower = 0;
    int mWetGrip = 0;
};

struct DriveBalance {
    int mModWearChance = 0;
    int mWearAmount = 0;
    LootChances mLootChances;
};

struct MonacoBalance {
    static constexpr int kCrashChance = 18;
    static constexpr DriveBalance kDrive = {
        16,
        10,
        {44, 10, 18}
    };
};

struct SpaBalance {
    static constexpr int kRainFuelChance = 32;
    static constexpr DriveBalance kDrive = {
        22,
        14,
        {18, 18, 24}
    };
};

struct MonzaBalance {
    static constexpr int kItemLossChance = 20;
    static constexpr DriveBalance kDrive = {
        24,
        16,
        {16, 22, 8}
    };
};

#endif // RACE_BALANCE_H
