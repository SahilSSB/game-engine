cmake_minimum_required(VERSION 3.15)
project(Engine2D)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_subdirectory(raylib)

add_executable(Engine2D
	src/main.cpp
	src/asset_manager.cpp
	src/corpse.cpp
	src/animation.cpp
	src/audio_manager.cpp
	src/player.cpp
	src/scene_game_screen.cpp
)
target_link_libraries(Engine2D raylib)
