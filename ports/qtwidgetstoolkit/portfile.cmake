# Registry port: builds from a tagged GitHub release of this library.
# REF/SHA512 are rewritten automatically by .github/workflows/vcpkg-registry-update.yml
# every time a new GitHub release is published — do not edit them by hand.
vcpkg_from_github(
    OUT_SOURCE_PATH SOURCE_PATH
    REPO Kotz-dev/qt-widgets-toolkit
    REF "v0.1.4.0"
    SHA512 021fc73918c5ddade7e0b97b285116dd54f41b20cfffce5c247d270dbbb8a6d5ebdb15b3b938770595a45db671bc793e418b37d2105d524fd988fbfd07d9307c
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
