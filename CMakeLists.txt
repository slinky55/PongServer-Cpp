cmake_minimum_required (VERSION 3.0.0)
project (PongServer)

set (CMAKE_CXX_STANDARD 20)

include_directories(include)
#add_subdirectory(3rdparty/sfml)

file(GLOB_RECURSE SRCS src/*.cpp)

add_executable (${PROJECT_NAME} ${SRCS})

target_link_libraries(${PROJECT_NAME} PRIVATE
	sfml-system sfml-network)
