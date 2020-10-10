cmake_minimum_required(VERSION 3.16.3 FATAL_ERROR)

set(PROGECT_NAME gEngine)
project(${PROGECT_NAME})

add_executable(${PROGECT_NAME} 
	src/main.cc
	src/Renderer/ShaderProgram.cc
	src/Renderer/ShaderProgram.h
)

target_compile_features(${PROGECT_NAME} PUBLIC cxx_std_17)

#template from GLFW Documentation
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(GLFW_INSTALL OFF CACHE BOOL "" FORCE)

add_subdirectory(external/glfw)

#link glfw library
target_link_libraries(${PROGECT_NAME} glfw)

add_subdirectory(external/glad)
target_link_libraries(${PROGECT_NAME} glad)

# to put executable file at specific folder
set_target_properties(${PROJECT_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/)

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
					COMMAND ${CMAKE_COMMAND} -E copy_directory
					${CMAKE_SOURCE_DIR}/res $<TARGET_FILE_DIR:${PROJECT_NAME}>/res)