# test executable: its own little program that runs checks against core
add_executable(test_greeter test_greeter.cpp)
target_link_libraries(test_greeter PRIVATE pomodoro::core pomodoro_warnings)

# registers it with ctest: a test named "greeter" that runs the test_greeter program.
# exit code 0 = pass, anything else = fail
add_test(NAME greeter COMMAND test_greeter)
