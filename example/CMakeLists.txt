cmake_minimum_required( VERSION 3.23.0 )

add_executable( example main.cpp )

target_link_libraries( example
	PRIVATE Audio
)
