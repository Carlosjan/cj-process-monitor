add_test([=[MyClassTest.SayHello]=]  /home/carlux/Code/cj-process-monitor/build/tests/cj_process_monitor_tests [==[--gtest_filter=MyClassTest.SayHello]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[MyClassTest.SayHello]=]  PROPERTIES WORKING_DIRECTORY /home/carlux/Code/cj-process-monitor/build/tests SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==])
set(  cj_process_monitor_tests_TESTS MyClassTest.SayHello)
