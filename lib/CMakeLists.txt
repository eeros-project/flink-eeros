include_directories(../include/)

set(BBBLUEEEROS_SRCS BBBlueDevice.cpp DigOut.cpp )
# set(FLINKEEROS_SRCS FlinkDevice.cpp DigOut.cpp DigIn.cpp AnalogOut.cpp AnalogIn.cpp Fqd.cpp Pwm.cpp Watchdog.cpp)

add_library(bbblueeeros SHARED ${BBBLUEEEROS_SRCS})
add_library(bbblueeeros_static ${BBBLUEEEROS_SRCS})

target_link_libraries(bbblueeeros flink eeros)
target_link_libraries(bbblueeeros_static flink eeros)

INSTALL(FILES ${CMAKE_CURRENT_BINARY_DIR}/libbbblueeeros.so ${CMAKE_CURRENT_BINARY_DIR}/libbbblueeeros_static.a DESTINATION lib)
