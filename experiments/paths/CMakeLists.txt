cmake_minimum_required(VERSION 3.16.3 FATAL_ERROR)

set(PROGECT_NAME experiments)
project(${PROGECT_NAME})

add_executable(${PROGECT_NAME} 
	src/main.cc
)

target_compile_features(${PROGECT_NAME} PUBLIC cxx_std_17)

# to put executable file at specific folder
set_target_properties(${PROJECT_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/)
