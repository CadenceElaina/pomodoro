TWO PLACES FOR THE PROGRAM TO STORE THINGS:

- Stack: local variables like int failures or std::string_view name - created and freed automatically when the function ends - dies with the functions but is faster
- Heap: memory requested at runtime that persists until its freed. Used when something needs to live past a function that made it or when its size isn't known

Older C++ used pointers like:
Timer\* t = new Timer; // Hey heap id like a Timer
// ... code that uses it ...
delete t; // Here you go Mr. Heap ty

- if you forget to free it with delete you get a MEMORY LEAK - memory is gone until the program exits (bad for programs that run for a long time like an app you open and forget to close)
- if you delete it twice it will crash or send silent bugs that are difficult to read/understand
- raw Timer\* doesnt tell if it should be deleted because who owns it? it doesnt really say.

Smart pointers :3
auto t = add std::make_unique<Timer>(); // from <memory>
// ... code that uses it ...
// no delete: freed automatically when t goes out of scope
// The std::unique_ptr is the owner and the type makes it clear. This cant be copied because it can only have one owner. Clean up happens automatically even on early returns. std::shared_ptr is for when several things need to co-own something but its less common.

--- WRITTEN BY CLAUDE AS A REFERENCE ---
What’s a stream?

A stream is a one-way flow of characters that you write to (or read from) in order, without caring where it ends up. Picture a pipe.

std::cout flows to standard output, which is your terminal by default.
std::cerr flows to standard error, also your terminal by default.
std::cin flows in from your keyboard.

cout and cerr are separate pipes, so you can split them: ./app > out.txt sends cout into the file while errors still show on screen. File streams (std::ofstream) use the exact same <<, which is the nice part. Later, your pomodoro stats could get written to a file with the code you already know.

PRIVATE / PUBLIC / INTERFACE

The question each keyword answers is: who else needs this setting? Here’s how it plays out with core:

Include path, PUBLIC: src/greeter.cpp includes "pomodoro/greeter.hpp", so core needs the path. main.cpp and the test include it too, so anyone linking core needs it as well. That’s both, so it’s PUBLIC.
Warnings, PRIVATE: core wants its own files checked, but that choice shouldn’t be forced on whoever uses core. That’s only core, so it’s PRIVATE. (app still gets warnings because it links pomodoro_warnings itself.)
Inside pomodoro_warnings, INTERFACE: it has no files of its own, so “applies to me” means nothing. The flags only exist to hand out to whoever links it. That’s only others, so it’s INTERFACE.

Think of it as medicine: PRIVATE is taking it yourself, INTERFACE is writing prescriptions for others, and PUBLIC is both.

What’s a target?

A target is a named thing CMake knows how to make, like a recipe card with a name on it. add_executable(app app/main.cpp) says “there’s a thing called app, made from these files, and it’s a program.” Every later line that mentions app adds settings to that card.
