cmake_minimum_required(VERSION 3.6.0)
project(endlessRunner)
include_directories(
	${PROJECT_SOURCE_DIR}/include
	${PROJECT_SOURCE_DIR}/src
)
file(GLOB SRCS
	"${PROJECT_SOURCE_DIR}/include/*"
	"${PROJECT_SOURCE_DIR}/src/*"
)
add_definitions(-DendlessRunner)
add_executable(endlessRunner ${SRCS})
find_package(SDL2 REQUIRED)
target_link_libraries(endlessRunner ${SDL2_LIBRARIES})
find_package(SDL2_image REQUIRED)
target_link_libraries(endlessRunner ${SDL2_IMAGE_LIBRARIES})
find_package(SDL2_ttf REQUIRED)
target_link_libraries(endlessRunner ${SDL2_TTF_LIBRARIES})
