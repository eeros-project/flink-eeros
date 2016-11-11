cmake_minimum_required(VERSION 2.6)
project(flinkeeros)

## Compiler flags
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

## Doxygen documentation target (make doc)
find_package(Doxygen)
if(DOXYGEN_FOUND)
	configure_file(doc/Doxyfile.in ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile @ONLY)
	add_custom_target(doc ${DOXYGEN_EXECUTABLE} ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile
		WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
		COMMENT "Generating API documentation with Doxygen" VERBATIM )
endif(DOXYGEN_FOUND)


## Install CMake configuration file
set(INCLUDE_INSTALL_DIR include/)
set(LIB_INSTALL_DIR lib/)

include(CMakePackageConfigHelpers)

configure_package_config_file(
	cmake/flinkeerosConfig.cmake.in
	${CMAKE_CURRENT_BINARY_DIR}/flinkeerosConfig.cmake
	INSTALL_DESTINATION ${LIB_INSTALL_DIR}/flinkeeros/cmake
	PATH_VARS INCLUDE_INSTALL_DIR LIB_INSTALL_DIR)

write_basic_package_version_file(
	${CMAKE_CURRENT_BINARY_DIR}/flinkeerosConfigVersion.cmake
	VERSION 0
	COMPATIBILITY SameMajorVersion)

install(
	FILES
		${CMAKE_CURRENT_BINARY_DIR}/flinkeerosConfig.cmake
		${CMAKE_CURRENT_BINARY_DIR}/flinkeerosConfigVersion.cmake
	DESTINATION
		${LIB_INSTALL_DIR}/flinkeeros/cmake)

find_package(flink REQUIRED)
if (FLINK_LIB_DIR)
	message(STATUS "-> libflink package available")
	include_directories("${FLINK_INCLUDE_DIR}")
	link_directories("${FLINK_LIB_DIR}")
	set(EXTERNAL_LIBS ${EXTERNAL_LIBS} flink)
	set(LIBFLINK "${FLINK_INCLUDE_DIR}")
else()
	find_file(LIBFLINK "flinklib.h" ${ADDITIONAL_INCLUDE_DIRS})
	if(LIBFLINK)
		message(STATUS "-> libflink available")
		set(EXTERNAL_LIBS ${EXTERNAL_LIBS} flink)
	endif()
endif()

find_package(EEROS REQUIRED)
include_directories(${EEROS_INCLUDE_DIR})
link_directories(${EEROS_LIB_DIR})

add_subdirectory(lib)
add_subdirectory(test)

INSTALL(FILES ${CMAKE_CURRENT_SOURCE_DIR}/include/FlinkDevice.hpp ${CMAKE_CURRENT_SOURCE_DIR}/include/DigOut.hpp DESTINATION include)
