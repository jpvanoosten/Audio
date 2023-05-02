cmake_minimum_required( VERSION 3.23.0 )

add_executable( example main.cpp MarioCoin.hpp MarioCoin.cpp )

target_link_libraries( example
	PRIVATE Audio
)

set_target_properties( example
    PROPERTIES
        CXX_STANDARD 20
)

# Set the startup project.
set_directory_properties( PROPERTIES
    VS_STARTUP_PROJECT example
)

# Set Local Debugger Settings (Command Arguments and Environment Variables)
set( COMMAND_ARGUMENTS "-cwd \"${CMAKE_CURRENT_SOURCE_DIR}\"" )
configure_file( DebugSettings.vcxproj.user.in ${CMAKE_CURRENT_BINARY_DIR}/example.vcxproj.user @ONLY )
