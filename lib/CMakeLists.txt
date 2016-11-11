include_directories(../include/)

set(FLINKEEROS_SRCS FlinkDevice.cpp DigOut.cpp)

add_library(flinkeeros SHARED ${FLINKEEROS_SRCS})
add_library(flinkeeros_static ${FLINKEEROS_SRCS})

target_link_libraries(flinkeeros flink)
target_link_libraries(flinkeeros_static flink)

INSTALL(FILES ${CMAKE_CURRENT_BINARY_DIR}/libflinkeeros.so ${CMAKE_CURRENT_BINARY_DIR}/libflinkeeros_static.a DESTINATION lib)

add_dependencies(flinkeeros FlinkDevice DigOut)
add_dependencies(flinkeeros_static FlinkDevice DigOut)
