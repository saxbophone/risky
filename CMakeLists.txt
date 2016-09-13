# begin basic metadata
cmake_minimum_required(VERSION 3.0)

project(risky VERSION 0.5.0 LANGUAGES C)
set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(
    RISKY_VERSION_STRING
    "${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}.${PROJECT_VERSION_PATCH}"
)
set(RISKY_ESCAPED_VERSION_STRING "\"${RISKY_VERSION_STRING}\"")
# end basic metadata

# pass in version of library as preprocessor definitions
add_definitions(-DRISKY_VERSION_MAJOR=${PROJECT_VERSION_MAJOR})
add_definitions(-DRISKY_VERSION_MINOR=${PROJECT_VERSION_MINOR})
add_definitions(-DRISKY_VERSION_PATCH=${PROJECT_VERSION_PATCH})
add_definitions(-DRISKY_VERSION_STRING=${RISKY_ESCAPED_VERSION_STRING})

# used for enabling additional compiler options if supported
include(CheckCCompilerFlag)

function(enable_c_compiler_flag_if_supported flag)
    string(FIND "${CMAKE_C_FLAGS}" "${flag}" flag_already_set)
    if(flag_already_set EQUAL -1)
        check_c_compiler_flag("${flag}" flag_supported)
        if(flag_supported)
            set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${flag}" PARENT_SCOPE)
        endif()
    endif()
endfunction()

# enable all warnings about 'questionable constructs'
enable_c_compiler_flag_if_supported("-Wall")
# issue 'pedantic' warnings for strict ISO compliance
enable_c_compiler_flag_if_supported("-pedantic")
# enable 'extra' strict warnings
enable_c_compiler_flag_if_supported("-Wextra")
# convert all warnings into errors
enable_c_compiler_flag_if_supported("-Werror")

# C Source files
file(GLOB LIB_RISKY_SOURCES "risky/*.c")
# C Header files
file(GLOB LIB_RISKY_HEADERS "risky/*.h")

# main library
add_library(risky ${LIB_RISKY_SOURCES})

# executables
add_executable(rivm rivm.c)
add_executable(tests tests.c)

target_link_libraries(rivm risky)
target_link_libraries(tests risky)

install(
    TARGETS risky
    ARCHIVE DESTINATION lib
    LIBRARY DESTINATION lib
    RUNTIME DESTINATION bin
)

# install library header files
install(FILES ${LIB_RISKY_HEADERS} DESTINATION include/risky)

# install executables
install(PROGRAMS rivm DESTINATION bin)

enable_testing()
add_test(unit_tests tests)
