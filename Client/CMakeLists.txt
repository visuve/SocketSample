# Client

file(GLOB ClientSource "*.cpp")
add_executable(Client ${ClientSource})

target_precompile_headers(Client PRIVATE "PCH.hpp")

target_include_directories(Client PRIVATE "../Shared/")

if(WIN32)
	target_link_libraries(Client LINK_PRIVATE Shared Ws2_32.lib)
else()
	target_link_libraries(Client LINK_PRIVATE Shared stdc++fs)
endif()