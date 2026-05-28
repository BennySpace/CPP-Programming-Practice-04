#ifndef GAME_SESSION_H
#define GAME_SESSION_H

#include "ModType.h"
#include "PlayerProfile.h"
#include "Race.h"
#include <memory>
#include <optional>
#include <string>
#include <vector>

struct GameCommandResult {
    bool mSuccess = false;
    bool mHighlightSuccess = false;
    std::string mTitle;
    std::string mMessage;
};

struct SessionAlert {
    bool mSuccess = false;
    std::string mTitle;
    std::string mMessage;
};

class GameSession {
private:
    PlayerProfile mPlayer;
    std::vector<std::unique_ptr<Race>> mRaces;
    const std::string mSaveFile = "savegame.json";
    int mActiveRaceIndex = -1;
    std::optional<SessionAlert> mPendingAlert;

public:
    GameSession();

    [[nodiscard]] PlayerProfile& player();
    [[nodiscard]] const PlayerProfile& player() const;
    [[nodiscard]] const std::vector<std::unique_ptr<Race>>& races() const;
    [[nodiscard]] const Race* activeRace() const;

    GameCommandResult startRace(size_t pRaceIndex);
    RaceDriveResult driveActiveRace(ModType pModType);
    void leaveRace();

    PlayerCommandResult buyFuel();
    PlayerCommandResult buyMod(ModType pModType, int pCost);
    PlayerCommandResult sellLoot(size_t pInventoryIndex);
    PlayerCommandResult repairMod(size_t pInventoryIndex);
    PlayerCommandResult donateLoot(size_t pInventoryIndex);
    PlayerCommandResult restart();

    [[nodiscard]] bool save();
    [[nodiscard]] std::optional<SessionAlert> consumePendingAlert();
};

#endif // GAME_SESSION_H
