cmake_minimum_required (VERSION 3.0.0)
project (PongServer)

set (CMAKE_CXX_STANDARD 20)

if (MACOS)
	include_directories(/usr/local/include PongClient/include)
	link_directories(/usr/local/lib)
else()
	include_directories(include)
endif()

file(GLOB_RECURSE SRCS src/*.cpp)

add_executable (${PROJECT_NAME} ${SRCS})

target_link_libraries(${PROJECT_NAME} PRIVATE
	sfml-system sfml-network)
