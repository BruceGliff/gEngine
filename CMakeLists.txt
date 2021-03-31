#[[ 
Comment what describes CMAKE behavior

# 1. setup requirements and project
# 2. set all .cc sources files what have .h
# 3. generate .h names
# 4. add .cc files which without .h pair
# 5. add .h files which without .cc pair
# 6. separte behavior depends on OS
# 7. set flags for .cc files
# 8. assembly project files
# 9. set standart C++17
# 10. Setup properties for GLFW
# 11. link libraries
# 12. put executable file at specific folder
]]

# 1. setup requirements and project
cmake_minimum_required(VERSION 3.10.2 FATAL_ERROR)

set(PROGECT_NAME gEngine)
project(${PROGECT_NAME})


# 2. set all .cc sources files what have .h
set(SOURCES_CC
	src/scene/gismo/grid.cc
	src/debug/debug.cc
	src/window/window_base.cc
	src/texture/Texture_base.cc
	src/scene/scene_wrap.cc
	src/renderer/ShaderProgram.cc
	src/renderer/TextureGL.cc
	src/properties/properties.cc
	src/process/global.cc
	src/model/mesh_base.cc
	src/manager/ResourceManager.cc
	src/manager/EnvironmentHandler_wrap.cc
	src/manager/Entity.cc
	src/geometry/geometry_base.cc
	src/debug/logger.cc
	src/actor/player_wrap.cc
	src/actor/actor.cc
	src/actor/components/component_base.cc
	src/actor/components/camera.cc
	src/actor/components/staticMesh.cc

)

# 3. generate .h names
foreach (src_cc ${SOURCES_CC})
	string(REPLACE ".cc" ".h" src_h ${src_cc})
	list(APPEND SOURCES_H ${src_h})
endforeach()


# 4. add .cc files which without .h pair
list(APPEND SOURCES_CC 
		src/main.cc
	)
# 5. add .h files which without .cc pair
list(APPEND SOURCES_H 
		src/texture/stb_image.h
		src/scene/scene.h
		src/actor/actorDEF.h
	)
# 6. separte behavior depends on OS
if(WIN32)
	#set windows flag
	set(OS_FLAG "-DgWINDOWS")
	list(APPEND SOURCES_CC
		src/debug/formater_WIN.cc
	)
	list(APPEND SOURCES_H
		src/debug/formater_WIN.h
	)
endif(WIN32)
if(UNIX)
	#set linux flag: NOT TESTED
	set(OS_FLAG "-DgUNIX")
	list(APPEND SOURCES_CC
		src/debug/formater_UNIX.cc
	)
	list(APPEND SOURCES_H
		src/debug/formater_UNIX.h
	)
endif(UNIX)

# 6. set flags for .cc files
set_source_files_properties(${SOURCES_CC} COMPILE_FLAGS "")#"-Wall")
# 7. assembly project files
add_executable(${PROGECT_NAME} ${SOURCES_CC} ${SOURCES_H})

# 8. set standart C++17
target_compile_features(${PROGECT_NAME} PUBLIC cxx_std_17)

target_compile_options(${PROGECT_NAME} PUBLIC ${OS_FLAG})

message("CMAKE_BUILD_TYPE = ${CMAKE_BUILD_TYPE}")

# 9. set flag for debugging
if (CMAKE_BUILD_TYPE STREQUAL "Debug")
	target_compile_options(${PROGECT_NAME} PUBLIC "-DgDEBUG")
	set_source_files_properties(${SOURCES_CC} COMPILE_FLAGS "-g -Wall")
endif()

# 10. Setup properties for GLFW
# template from GLFW Documentation
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(GLFW_INSTALL OFF CACHE BOOL "" FORCE)


# 11. link libraries
add_subdirectory(external/glfw)
target_link_libraries(${PROGECT_NAME} glfw)

add_subdirectory(external/assimp)
target_link_libraries(${PROGECT_NAME} assimp)

add_subdirectory(external/glad)
target_link_libraries(${PROGECT_NAME} glad)

include_directories(external/glm)

# 12. put executable file at specific folder
set_target_properties(${PROJECT_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/)

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
					COMMAND ${CMAKE_COMMAND} -E copy_directory
					${CMAKE_SOURCE_DIR}/res $<TARGET_FILE_DIR:${PROJECT_NAME}>/res)
