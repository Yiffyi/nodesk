add_executable(
    nodesk WIN32
    "NoDesk.c"
    "heur.c"
)

target_link_libraries(nodesk PRIVATE nodesk_common)