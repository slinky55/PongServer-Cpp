cmake_minimum_required (VERSION 3.0.0)
project (PongServer)

set (CMAKE_CXX_STANDARD 20)

include_directories(include)
#add_subdirectory(3rdparty/sfml)

add_executable (${PROJECT_NAME} main.cpp Server.cpp)

target_link_libraries(${PROJECT_NAME} PRIVATE
	sfml-system sfml-network)
