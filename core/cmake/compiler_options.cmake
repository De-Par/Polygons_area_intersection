include_guard(GLOBAL)

option(POLYGONS_ENABLE_SANITIZERS "Enable AddressSanitizer and UndefinedBehaviorSanitizer" OFF)

function(polygons_core_options target)
    set_target_properties(${target} PROPERTIES
        CXX_EXTENSIONS OFF
    )
    if(MSVC)
        target_compile_options(${target} PRIVATE
            /W4 /permissive- /utf-8
        )
    else()
        target_compile_options(${target} PRIVATE
            -Wall -Wextra -Wpedantic -Wconversion -Wshadow
        )
    endif()
endfunction()

function(polygons_core_sanitizers target)
    if(NOT POLYGONS_ENABLE_SANITIZERS)
        return()
    endif()

    if(NOT CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang" OR MSVC)
        message(FATAL_ERROR "Sanitizers require GCC or Clang with a GNU-style frontend")
    endif()

    target_compile_options(${target} PUBLIC
        -fsanitize=address,undefined
        -fno-omit-frame-pointer
    )

    target_link_options(${target} PUBLIC
        -fsanitize=address,undefined
    )
endfunction()
