cmake_minimum_required (VERSION 3.22)

project ("NoDesk")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -static -static-libgcc -static-libstdc++")
add_subdirectory(3rdParty)
add_subdirectory(NoDeskCommon)
add_subdirectory(NoDeskRT)
add_subdirectory(NoDesk)
add_subdirectory(AnyDesk)