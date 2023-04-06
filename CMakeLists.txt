cmake_minimum_required(VERSION 3.24)
project(SeaBattle)

set(CMAKE_CXX_STANDARD 17)

add_executable(SeaBattle main.cpp Player.cpp Player.h Random.tpp Random.h Game.hpp IPlayer.hpp PlayerRandom.hpp CheckPlayer.hpp)
