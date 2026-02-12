add_executable(
    nodesk_installer
    "NoDeskInstaller.cpp"
)

target_link_libraries(nodesk_installer PRIVATE nodesk_common)