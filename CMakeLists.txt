cmake_minimum_required(VERSION 3.5.1)

project(flinkeeros)

set(CMAKE_CXX_STANDARD 14)

set(RECOMMENDED_EEROS_VERSION 1.0.0.0)

include(cmake/MunkeiVersionFromGit.cmake)
version_from_git() # Fetch the library version information from git

if(NOT DEFINED REQUIRED_EEROS_VERSION OR
   NOT REQUIRED_EEROS_VERSION MATCHES
       "^(0|[1-9][0-9]*)[.](0|[1-9][0-9]*)[.](0|[1-9][0-9]*)[.](0|[1-9][0-9]*)$")

  set(REQUIRED_EEROS_VERSION ${RECOMMENDED_EEROS_VERSION})
  message("Using recommended EEROS version, which is: v${REQUIRED_EEROS_VERSION}")

else()
  if(NOT ${REQUIRED_EEROS_VERSION} EQUAL ${RECOMMENDED_EEROS_VERSION})
     message("You are not using the recommended EEROS version, "
             "which would be: v${RECOMMENDED_EEROS_VERSION}")
  endif(NOT ${REQUIRED_EEROS_VERSION} EQUAL ${RECOMMENDED_EEROS_VERSION})
endif()


find_package(EEROS ${REQUIRED_EEROS_VERSION} EXACT)

if(EEROS_FOUND) # set by find_package()
	message("EEROS version checked; v${REQUIRED_EEROS_VERSION} found.")
else()
	message(FATAL_ERROR "Make sure the required EEROS version is available "
                   "or set the REQUIRED_EEROS_VERSION variable appropriately.")
endif()


include_directories(${ADDITIONAL_INCLUDE_DIRS})
link_directories(${ADDITIONAL_LINK_DIRS})

find_package(flink QUIET)
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
