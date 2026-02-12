add_library(
    nodesk_rt SHARED
    dllmain.c
    DetourFunctions.c
)

target_include_directories(
    nodesk_rt
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(
    nodesk_rt
    PUBLIC
        minhook
        Shlwapi
        nodesk_common
)