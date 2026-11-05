BasedOnStyle: LLVM
IndentWidth: 4
BreakBeforeBraces: Allman
ColumnLimit: 100

.clang-format
Allman keeps braces on their own lines

Header files allow us to put declarations in one place and then import them wherever we need them. This can save a lot of typing in multi-file programs.

add.h contians a forward declaration for add()
typically youd do
int add(int x, int y){
return x+y;
}

int main(){
std::cout << 'sum: ' add(3, 4) << '\n';
return 0;
}

if you did main then add() youd get an issue 'add': identifier not found
compiler compiiles contents of code files sequentially.

so you can reorder the fn definitions or use forward declaration
A forward declaration allows us to tell the compiler about the existence of an identifier before actually defining the identifier. For functions we use function declaration statement (function prototype): fn = return type, name, and param types terminated with ;
fn declaration: int add(int x, int y); // no fn body
int add(int x, int y);
int main() {
... add(3,4) ...
}
int add(int x, int y) {return x + y;}
-- often used to tell compiler about a fn defined in another code file - cant reorder in that situation.
Declaration: actually implements or instantiates the identifier
int add(int x, int y);
int x;

definition: a declaration that actually implemetns or instantiates the identifier.
int add(int x, int y){
int z{x+y}; // instantiates variable z

    return z;

}

int x; // instantiates variable x

- in C++ ALL DEFINITIONS ARE DECLARATIONS
  Term Technical Meaning Examples
  Declaration Tells compiler about an identifier and its associated type information. void foo(); // function forward declaration (no body)
  void goo() {}; // function definition (has body)
  int x; // variable definition
  Definition Implements a function or instantiates a variable.
  Definitions are also declarations. void foo() { } // function definition (has body)
  int x; // variable definition
  Pure declaration A declaration that isn’t a definition. void foo(); // function forward declaration (no body)
  Initialization Provides an initial value for a defined object. int x { 2 }; // x is initialized to value 2

learncpp.com header-files
add.cpp --- #include "add.h" --- main.cpp --- #include <iostrem>-
| | | |
| | | |
Compile--------add.h------------Compile------iostream(header file)
| |
add.o main.o
| |
-------Link------------------------------------C++ standard library
|
main.exe

header guards and #pragma once solve the same problem: preventing the preprocessor from including the contents of a header file multiple times within the same translation unit - avoid duplicate symbol definitions and violation of the One Definition Rule (ODR)

header guards #ifndef is the C and C++ standard and 100% portable while #pragma once is non standard compiler ext supported by GCC Clang MSVC and intel - with rare edge cases embedded compilers may lack
pragma - can fail if symlinks hardlinks or mount points alias the same file differently - and is fast natively

#include <iostream>

namespace Foo // define a namespace named Foo
{
// This doSomething() belongs to namespace Foo
int doSomething(int x, int y)
{
return x + y;
}
}

namespace Goo // define a namespace named Goo
{
// This doSomething() belongs to namespace Goo
int doSomething(int x, int y)
{
return x - y;
}
}

int main()
{
std::cout << Goo::doSomething(4, 3) << '\n'; // use the doSomething() that exists in namespace Goo
return 0;
} // results in "1"

scope resolution operator "::" allows us to explicitly pick which namespace w want to look in

#include <iostream>

namespace Foo // define a namespace named Foo
{
// This doSomething() belongs to namespace Foo
int doSomething(int x, int y)
{
return x + y;
}
}

namespace Goo // define a namespace named Goo
{
// This doSomething() belongs to namespace Goo
int doSomething(int x, int y)
{
return x - y;
}
}

int main()
{
std::cout << Foo::doSomething(4, 3) << '\n'; // use the doSomething() that exists in namespace Foo
std::cout << Goo::doSomething(4, 3) << '\n'; // use the doSomething() that exists in namespace Goo
return 0;
} // 7
// 1

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

Most of the time you don’t touch the heap directly at all. std::string and std::vector use the heap internally and clean up after themselves.
