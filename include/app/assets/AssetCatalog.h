#ifndef ASSET_CATALOG_H
#define ASSET_CATALOG_H

#include <array>
#include <cstddef>

namespace app_asset_catalog {
struct TrackVisualDefinition {
    const char* mDisplayName;
    const char* mPreviewFile;
    const char* mMapFile;
};

inline constexpr std::array<TrackVisualDefinition, 3> kTrackVisualDefinitions = {{
    {"MONACO GP", "monaco_preview.jpg", "monaco_map.jpg"},
    {"SPA GP", "spa_preview.jpg", "spa_map.jpg"},
    {"MONZA GP", "monza_preview.jpg", "monza_map.jpg"}
}};

inline const TrackVisualDefinition& track_visual(const size_t pIndex) {
    return kTrackVisualDefinitions[pIndex < kTrackVisualDefinitions.size() ? pIndex : kTrackVisualDefinitions.size() - 1];
}
}

#endif // ASSET_CATALOG_H
