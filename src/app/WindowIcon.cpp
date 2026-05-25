#include "platform/WindowIcon.h"

#ifdef _WIN32
#include "resource.h"
#include <SFML/Window/WindowHandle.hpp>
#include <Windows.h>

namespace {
HICON load_icon(const int size) {
    return static_cast<HICON>(LoadImageW(
        GetModuleHandleW(nullptr),
        MAKEINTRESOURCEW(IDI_APP_ICON),
        IMAGE_ICON,
        size,
        size,
        LR_DEFAULTCOLOR | LR_SHARED));
}
}
#endif

namespace platform {
void apply_window_icon(sf::RenderWindow& pWindow) {
#ifdef _WIN32
    HWND windowHandle = pWindow.getNativeHandle();
    if (windowHandle == nullptr) {
        return;
    }

    if (HICON largeIcon = load_icon(256); largeIcon != nullptr) {
        SendMessageW(windowHandle, WM_SETICON, ICON_BIG, reinterpret_cast<LPARAM>(largeIcon));
    }

    const int smallIconSize = GetSystemMetrics(SM_CXSMICON);
    if (HICON smallIcon = load_icon(smallIconSize); smallIcon != nullptr) {
        SendMessageW(windowHandle, WM_SETICON, ICON_SMALL, reinterpret_cast<LPARAM>(smallIcon));
    }
#else
    (void)pWindow;
#endif
}
}
