cmake_minimum_required(VERSION 3.15)
project(Engine2D)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(raylib REQUIRED)

add_executable(Engine2D
	src/animation.cpp
  src/main.cpp
	src/asset_manager.cpp
	src/audio_manager.cpp
	src/player.cpp
	src/corpse.cpp
	src/scene_game_screen.cpp
)
target_link_libraries(Engine2D raylib)
