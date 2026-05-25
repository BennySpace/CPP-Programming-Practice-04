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
    static constexpr int kCrashChance = 12;
    static constexpr DriveBalance kDrive = {
        12,
        8,
        {38, 18, 8}
    };
};

struct SpaBalance {
    static constexpr int kRainFuelChance = 20;
    static constexpr DriveBalance kDrive = {
        18,
        12,
        {16, 22, 28}
    };
};

struct MonzaBalance {
    static constexpr int kItemLossChance = 18;
    static constexpr DriveBalance kDrive = {
        28,
        18,
        {12, 26, 10}
    };
};

#endif // RACE_BALANCE_H
