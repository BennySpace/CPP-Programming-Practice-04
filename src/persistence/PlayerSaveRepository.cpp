#include "PlayerSaveRepository.h"
#include "PlayerSaveCodec.h"
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

PlayerSaveWriteStatus PlayerSaveRepository::save(const PlayerSaveData& pSaveData, const std::string& pFilename) {
    json saveData;
    if (!PlayerSaveCodec::encode(pSaveData, saveData)) {
        return PlayerSaveWriteStatus::encode_error;
    }

    const std::string tempFilename = pFilename + ".tmp";

    try {
        {
            std::ofstream file(tempFilename, std::ios::trunc);
            if (!file.is_open()) {
                return PlayerSaveWriteStatus::io_error;
            }

            file << saveData.dump(4);
            if (!file.good()) {
                file.close();
                std::filesystem::remove(tempFilename);
                return PlayerSaveWriteStatus::io_error;
            }
        }

        return replace_file(tempFilename, pFilename)
            ? PlayerSaveWriteStatus::success
            : PlayerSaveWriteStatus::io_error;
    } catch (const std::exception&) {
        std::error_code ignoredError;
        std::filesystem::remove(tempFilename, ignoredError);
        return PlayerSaveWriteStatus::io_error;
    }
}

PlayerSaveLoadStatus PlayerSaveRepository::load(PlayerSaveData& pSaveData, const std::string& pFilename) {
    std::ifstream file(pFilename);
    if (!file.is_open()) {
        return std::filesystem::exists(pFilename)
            ? PlayerSaveLoadStatus::io_error
            : PlayerSaveLoadStatus::missing_file;
    }

    try {
        json saveData;
        file >> saveData;

        PlayerSaveData loadedData;
        if (!PlayerSaveCodec::decode(saveData, loadedData)) {
            return PlayerSaveLoadStatus::invalid_data;
        }

        pSaveData = loadedData;
    } catch (const json::exception&) {
        return PlayerSaveLoadStatus::invalid_data;
    } catch (const std::exception&) {
        return PlayerSaveLoadStatus::io_error;
    }

    return PlayerSaveLoadStatus::success;
}
