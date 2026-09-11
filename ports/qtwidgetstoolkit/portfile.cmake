# Registry port: builds from a tagged GitHub release of this library.
# REF/SHA512 are rewritten automatically by .github/workflows/vcpkg-registry-update.yml
# every time a new GitHub release is published — do not edit them by hand.
vcpkg_from_github(
    OUT_SOURCE_PATH SOURCE_PATH
    REPO Kotz-dev/qt-widgets-toolkit
    REF "v0.1.3"
    SHA512 5007cd73332c3188509ba20dd9656da2ea649c49001215391d988760989e0cb911632413c2c84aaada2be578821ef3e1e913f3628035278c759d327033b480a1
    HEAD_REF Master
)

vcpkg_cmake_configure(
    SOURCE_PATH "${SOURCE_PATH}"
)

vcpkg_cmake_install()

vcpkg_cmake_config_fixup(
    PACKAGE_NAME QtWidgetStoolkit
    CONFIG_PATH lib/cmake/QtWidgetStoolkit
)

file(REMOVE_RECURSE "${CURRENT_PACKAGES_DIR}/debug/include")
