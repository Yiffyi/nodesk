add_library(
    nodesk_common SHARED
    NoDesk/crypt.cpp
    NoDesk/paths.c
    NoDesk/process.c
    NoDesk/strings.cpp
    # NoDesk/update.cpp
)

target_include_directories(
    nodesk_common
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(
    nodesk_common
    PUBLIC
        spdlog
        bcrypt
        Shlwapi
)