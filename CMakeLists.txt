#[[cmake_minimum_required(VERSION 3.10)

project(flink-eeros)

set(CMAKE_CXX_STANDARD 14)


set(RECOMMENDED_EEROS_VERSION 1.4)


# Load CMake modules library at specified version
set(LOAD_CMAKE_MODULES_LIB TRUE CACHE BOOL "TRUE if the cmake-modules library should be loaded.")

if(LOAD_CMAKE_MODULES_LIB)
  include(cmake/CMakeModulesLibLoader.cmake)
  load_cmake_modules_lib(https://github.com/eeros-project/cmake-modules.git)
endif()

include(CMakeModulesLib)

if(CMAKE_BUILD_TYPE MATCHES "Debug|DEBUG")
  logger_on()
endif()

if(LOAD_CMAKE_MODULES_LIB)
  checkout_cmake_modules_lib_version(504ffe3)
endif()


# Fetch the version information from git tag
include(VersioningHelpers)
setLibraryVersion()


# Find EEROS
setVersionToFind("EEROS" "REQUIRED_EEROS_VERSION" ${RECOMMENDED_EEROS_VERSION} ${REQUIRED_EEROS_VERSION})
find_package(EEROS ${VERSION_TO_FIND})
checkIfModuleFound("EEROS" "REQUIRED_EEROS_VERSION")
set(REQUIRED_DEGREE_OF_VERSION_COMPATIBILITY 2 CACHE STRING "The required degree of EEROS version compatibilty.")
checkVersionCompatibility(${EEROS_VERSION} ${VERSION_TO_FIND} ${REQUIRED_DEGREE_OF_VERSION_COMPATIBILITY})


find_package(flink REQUIRED)
link_directories(${flink_LIB_DIR})


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
	 ]]

cmake_minimum_required(VERSION 3.14)

include(cmake/git.cmake)

version_from_git(GIT_VERSION)
message("git version: ${GIT_VERSION}")

project(flink-eeros LANGUAGES CXX VERSION ${GIT_VERSION})

include(GNUInstallDirs)
include(CMakePackageConfigHelpers)

add_library("${PROJECT_NAME}_flink" SHARED)
add_library("${PROJECT_NAME}::flink" ALIAS "${PROJECT_NAME}_flink")
set_target_properties("${PROJECT_NAME}_flink" PROPERTIES VERSION ${GIT_VERSION} SOVERSION ${PROJECT_VERSION_MAJOR} OUTPUT_NAME flinkeeros EXPORT_NAME flinkeeros)

find_package(EEROS 1.4 REQUIRED)
find_package(flink REQUIRED)

add_subdirectory(lib)
target_link_libraries("${PROJECT_NAME}_flink" EEROS::eeros flink)

target_include_directories("${PROJECT_NAME}_flink" PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include> $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}/${PROJECT_NAME}>)

target_compile_features("${PROJECT_NAME}_flink" PRIVATE cxx_std_14)
write_basic_package_version_file(
  ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}ConfigVersion.cmake
  COMPATIBILITY AnyNewerVersion
)

install(FILES
  ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}ConfigVersion.cmake
  ${CMAKE_CURRENT_SOURCE_DIR}/cmake/${PROJECT_NAME}Config.cmake
  DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/${PROJECT_NAME}
)

INSTALL(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/include/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/${PROJECT_NAME})

install(TARGETS "${PROJECT_NAME}_flink"
  EXPORT flinkeeros
  RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
  ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

install(EXPORT flinkeeros NAMESPACE ${PROJECT_NAME}:: DESTINATION ${CMAKE_INSTALL_DATADIR}/${PROJECT_NAME})
