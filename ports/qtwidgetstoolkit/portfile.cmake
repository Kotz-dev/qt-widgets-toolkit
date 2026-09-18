# Registry port: builds from a tagged GitHub release of this library.
# REF/SHA512 are rewritten automatically by .github/workflows/vcpkg-registry-update.yml
# every time a new GitHub release is published — do not edit them by hand.
vcpkg_from_github(
    OUT_SOURCE_PATH SOURCE_PATH
    REPO Kotz-dev/qt-widgets-toolkit
    REF "v0.1.3.1"
    SHA512 8b07e14a5c0617a17b06ed9ad3fb9b99029c9c8a47371e43ca3ba6a08c736b2e0b6a097e90e8a7d06b6f1b7a0787d2b32742fe8484a4de79da3bca426806419f
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
