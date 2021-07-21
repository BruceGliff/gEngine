# 1. setup requirements and project
cmake_minimum_required(VERSION 3.10.2 FATAL_ERROR)

set(PROJECT_NAME tmp)
project(${PROJECT_NAME})


# 2. set all .cc sources files what have .h
set(SOURCES_CC
	main.cc
	raw_texture.cc
	texture.cc

)

set_source_files_properties(${SOURCES_CC} COMPILE_FLAGS "")# "-Wall")
add_executable(${PROJECT_NAME} ${SOURCES_CC} ${SOURCES_H})
target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_17)
