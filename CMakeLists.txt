cmake_minimum_required(VERSION 3.10)

project(CPUSim)

set (SOURCES
	src/main.cpp
	src/core/circuit.cpp
	src/core/drawManager.cpp
	src/core/inputManager.cpp
	src/components/component.cpp
	src/components/node.cpp
	src/components/gates/andGate.cpp
	src/components/gates/notGate.cpp
	src/components/gates/inLight.cpp
	src/components/gates/outLight.cpp
)

add_subdirectory(vendor/raylib)

add_executable(CPUSim ${SOURCES})

target_include_directories(CPUSim PRIVATE src)

target_link_libraries(CPUSim PRIVATE raylib)

