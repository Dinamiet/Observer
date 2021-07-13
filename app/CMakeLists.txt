cmake_minimum_required(VERSION 3.20.0)


################################
set(EXECUTABLE_TARGET "${PROJECT_NAME}_example")
add_executable(${EXECUTABLE_TARGET})

target_compile_options(
    ${EXECUTABLE_TARGET}
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

target_sources(
    ${EXECUTABLE_TARGET}
    PRIVATE # All private source and header files listed here
        main.c
)

target_link_libraries(
    ${EXECUTABLE_TARGET}
    PRIVATE # All external libraries needed for this project.
        ${PROJECT_NAME}
)

add_test(
    NAME
        ${EXECUTABLE_TARGET}
    COMMAND
        ${EXECUTABLE_TARGET}
)
