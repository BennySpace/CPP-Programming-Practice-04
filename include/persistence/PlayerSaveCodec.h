#ifndef PLAYER_SAVE_CODEC_H
#define PLAYER_SAVE_CODEC_H

#include "PlayerSaveData.h"
#include "nlohmann/json.hpp"

class PlayerSaveCodec {
public:
    [[nodiscard]] static bool encode(const PlayerSaveData& pSaveData, nlohmann::json& pOutput);
    [[nodiscard]] static bool decode(const nlohmann::json& pInput, PlayerSaveData& pOutput);
};

#endif // PLAYER_SAVE_CODEC_H
