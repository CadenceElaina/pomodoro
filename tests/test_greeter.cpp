// dependency-free tests so the project builds offline
// can swap in a framework (GoogleTest / Catch2) later

#include <cstdlib>     // C++ wrapper around C's standard library, gives EXIT_SUCCESS / EXIT_FAILURE
#include <iostream>    // streams: std::cout / std::cerr
#include <string_view> // read-only window onto existing text (pointer + length), passing one avoids copying strings

#include "pomodoro/greeter.hpp"

// namespace = a named scope so my names can't clash with names from libraries or other files
// (pomodoro::greet and some_lib::greet can both exist).
// an UNNAMED namespace like this one goes further and makes everything inside private
// to this .cpp file only, so check and failures can't collide with anything elsewhere
namespace
{

    int failures = 0;

    // the comparison is evaluated at the call site, so pomodoro::greet("Ninja") == "Hello, Ninja!! :3"
    // becomes true or false BEFORE check runs, and that bool is what check receives.
    // description is just the label for the test (nothing to do with terminal input).
    // false -> print the label to std::cerr (the standard error stream, lives in namespace std)
    // and count the failure
    void check(bool condition, std::string_view description)
    {
        if (!condition)
        {
            std::cerr << "FAIL: " << description << '\n';
            ++failures;
        }
    }

} // namespace

// main lives outside any namespace (it's the program's entry point, it has to).
// it can still call check because things in an unnamed namespace are usable anywhere later in the same file
int main()
{
    check(pomodoro::greet("Ninja") == "Hello, Ninja!! :3", "greet with a name pls");
    check(pomodoro::greet("") == "Hello, World!!", "greet with empty name");

    if (failures == 0)
    {
        std::cout << "All tests passed!\n";
        return EXIT_SUCCESS; // named constant for 0, same meaning as return 0. the exit code is how ctest knows the test passed
    }
    return EXIT_FAILURE;
}
