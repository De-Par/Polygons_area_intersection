include(CMakePackageConfigHelpers)

set(polygons_package_dir "${CMAKE_INSTALL_LIBDIR}/cmake/PolygonsCore")

configure_package_config_file(
    "${CMAKE_CURRENT_LIST_DIR}/PolygonsCoreConfig.cmake.in"
    "${CMAKE_CURRENT_BINARY_DIR}/PolygonsCoreConfig.cmake"
    INSTALL_DESTINATION "${polygons_package_dir}"
)

write_basic_package_version_file(
    "${CMAKE_CURRENT_BINARY_DIR}/PolygonsCoreConfigVersion.cmake"
    VERSION "${PROJECT_VERSION}"
    COMPATIBILITY SameMajorVersion
)

install(
    TARGETS polygons_core
    EXPORT PolygonsCoreTargets
    ARCHIVE DESTINATION "${CMAKE_INSTALL_LIBDIR}"
)

install(
    DIRECTORY include/polygons
    DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}"
)

install(
    EXPORT PolygonsCoreTargets
    NAMESPACE Polygons::
    DESTINATION "${polygons_package_dir}"
)

install(
    FILES
        "${CMAKE_CURRENT_BINARY_DIR}/PolygonsCoreConfig.cmake"
        "${CMAKE_CURRENT_BINARY_DIR}/PolygonsCoreConfigVersion.cmake"
    DESTINATION "${polygons_package_dir}"
)
