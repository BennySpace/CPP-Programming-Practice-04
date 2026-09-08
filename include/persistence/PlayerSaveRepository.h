#ifndef PLAYER_SAVE_REPOSITORY_H
#define PLAYER_SAVE_REPOSITORY_H

#include <string>

struct PlayerSaveData;

enum class PlayerSaveLoadStatus {
    success,
    missing_file,
    invalid_data,
    io_error
};

enum class PlayerSaveWriteStatus {
    success,
    encode_error,
    io_error
};

class PlayerSaveRepository {
public:
    [[nodiscard]] static PlayerSaveWriteStatus save(const PlayerSaveData& pSaveData, const std::string& pFilename);
    [[nodiscard]] static PlayerSaveLoadStatus load(PlayerSaveData& pSaveData, const std::string& pFilename);
};

#endif // PLAYER_SAVE_REPOSITORY_H
