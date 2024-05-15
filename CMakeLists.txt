cmake_minimum_required(VERSION 3.10)
project(slotGameSimulator)

set(CMAKE_CXX_STANDARD 17)

# Google Test
include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG        release-1.11.0
)
FetchContent_MakeAvailable(googletest)


# Dodaj pliki źródłowe
set(SOURCE_FILES
    src/slotGameSimulator.cpp
    src/Drum.cpp
    src/GameSimulator.cpp
    src/Wallet.cpp
    src/WinningLinesChecker.cpp
)

# Dodaj pliki nagłówkowe
set(HEADER_FILES
    src/Drum.hpp
    src/GameSimulator.hpp
    src/RandomGenerator.hpp
    src/Wallet.hpp
    src/WinningLinesChecker.hpp
    src/FruitTypeHelper.hpp
    src/Definitions.hpp
    src/Timer.hpp
    src/FruitType.hpp
)

# Dodaj wykonywalny plik
add_executable(slotGameSimulator ${SOURCE_FILES} ${HEADER_FILES})

# Tests

add_executable(test_wallet tests/test_wallet.cpp src/Wallet.cpp)
target_link_libraries(test_wallet gtest_main)

add_executable(test_drum tests/test_drum.cpp src/Drum.cpp)
target_link_libraries(test_drum gtest_main)

add_executable(test_randomGenerator tests/test_randomGenerator.cpp)
target_link_libraries(test_randomGenerator gtest_main)

add_executable(test_fruitTypeHelper tests/test_fruitTypeHelper.cpp)
target_link_libraries(test_fruitTypeHelper gtest_main)

add_executable(test_gameSimulator tests/test_gameSimulator.cpp src/GameSimulator.cpp src/Drum.cpp src/Wallet.cpp src/WinningLinesChecker.cpp)
target_link_libraries(test_gameSimulator gtest_main)

add_executable(test_winningLinesChecker tests/test_winningLinesChecker.cpp src/WinningLinesChecker.cpp)
target_link_libraries(test_winningLinesChecker gtest_main)



