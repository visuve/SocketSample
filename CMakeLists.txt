cmake_minimum_required(VERSION 3.16)
set(CMAKE_CXX_STANDARD 20)

project("Tunkio")

if(MSVC)
	add_compile_options(
		$<$<CONFIG:>:/MT>
		$<$<CONFIG:Debug>:/MTd>
		$<$<CONFIG:Release>:/MT>
	)
endif()

add_subdirectory("Shared")
add_subdirectory("Server")
add_subdirectory("Client")