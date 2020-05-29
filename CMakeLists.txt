cmake_minimum_required(VERSION 3.16)
project(tictactoe)

set(CMAKE_CXX_STANDARD 14)

add_executable(tictactoe src/main.c src/state.c src/state.h src/constants.h src/player.c src/player.h src/scores.c src/scores.h src/nextstates.c src/nextstates.h src/minimax.c src/minimax.h)