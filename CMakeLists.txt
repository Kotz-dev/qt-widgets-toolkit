cmake_minimum_required(VERSION 3.21)
project(QtWidgetStoolkit VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTOMOC ON)

include(GNUInstallDirs)
include(CMakePackageConfigHelpers)

find_package(Qt6 COMPONENTS Core Gui Widgets REQUIRED)

add_library(QtWidgetStoolkit STATIC
        include/QtWidgetStoolkit/QtWidgetStoolkit.h
        include/QtWidgetStoolkit/Animation.h
        src/Animation.cpp
        include/QtWidgetStoolkit/Blur.h
        src/Blur.cpp
        include/QtWidgetStoolkit/Frame.h
        src/Frame.cpp
        include/QtWidgetStoolkit/Geometry.h
        src/Geometry.cpp
        include/QtWidgetStoolkit/ProgessBar.h
        src/ProgessBar.cpp
        include/QtWidgetStoolkit/Signal.h
        include/QtWidgetStoolkit/Splitter.h
        src/Splitter.cpp
        include/QtWidgetStoolkit/Window.h
        src/Window.cpp
)

add_library(QtWidgetStoolkit::QtWidgetStoolkit ALIAS QtWidgetStoolkit)

target_include_directories(QtWidgetStoolkit PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)

target_link_libraries(QtWidgetStoolkit PUBLIC
        Qt6::Core
        Qt6::Gui
        Qt6::Widgets
)

install(TARGETS QtWidgetStoolkit
        EXPORT QtWidgetStoolkitTargets
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

install(DIRECTORY include/QtWidgetStoolkit
        DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)

install(EXPORT QtWidgetStoolkitTargets
        FILE QtWidgetStoolkitTargets.cmake
        NAMESPACE QtWidgetStoolkit::
        DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/QtWidgetStoolkit
)

configure_package_config_file(
        ${CMAKE_CURRENT_SOURCE_DIR}/cmake/QtWidgetStoolkitConfig.cmake.in
        ${CMAKE_CURRENT_BINARY_DIR}/QtWidgetStoolkitConfig.cmake
        INSTALL_DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/QtWidgetStoolkit
)

write_basic_package_version_file(
        ${CMAKE_CURRENT_BINARY_DIR}/QtWidgetStoolkitConfigVersion.cmake
        VERSION ${PROJECT_VERSION}
        COMPATIBILITY SameMajorVersion
)

install(FILES
        ${CMAKE_CURRENT_BINARY_DIR}/QtWidgetStoolkitConfig.cmake
        ${CMAKE_CURRENT_BINARY_DIR}/QtWidgetStoolkitConfigVersion.cmake
        DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/QtWidgetStoolkit
)