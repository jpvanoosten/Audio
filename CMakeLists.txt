cmake_minimum_required( VERSION 3.23.0 )

project( Audio LANGUAGES C CXX )

option( AUDIO_BUILD_EXAMPLES "Include the example projects." OFF )

set( INC_FILES
    inc/Audio/Config.hpp
    inc/Audio/Device.hpp
    inc/Audio/Listener.hpp
    inc/Audio/Sound.hpp
    inc/Audio/Vector.hpp
	inc/Audio/Waveform.hpp
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
	src/Waveform.cpp
	src/WaveformImpl.hpp
	src/WaveformImpl.cpp
    src/stb_vorbis.c
)

set( ALL_FILES 
    ${SRC_FILES} 
    ${INC_FILES} 
)

add_library( Audio ${ALL_FILES} .clang-format )

set_target_properties( Audio
    PROPERTIES
        CXX_STANDARD 17
)

target_include_directories( Audio
    PUBLIC inc
)

if( AUDIO_BUILD_EXAMPLES )
	add_subdirectory( example )
	# Set the startup project.
    set_directory_properties( PROPERTIES
        VS_STARTUP_PROJECT example
	)
endif( AUDIO_BUILD_EXAMPLES)
