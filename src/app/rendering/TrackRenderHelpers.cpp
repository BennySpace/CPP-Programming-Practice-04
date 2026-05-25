#include "assets/AssetCatalog.h"
#include "rendering/RenderHelpers.h"

namespace app_render_helpers {
std::string display_track_name(const size_t pIndex) {
    return app_asset_catalog::track_visual(pIndex).mDisplayName;
}
}
