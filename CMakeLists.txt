cmake_minimum_required(VERSION 3.16.3 FATAL_ERROR)

set(PROGECT_NAME gEngine)
project(${PROGECT_NAME})

add_executable(${PROGECT_NAME} 
	src/main.cc
	src/renderer/ShaderProgram.cc
	src/renderer/ShaderProgram.h
	src/renderer/TextureGL.cc
	src/renderer/TextureGL.h
	src/manager/ResourceManager.cc
	src/manager/ResourceManager.h
	src/manager/ResourceManager_wrap.cc
	src/manager/ResourceManager_wrap.h
	src/texture/Texture_base.cc
	src/texture/Texture_base.h
	src/texture/stb_image.h
	src/window/window_base.cc
	src/window/window_base.h
	src/window/window_wrap.cc
	src/window/window_wrap.h
	src/geometry/geometry_base.cc
	src/geometry/geometry_base.h
	src/model/mesh_base.cc
	src/model/mesh_base.h
	src/actor/player_wrap.cc
	src/actor/player_wrap.h
	src/actor/actor.cc
	src/actor/actor.h
	src/process/global.cc
	src/process/global.h
	src/actor/components/component_base.cc
	src/actor/components/component_base.h
	src/actor/components/camera.cc
	src/actor/components/camera.h

)

target_compile_features(${PROGECT_NAME} PUBLIC cxx_std_17)

#template from GLFW Documentation
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(GLFW_INSTALL OFF CACHE BOOL "" FORCE)


#link glfw library
add_subdirectory(external/glfw)
target_link_libraries(${PROGECT_NAME} glfw)

add_subdirectory(external/assimp)
target_link_libraries(${PROGECT_NAME} assimp)

add_subdirectory(external/glad)
target_link_libraries(${PROGECT_NAME} glad)

include_directories(external/glm)

# to put executable file at specific folder
set_target_properties(${PROJECT_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/)

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
					COMMAND ${CMAKE_COMMAND} -E copy_directory
					${CMAKE_SOURCE_DIR}/res $<TARGET_FILE_DIR:${PROJECT_NAME}>/res)
