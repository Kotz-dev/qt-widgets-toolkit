# Local overlay port: builds directly from this working copy instead of
# downloading a release, so `vcpkg install` always picks up local changes.
# To publish a versioned release instead, replace this block with
# vcpkg_from_github()/vcpkg_from_git() pinned to a tagged commit.
get_filename_component(SOURCE_PATH "${CMAKE_CURRENT_LIST_DIR}/../../.." ABSOLUTE)

vcpkg_cmake_configure(
    SOURCE_PATH "${SOURCE_PATH}"
)

vcpkg_cmake_install()

vcpkg_cmake_config_fixup(
    PACKAGE_NAME QtWidgetStoolkit
    CONFIG_PATH lib/cmake/QtWidgetStoolkit
)

file(REMOVE_RECURSE "${CURRENT_PACKAGES_DIR}/debug/include")
