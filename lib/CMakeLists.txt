include_directories(../include/)

set(FLINKEEROS_SRCS FlinkDevice.cpp DigOut.cpp DigIn.cpp AnalogOut.cpp AnalogIn.cpp Fqd.cpp Pwm.cpp Watchdog.cpp)

add_library(flinkeeros SHARED ${FLINKEEROS_SRCS})
add_library(flinkeeros_static ${FLINKEEROS_SRCS})


target_link_libraries(flinkeeros flink eeros)
set_target_properties(flinkeeros PROPERTIES VERSION ${LIBRARY_VERSION})

target_link_libraries(flinkeeros_static flink eeros)

INSTALL(TARGETS flinkeeros flinkeeros_static LIBRARY DESTINATION lib ARCHIVE DESTINATION lib)

