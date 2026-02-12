add_executable(
    nodesk
    "NoDesk.c"
)

target_link_libraries(nodesk PRIVATE nodesk_common)