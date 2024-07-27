cmake_minimum_required(VERSION 3.0.2)
project(nhgui)



include_directories("${PROJECT_SOURCE_DIR}/src/")
include_directories("${PROJECT_SOURCE_DIR}/include/")

set(SOURCES 
	"${PROJECT_SOURCE_DIR}/src/nh_platform.c"
)

add_library(nhplatform SHARED ${SOURCES})

#Dependencies library 
target_link_libraries(nhplatform m)
target_link_libraries(nhplatform ${GLEW_LIBRARIES})
target_link_libraries(nhplatform glfw)
target_link_libraries(nhplatform ${OPENGL_LIBRARIES})

target_include_directories(nhplatform PUBLIC "include/")


find_package(GLEW REQUIRED)
target_include_directories(nhplatform PUBLIC ${GLEW_INCLUDE_DIRS})

set(OpenGL_GL_PREFERENCE GLVND)
find_package(OpenGL REQUIRED)
target_include_directories(nhplatform PUBLIC ${OpenGL_INCLUDE_DIR})

find_package(glfw3 3.0 REQUIRED)


add_subdirectory(example)



