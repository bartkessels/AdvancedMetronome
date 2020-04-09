cmake_minimum_required(VERSION 3.15)

find_package(Qt5 COMPONENTS Widgets REQUIRED)

set(SOURCE_FILES
        ../src/domain/model/Measure.cpp
        ../src/domain/model/Metronome.cpp
        ../src/domain/model/TimeSignature.cpp
)

set(TST_SOURCE_FILES
        main.cpp
        domain/model/tst_Metronome.cpp
        domain/model/tst_TimeSignature.cpp
)

add_executable(am_tests ${SOURCE_FILES} ${TST_SOURCE_FILES})

# Include directories for dependencies
include_directories(../src)

# Libraries
target_link_libraries(am_tests trompeloeil Catch2::Catch2)

add_test(NAME am_tests  COMMAND am_tests)
