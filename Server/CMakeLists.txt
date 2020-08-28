# Server

file(GLOB ServerSource "*.cpp")
add_executable(Server ${ServerSource})

target_precompile_headers(Server PRIVATE "PCH.hpp")

target_include_directories(Server PRIVATE "../Shared/")

if(WIN32)
	target_link_libraries(Server LINK_PRIVATE Shared Ws2_32.lib)
else()
	target_link_libraries(Server LINK_PRIVATE Shared stdc++fs)
endif()