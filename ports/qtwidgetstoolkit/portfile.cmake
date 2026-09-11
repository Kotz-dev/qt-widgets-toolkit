# Registry port: builds from a tagged GitHub release of this library.
# REF/SHA512 are rewritten automatically by .github/workflows/vcpkg-registry-update.yml
# every time a new GitHub release is published — do not edit them by hand.
vcpkg_from_github(
    OUT_SOURCE_PATH SOURCE_PATH
    REPO Kotz-dev/qt-widgets-toolkit
    REF "v0.1.0"
    SHA512 00000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000
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
