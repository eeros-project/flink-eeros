cmake_minimum_required(VERSION 3.5.1)

project(flink-eeros)

set(CMAKE_CXX_STANDARD 14)


set(RECOMMENDED_EEROS_VERSION 1.1.0.0)


if(CMAKE_BUILD_TYPE MATCHES "Debug|DEBUG")
	set(LOGGER ON)
endif()


include(cmake/versionCheckHelpers.cmake)


setLibraryVersion()


# Find EEROS
setVersionToFind("EEROS" "REQUIRED_EEROS_VERSION" ${RECOMMENDED_EEROS_VERSION} ${REQUIRED_EEROS_VERSION})
find_package(EEROS ${VERSION_TO_FIND} EXACT)
checkIfModuleFound("EEROS" "REQUIRED_EEROS_VERSION")


include_directories(${ADDITIONAL_INCLUDE_DIRS})
link_directories(${ADDITIONAL_LINK_DIRS})

find_package(flink QUIET)
include_directories(${FLINK_INCLUDE_DIR})
link_directories(${FLINK_LIB_DIR})


add_subdirectory(lib)


createPackageFiles(flink-eerosConfig.cmake.in include/ lib/)


INSTALL(FILES ${CMAKE_CURRENT_SOURCE_DIR}/include/FlinkDevice.hpp 
	      ${CMAKE_CURRENT_SOURCE_DIR}/include/DigOut.hpp 
	      ${CMAKE_CURRENT_SOURCE_DIR}/include/DigIn.hpp 
	      ${CMAKE_CURRENT_SOURCE_DIR}/include/AnalogOut.hpp 
	      ${CMAKE_CURRENT_SOURCE_DIR}/include/AnalogIn.hpp 
	      ${CMAKE_CURRENT_SOURCE_DIR}/include/Fqd.hpp 
	      ${CMAKE_CURRENT_SOURCE_DIR}/include/Pwm.hpp 
	      ${CMAKE_CURRENT_SOURCE_DIR}/include/Watchdog.hpp DESTINATION include/flinkeeros)
	      
