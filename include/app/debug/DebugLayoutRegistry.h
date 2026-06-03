#ifndef DEBUG_LAYOUT_REGISTRY_H
#define DEBUG_LAYOUT_REGISTRY_H

#ifndef NDEBUG

#include "ApplicationState.h"
#include "GameSession.h"
#include "debug/DebugLayoutEditor.h"
#include <vector>

[[nodiscard]] std::vector<DebugEditableRect> build_debug_layout_rects(
    const GameSession& pGame,
    const ApplicationState& pUiState,
    const DebugLayoutEditor& pEditor);

#endif

#endif // DEBUG_LAYOUT_REGISTRY_H
