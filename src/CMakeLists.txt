cmake_minimum_required(VERSION 3.15)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

find_package(Qt5 COMPONENTS Widgets REQUIRED)

set(CMAKE_CXX_STANDARD 20)

set(SOURCE_FILES
        main.cpp
        model/TimeSignature.cpp
)

set(HEADER_FILES
        model/Measure.hpp
        model/TimeSignature.hpp
)

add_executable(
        advancedmetronome
        ${HEADER_FILES}
        ${SOURCE_FILES}
)

# Libraries
target_link_libraries(advancedmetronome Qt5::Widgets)