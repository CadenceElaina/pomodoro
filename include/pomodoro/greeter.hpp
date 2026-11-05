
#pragma once // only paste this file once per .cpp even if it gets included
             // twice

#include <string>
#include <string_view>

// scope named pomodoro - everything between { } belongs to pomodoro::
namespace pomodoro {

// Returns "Hello, <name>!! :3" (or "Hello, World!!" when name is empty).
// function declaration for greet. Tells the compiler a function named
// pomodoro::greet exists, take a std::string_view, and returns a std::string
// nodiscard is a C++17 compiler attribute that tells the compiler "Issue a
// warning if someone calls this function and throws away the return value"
[[nodiscard]] std::string greet(std::string_view name);
/*
If you call pomodoro::greet("Ninja"); by itself without assigning it to a
variable (like std::string msg = pomodoro::greet("Ninja");) or passing it to
something (like std::cout << pomodoro::greet("Ninja");), the compiler
immediately flags a warning
*/

[[nodiscard]] std::string farewell(std::string_view name);
} // namespace pomodoro
