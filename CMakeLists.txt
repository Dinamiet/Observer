cmake_minimum_required(VERSION 3.20.0)

# Let's nicely support folders in IDEs
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

project(
    Database
)

if (NOT TARGET ${PROJECT_NAME}) # Only configure if not already configured

add_library(
    ${PROJECT_NAME}
    STATIC
)

target_compile_options(
    ${PROJECT_NAME}
    PRIVATE
        "-Wall" # Enable all common warnings
        "-Wextra" # Enable more warnings
        "-Wpedantic" # Warn about non-standard code
        "-Werror" # Warnings are treated as errors
        "-Wshadow" # Warn about shadow variables
        "-Wdouble-promotion" # Warn when promoting floats to double
        "-Wformat=2" # printf and scanf warnings
        "-Wformat-security" # printf and scanf warnings
        "-Wformat-truncation" # printf and scanf warnings
        "-Wundef" # Warn when evaluating not defined flags
        "-fno-common" # Warn about multiple global variables with same name
        "-Wconversion" # Warn about implicit conversions
        "-Wpadded" # Warn about padded structures
        "-flto" # Link time optimization
        "-fno-fat-lto-objects" # Link time optimization
        "-ffunction-sections" # Link time optimization help
        "-fdata-sections" # Link time optimization help
        "-fanalyzer" # Static analysis of program flow
)

target_link_options(
    ${PROJECT_NAME}
    PRIVATE
        "-Wl,--gc-sections" # Remove unwanted sections
        "-flto" # Link time optimization
        "-fno-fat-lto-objects" # Link time optimization
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
