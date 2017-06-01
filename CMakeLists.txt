cmake_minimum_required(VERSION 2.6)
project(flinkeeros)

## Compiler flags
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

include_directories(${ADDITIONAL_INCLUDE_DIRS})
link_directories(${ADDITIONAL_LINK_DIRS})

find_package(flink REQUIRED)
include_directories(${FLINK_INCLUDE_DIR})
link_directories(${FLINK_LIB_DIR})

add_subdirectory(lib)
add_subdirectory(test)

INSTALL(FILES ${CMAKE_CURRENT_SOURCE_DIR}/include/FlinkDevice.hpp 
	      ${CMAKE_CURRENT_SOURCE_DIR}/include/DigOut.hpp 
	      ${CMAKE_CURRENT_SOURCE_DIR}/include/DigIn.hpp 
	      ${CMAKE_CURRENT_SOURCE_DIR}/include/AnalogOut.hpp 
	      ${CMAKE_CURRENT_SOURCE_DIR}/include/AnalogIn.hpp 
	      ${CMAKE_CURRENT_SOURCE_DIR}/include/Fqd.hpp 
	      ${CMAKE_CURRENT_SOURCE_DIR}/include/Pwm.hpp 
	      ${CMAKE_CURRENT_SOURCE_DIR}/include/Watchdog.hpp DESTINATION include/flinkeeros)
