cmake_minimum_required(VERSION 3.21)

project(PolygonsCore
    VERSION 1.0.0
    DESCRIPTION "Convex polygon geometry library"
    LANGUAGES CXX
)

include(cmake/compiler_options.cmake)
include(GNUInstallDirs)

add_library(polygons_core STATIC
    src/geometry.cpp
    src/polygon.cpp
    include/polygons/geometry.hpp
    include/polygons/point.hpp
    include/polygons/polygon.hpp
)

add_library(Polygons::Core ALIAS polygons_core)

set_target_properties(polygons_core PROPERTIES
    EXPORT_NAME Core
    POSITION_INDEPENDENT_CODE ON
)

target_compile_features(polygons_core PUBLIC cxx_std_17)

target_include_directories(polygons_core PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)

polygons_core_options(polygons_core)
polygons_core_sanitizers(polygons_core)

if(PROJECT_IS_TOP_LEVEL)
    include(CTest)
endif()

if(BUILD_TESTING)
    add_subdirectory(tests)
endif()

include(cmake/install.cmake)
