add_executable(geometry_tests
    geometry_tests.cpp
)

target_link_libraries(geometry_tests
    PRIVATE
        Polygons::Core
)

polygons_core_options(geometry_tests)

add_test(
    NAME core.geometry
    COMMAND geometry_tests
)
