cmake_minimum_required(VERSION 3.5.0)
project(eac-cue-workaround VERSION 0.1.0 LANGUAGES C CXX)

add_executable(eac-cue-workaround 
    main.cpp
    Track.cpp
    Disc.cpp
    ClipboardReader.cpp
    Workaround.cpp
)

