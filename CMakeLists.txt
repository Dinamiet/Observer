cmake_minimum_required(VERSION 3.20.0)

project(
    DataBase
)

if (NOT TARGET ${PROJECT_NAME})

if (CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)

    # Let's nicely support folders in IDEs
    set_property(GLOBAL PROPERTY USE_FOLDERS ON)

    # Enable link time optimization if supported by the compiler
    include(CheckIPOSupported)
    check_ipo_supported(RESULT IPO_SUPPORTED)
    if(IPO_SUPPORTED)
        set(CMAKE_INTERPROCEDURAL_OPTIMIZATION TRUE)
    endif()

    include(CTest)

    add_subdirectory(app)

endif()

add_library(
    ${PROJECT_NAME}
    STATIC
)

target_compile_options(
    ${PROJECT_NAME}
    PRIVATE
        "-Wall"
        "-Wextra"
        "-Wpedantic"
        "-Werror"
        "-Wshadow"
        "-Wdouble-promotion"
        "-Wformat=2"
        "-Wformat-security"
        "-Wformat-truncation"
        "-Wundef"
        "-fno-common"
        # "-Wconversion"
        "-Wpadded"
)

target_include_directories(
    ${PROJECT_NAME}
    PUBLIC
        include
)

target_sources(
    ${PROJECT_NAME}
    PUBLIC  # All public source and header files listed here
        include/database.h
    PRIVATE # All private source and header files listed here
        src/database.c
)

add_subdirectory(lib/Buffers)
target_link_libraries(${PROJECT_NAME} PUBLIC Buffers)

add_subdirectory(lib/ChecksumHash)
target_link_libraries(${PROJECT_NAME} PRIVATE ChecksumHash)

endif()
