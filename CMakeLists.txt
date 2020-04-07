cmake_minimum_required(VERSION 3.15)

project(AdvancedMetronome
        VERSION 0.0.1
        DESCRIPTION "Advanced Metronome is a small application in which you can set multiple measures with their own speed, time-signature and number of repeats. This gives you the ability to practice songs that have multiple speeds and/or time-signatures."
        HOMEPAGE_URL "https://github.com/bartkessels/AdvancedMetronome"
)

# Variables
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/build)

# Subdirectories
add_subdirectory(src)
add_subdirectory(tests)
add_subdirectory(3rd_party)