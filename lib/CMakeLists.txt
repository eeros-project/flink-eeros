include_directories(../include/)

set(FLINKEEROS_SRCS FlinkDevice.cpp DigOut.cpp DigIn.cpp AnalogOut.cpp AnalogIn.cpp Fqd.cpp Pwm.cpp Watchdog.cpp)

add_library(flinkeeros SHARED ${FLINKEEROS_SRCS})
add_library(flinkeeros_static ${FLINKEEROS_SRCS})

target_link_libraries(flinkeeros flink eeros)
target_link_libraries(flinkeeros_static flink eeros)

INSTALL(FILES ${CMAKE_CURRENT_BINARY_DIR}/libflinkeeros.so ${CMAKE_CURRENT_BINARY_DIR}/libflinkeeros_static.a DESTINATION lib)
