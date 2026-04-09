find_package(PkgConfig REQUIRED)
pkg_check_modules(SDBUS REQUIRED sdbus-c++)

# Create a library from your src code
add_library(cj_process_monitor_lib
        ProcessReader.cpp
        ProcessReader.h
        #dbus/client-proxy.h
        dbus/server-adaptor.h
        dbus/MyService.h
)

# Expose the include path for consumers (tests, other targets)
target_include_directories(cj_process_monitor_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_include_directories(cj_process_monitor_lib PRIVATE ${SDBUS_INCLUDE_DIRS})
target_link_libraries(cj_process_monitor_lib ${SDBUS_LIBRARIES})

add_executable(cj_process_monitor main.cpp)
target_link_libraries(cj_process_monitor PRIVATE cj_process_monitor_lib)
