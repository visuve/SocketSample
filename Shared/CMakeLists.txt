# Shared

if(WIN32)
	file(GLOB SharedSource "*.cpp" "Win32/*.cpp")
	add_library(Shared STATIC ${SharedSource})
	target_precompile_headers(Shared PRIVATE "PCH.hpp")
	target_include_directories(Shared PUBLIC "." "Win32")
else()
	file(GLOB SharedSource "*.cpp" "Posix/*.cpp")
	add_library(Shared STATIC ${SharedSource})
	target_precompile_headers(Shared PRIVATE "PCH.hpp")
	target_include_directories(Shared PUBLIC "." "Posix")
endif()
