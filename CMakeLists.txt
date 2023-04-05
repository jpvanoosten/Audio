cmake_minimum_required( VERSION 3.23.0 )

project( Audio LANGUAGES CXX )

set( INC_FILES
    inc/Audio/Device.hpp
    inc/Audio/Listener.hpp
    inc/Audio/Sound.hpp
    inc/Audio/Vector.hpp
)

set( SRC_FILES
    src/Device.cpp
    src/Listener.cpp
    src/ListenerImpl.hpp
    src/ListenerImpl.cpp
    src/miniaudio.c
    src/miniaudio.h
    src/Sound.cpp
    src/SoundImpl.hpp
    src/SoundImpl.cpp
    src/stb_vorbis.c
)

set( ALL_FILES 
    ${SRC_FILES} 
    ${INC_FILES} 
)

add_library( Audio STATIC ${ALL_FILES} .clang-format )

set_target_properties( Audio
    PROPERTIES
        CXX_STANDARD 20
)

target_include_directories( Audio
    PUBLIC inc
)
