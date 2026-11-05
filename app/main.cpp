#include <iostream> // streams: std::cout (normal output), std::cerr (errors), std::cin (input)
#include <string_view> // std::string_view: read-only window onto existing text

#include "pomodoro/greeter.hpp" // found because core's include/ folder is PUBLIC in CMake

// argc = argument count, argv = the arguments themselves
//   ./app Ninja  ->  argc == 2, argv[0] == "./app", argv[1] == "Ninja"
// char *argv[] = an array of char*, each char* is a C-style string
// (raw pointers, the old C way of handling text)
//
// pointers vs references vs smart pointers:
//   T*                  raw pointer: an address. can be null, doesn't say who
//   owns the thing T&                  reference: "use this existing thing",
//   never null std::unique_ptr<T>  smart pointer: owns heap memory and deletes
//   it automatically
// reach for references first, smart pointers when you own something,
// and raw pointers only when an API hands them to you (like argv here)
int main(int argc, char *argv[]) {
  // ternary  condition ? a : b  = "if there's an argument use it, else use
  // empty"
  const std::string_view name = argc > 1 ? argv[1] : "";

  // :: = "look inside this scope", so pomodoro::greet is the function greet
  // inside namespace pomodoro.
  //      namespaces and folders are UNRELATED, the folder only matters for
  //      #include
  // << = "send into the stream", so this writes the greeting and then a newline
  // to the terminal
  std::cout << pomodoro::greet(name) << '\n';
  std::cout << pomodoro::farewell(name) << '\n';
  // main is special: reaching the end without a return means return 0 (success)
}
