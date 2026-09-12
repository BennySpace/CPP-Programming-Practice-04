# Prefer an explicitly selected vcpkg checkout, then Visual Studio's bundled copy.
set(_project_vcpkg_root "$ENV{VCPKG_ROOT}")
if (NOT _project_vcpkg_root)
    set(_project_vswhere "$ENV{ProgramFiles\(x86\)}/Microsoft Visual Studio/Installer/vswhere.exe")
    if (EXISTS "${_project_vswhere}")
        execute_process(
            COMMAND "${_project_vswhere}" -latest -products * -property installationPath
            OUTPUT_VARIABLE _project_vs_root
            OUTPUT_STRIP_TRAILING_WHITESPACE
        )
        set(_project_vcpkg_root "${_project_vs_root}/VC/vcpkg")
    endif ()
endif ()

if (NOT EXISTS "${_project_vcpkg_root}/scripts/buildsystems/vcpkg.cmake")
    message(FATAL_ERROR
        "vcpkg was not found. Install the Visual Studio vcpkg component, or set "
        "VCPKG_ROOT to your vcpkg checkout and restart Visual Studio.")
endif ()

include("${_project_vcpkg_root}/scripts/buildsystems/vcpkg.cmake")
