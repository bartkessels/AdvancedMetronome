cmake_minimum_required(VERSION 3.15)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

find_package(Qt5 COMPONENTS Widgets Multimedia REQUIRED)

set(CMAKE_CXX_STANDARD 20)

set(SOURCE_FILES
        main.cpp
        domain/model/Measure.cpp
        domain/model/Metronome.cpp
        domain/model/TimeSignature.cpp
        domain/players/MetronomeSoundPlayer.cpp
        domain/sound_engines/QtSoundEngine.cpp
)

set(HEADER_FILES
        domain/contracts/MetronomePlayer.hpp
        domain/contracts/SoundEngine.hpp
        domain/model/Measure.hpp
        domain/model/Metronome.hpp
        domain/model/TimeSignature.hpp
        domain/players/MetronomeSoundPlayer.hpp
        domain/sound_engines/QtSoundEngine.hpp
)

add_executable(
        advancedmetronome
        ${HEADER_FILES}
        ${SOURCE_FILES}
        ../resources/resources.qrc
)

# Libraries
target_link_libraries(advancedmetronome Qt5::Widgets Qt5::Multimedia)