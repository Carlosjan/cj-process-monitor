include(FetchContent)

FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/releases/download/v1.17.0/googletest-1.17.0.tar.gz
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

add_executable(cj_process_monitor_tests 
        test_main.cpp
        #HardwareInfoReader.cpp
)
target_link_libraries(cj_process_monitor_tests PRIVATE gtest_main cj_process_monitor_lib)

include(GoogleTest)
gtest_discover_tests(cj_process_monitor_tests)