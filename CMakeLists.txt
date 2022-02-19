project(QUADTREE)

cmake_minimum_required(VERSION 3.0)

# set(CMAKE_CXX_FLAGS_DEBUG_INIT "-Wextra -Wall -pedantic --std=c++17 -g2")
set(CMAKE_CXX_FLAGS_RELEASE_INIT "-Wextra -Wall -pedantic --std=c++17 -O2")

include_directories(include)

set(SRC_FILES src/main.cpp src/app.cpp src/entity.cpp)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)


link_libraries(sfml-graphics sfml-window sfml-system sfml-audio pthread X11)


add_executable(quadtree ${SRC_FILES})
