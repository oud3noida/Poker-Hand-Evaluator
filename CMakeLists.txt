cmake_minimum_required(VERSION 3.17)
project(Poker_Hand_Evaluator)

set(CMAKE_CXX_STANDARD 14)

include_directories(Poker-Hand-Evaluator)

add_executable(Poker_Hand_Evaluator
        test_card.cpp
        evaluator/Card.h
        evaluator/Card.cpp)
