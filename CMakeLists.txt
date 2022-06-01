cmake_minimum_required(VERSION 3.21)
project (cpp_game)

set(CMAKE_CXX_STANDARD 14)

add_executable(cpp_game main.cpp Objects/Bomb.h Objects/Bomb.cpp Objects/Heart.h Objects/Heart.cpp Objects/Map.h Objects/Map.cpp Objects/Player.h Objects/Wall.h Objects/Wall.cpp Objects/Player.cpp)

include_directories(/usr/local/include)

find_package(SFML 2.5.1 COMPONENTS system window graphics network audio REQUIRED)
include_directories(${SFML_INCLUDE_DIRS})
target_link_libraries(cpp_game sfml-system sfml-window sfml-graphics sfml-audio sfml-network)
set(SFML_INCLUDE_DIR "/Desktop/project/sfml/include")
set(SFML_LIBRARY_DIR "/Desktop/project/sfml/build/lib")
set(SFML_DIR)