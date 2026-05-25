#ifndef PLAYER_SAVE_REPOSITORY_H
#define PLAYER_SAVE_REPOSITORY_H

#include <string>

class PlayerProfile;

class PlayerSaveRepository {
public:
    [[nodiscard]] static bool save(const PlayerProfile& pPlayer, const std::string& pFilename);
    static bool load(PlayerProfile& pPlayer, const std::string& pFilename);
};

#endif // PLAYER_SAVE_REPOSITORY_H
