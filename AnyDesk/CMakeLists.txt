add_executable(
    anydesk
    "main.c"
)

target_link_libraries(anydesk PRIVATE nodesk_common spdlog)