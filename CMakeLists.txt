cmake_minimum_required(VERSION 3.25)
project(Formula_One_Simulator_2 VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
set(VCPKG_APPLOCAL_DEPS OFF)

set(PROJECT_VCPKG_INSTALLED_DIR "${CMAKE_SOURCE_DIR}/external")
if (DEFINED VCPKG_INSTALLED_DIR AND NOT VCPKG_INSTALLED_DIR STREQUAL "")
    set(PROJECT_VCPKG_INSTALLED_DIR "${VCPKG_INSTALLED_DIR}")
endif ()

set(SFML_DIR "${PROJECT_VCPKG_INSTALLED_DIR}/x64-windows/share/sfml")
set(nlohmann_json_DIR "${PROJECT_VCPKG_INSTALLED_DIR}/x64-windows/share/nlohmann_json")

find_package(SFML CONFIG REQUIRED COMPONENTS Graphics Window System)
find_package(nlohmann_json CONFIG REQUIRED)

set(PROJECT_VCPKG_RUNTIME_BIN_DIR "${PROJECT_VCPKG_INSTALLED_DIR}/x64-windows/bin")
if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    set(PROJECT_VCPKG_RUNTIME_BIN_DIR "${PROJECT_VCPKG_INSTALLED_DIR}/x64-windows/debug/bin")
endif ()

file(GLOB PROJECT_VCPKG_RUNTIME_DLLS
    "${PROJECT_VCPKG_RUNTIME_BIN_DIR}/*.dll"
)

set(APP_SOURCES
    ${CMAKE_SOURCE_DIR}/src/app/Application.cpp
    ${CMAKE_SOURCE_DIR}/src/app/AssetManager.cpp
    ${CMAKE_SOURCE_DIR}/src/app/CommandExecutor.cpp
    ${CMAKE_SOURCE_DIR}/src/app/InputHandling.cpp
    ${CMAKE_SOURCE_DIR}/src/app/screens/ScreenInteractions.cpp
    ${CMAKE_SOURCE_DIR}/src/app/screens/ScreenNavigation.cpp
    ${CMAKE_SOURCE_DIR}/src/app/WindowIcon.cpp
    ${CMAKE_SOURCE_DIR}/src/app/rendering/BackgroundRenderer.cpp
    ${CMAKE_SOURCE_DIR}/src/app/rendering/GarageRenderer.cpp
    ${CMAKE_SOURCE_DIR}/src/app/rendering/MainMenuRenderer.cpp
    ${CMAKE_SOURCE_DIR}/src/app/rendering/MuseumRenderer.cpp
    ${CMAKE_SOURCE_DIR}/src/app/rendering/RaceRenderer.cpp
    ${CMAKE_SOURCE_DIR}/src/app/rendering/TrackRenderHelpers.cpp
    ${CMAKE_SOURCE_DIR}/src/app/rendering/WidgetRenderer.cpp
)

set(DOMAIN_SOURCES
    ${CMAKE_SOURCE_DIR}/src/domain/GameSession.cpp
    ${CMAKE_SOURCE_DIR}/src/domain/ModType.cpp
    ${CMAKE_SOURCE_DIR}/src/domain/PlayerProfile.cpp
    ${CMAKE_SOURCE_DIR}/src/domain/Race.cpp
    ${CMAKE_SOURCE_DIR}/src/domain/RaceFactory.cpp
)

set(PERSISTENCE_SOURCES
    ${CMAKE_SOURCE_DIR}/src/persistence/PlayerSaveCodec.cpp
    ${CMAKE_SOURCE_DIR}/src/persistence/PlayerSaveRepository.cpp
)

set(UI_SOURCES
    ${CMAKE_SOURCE_DIR}/src/ui/BitmapText.cpp
)

add_executable(Formula_One_Simulator_2 WIN32)
target_sources(Formula_One_Simulator_2 PRIVATE
    ${CMAKE_SOURCE_DIR}/src/Main.cpp
    ${CMAKE_SOURCE_DIR}/resources/app.rc
    ${APP_SOURCES}
    ${DOMAIN_SOURCES}
    ${PERSISTENCE_SOURCES}
    ${UI_SOURCES}
)
target_compile_features(Formula_One_Simulator_2 PRIVATE cxx_std_17)
target_include_directories(Formula_One_Simulator_2 PRIVATE
    ${CMAKE_SOURCE_DIR}/include
    ${CMAKE_SOURCE_DIR}/include/app
    ${CMAKE_SOURCE_DIR}/include/app/assets
    ${CMAKE_SOURCE_DIR}/include/app/commands
    ${CMAKE_SOURCE_DIR}/include/app/rendering
    ${CMAKE_SOURCE_DIR}/include/app/platform
    ${CMAKE_SOURCE_DIR}/include/app/sfml
    ${CMAKE_SOURCE_DIR}/include/app/text
    ${CMAKE_SOURCE_DIR}/include/domain
    ${CMAKE_SOURCE_DIR}/include/persistence
    ${CMAKE_SOURCE_DIR}/include/ui
    ${CMAKE_SOURCE_DIR}/resources
)

if (MSVC AND CMAKE_GENERATOR MATCHES "Ninja")
    get_filename_component(PROJECT_MSVC_BIN_DIR "${CMAKE_CXX_COMPILER}" DIRECTORY)
    get_filename_component(PROJECT_MSVC_ROOT_DIR "${PROJECT_MSVC_BIN_DIR}/../../.." ABSOLUTE)

    set(PROJECT_WINDOWS_SDK_ROOT_DIR "$ENV{ProgramFiles\(x86\)}/Windows Kits/10")
    file(GLOB PROJECT_WINDOWS_SDK_INCLUDE_DIRS LIST_DIRECTORIES true "${PROJECT_WINDOWS_SDK_ROOT_DIR}/include/*")
    list(SORT PROJECT_WINDOWS_SDK_INCLUDE_DIRS COMPARE NATURAL ORDER DESCENDING)
    list(GET PROJECT_WINDOWS_SDK_INCLUDE_DIRS 0 PROJECT_WINDOWS_SDK_VERSION_DIR)
    get_filename_component(PROJECT_WINDOWS_SDK_VERSION "${PROJECT_WINDOWS_SDK_VERSION_DIR}" NAME)

    target_include_directories(Formula_One_Simulator_2 SYSTEM PRIVATE
        "${PROJECT_MSVC_ROOT_DIR}/include"
        "${PROJECT_WINDOWS_SDK_ROOT_DIR}/include/${PROJECT_WINDOWS_SDK_VERSION}/ucrt"
        "${PROJECT_WINDOWS_SDK_ROOT_DIR}/include/${PROJECT_WINDOWS_SDK_VERSION}/um"
        "${PROJECT_WINDOWS_SDK_ROOT_DIR}/include/${PROJECT_WINDOWS_SDK_VERSION}/shared"
        "${PROJECT_WINDOWS_SDK_ROOT_DIR}/include/${PROJECT_WINDOWS_SDK_VERSION}/winrt"
        "${PROJECT_WINDOWS_SDK_ROOT_DIR}/include/${PROJECT_WINDOWS_SDK_VERSION}/cppwinrt"
    )
    target_link_directories(Formula_One_Simulator_2 PRIVATE
        "${PROJECT_MSVC_ROOT_DIR}/lib/x64"
        "${PROJECT_WINDOWS_SDK_ROOT_DIR}/lib/${PROJECT_WINDOWS_SDK_VERSION}/ucrt/x64"
        "${PROJECT_WINDOWS_SDK_ROOT_DIR}/lib/${PROJECT_WINDOWS_SDK_VERSION}/um/x64"
    )
endif ()

target_link_libraries(Formula_One_Simulator_2 PRIVATE SFML::Graphics SFML::Window SFML::System)
target_link_libraries(Formula_One_Simulator_2 PRIVATE nlohmann_json::nlohmann_json)

if (WIN32)
    target_link_libraries(Formula_One_Simulator_2 PRIVATE
        debug "${PROJECT_VCPKG_INSTALLED_DIR}/x64-windows/debug/lib/manual-link/sfml-main-d.lib"
        optimized "${PROJECT_VCPKG_INSTALLED_DIR}/x64-windows/lib/manual-link/sfml-main.lib"
    )
endif ()

add_custom_command(TARGET Formula_One_Simulator_2 POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        $<TARGET_RUNTIME_DLLS:Formula_One_Simulator_2>
        $<TARGET_FILE_DIR:Formula_One_Simulator_2>
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        ${PROJECT_VCPKG_RUNTIME_DLLS}
        $<TARGET_FILE_DIR:Formula_One_Simulator_2>
    COMMAND ${CMAKE_COMMAND} -E rm -rf
        $<TARGET_FILE_DIR:Formula_One_Simulator_2>/assets/circuits
    COMMAND ${CMAKE_COMMAND} -E rm -rf
        $<TARGET_FILE_DIR:Formula_One_Simulator_2>/assets/tracks
    COMMAND ${CMAKE_COMMAND} -E rm -rf
        $<TARGET_FILE_DIR:Formula_One_Simulator_2>/assets/vehicles
    COMMAND ${CMAKE_COMMAND} -E rm -rf
        $<TARGET_FILE_DIR:Formula_One_Simulator_2>/assets/items
    COMMAND ${CMAKE_COMMAND} -E make_directory
        $<TARGET_FILE_DIR:Formula_One_Simulator_2>/assets/circuits
    COMMAND ${CMAKE_COMMAND} -E make_directory
        $<TARGET_FILE_DIR:Formula_One_Simulator_2>/assets/items
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/assets/circuits
        $<TARGET_FILE_DIR:Formula_One_Simulator_2>/assets/circuits
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/assets/items
        $<TARGET_FILE_DIR:Formula_One_Simulator_2>/assets/items
    COMMAND_EXPAND_LISTS
)
