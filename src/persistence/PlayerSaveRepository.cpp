#include "PlayerSaveRepository.h"
#include "PlayerSaveCodec.h"
#include "PlayerProfile.h"
#include "nlohmann/json.hpp"
#include <filesystem>
#include <fstream>

#ifdef _WIN32
#ifndef NOMINMAX
#define NOMINMAX
#endif
#include <windows.h>
#endif

using json = nlohmann::json;

namespace {
bool replace_file(const std::string& pSource, const std::string& pDestination) {
#ifdef _WIN32
    return MoveFileExA(
        pSource.c_str(),
        pDestination.c_str(),
        MOVEFILE_REPLACE_EXISTING | MOVEFILE_WRITE_THROUGH) != 0;
#else
    std::filesystem::rename(pSource, pDestination);
    return true;
#endif
}
}

bool PlayerSaveRepository::save(const PlayerProfile& pPlayer, const std::string& pFilename) {
    json saveData;
    if (!PlayerSaveCodec::encode(pPlayer.toSaveData(), saveData)) {
        return false;
    }

    const std::string tempFilename = pFilename + ".tmp";

    try {
        {
            std::ofstream file(tempFilename, std::ios::trunc);
            if (!file.is_open()) {
                return false;
            }

            file << saveData.dump(4);
            if (!file.good()) {
                file.close();
                std::filesystem::remove(tempFilename);
                return false;
            }
        }

        return replace_file(tempFilename, pFilename);
    } catch (const std::exception&) {
        std::error_code ignoredError;
        std::filesystem::remove(tempFilename, ignoredError);
        return false;
    }
}

bool PlayerSaveRepository::load(PlayerProfile& pPlayer, const std::string& pFilename) {
    std::ifstream file(pFilename);
    if (!file.is_open()) {
        return false;
    }

    try {
        json saveData;
        file >> saveData;

        PlayerSaveData loadedData;
        if (!PlayerSaveCodec::decode(saveData, loadedData)) {
            return false;
        }

        pPlayer.applySaveData(loadedData);
    } catch (const json::exception&) {
        return false;
    } catch (const std::exception&) {
        return false;
    }

    return true;
}
