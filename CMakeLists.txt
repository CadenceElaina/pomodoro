cmake_minimum_required(VERSION 3.21)

project(pomodoro
    VERSION 0.1.0
    DESCRIPTION "Simple pomodoro timer desktop application"
    LANGUAGES CXX)

# by default GCC compiles "GNU C++" which allows a few non-standard features
# (like variable-length arrays). OFF = plain standard C++ so code stays portable
set(CMAKE_CXX_EXTENSIONS OFF)

# emits build/<preset>/compile_commands.json so clangd / IDEs know how each file gets compiled
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# option() creates an ON/OFF switch you can flip from the command line:
#   cmake --preset debug -DPOMODORO_WARNINGS_AS_ERRORS=ON
# OFF = warnings print but the build succeeds, ON = any warning fails the build
# the pomodoro_ prefix is my own naming convention so nothing clashes with other projects.
# anything starting with CMAKE_ (plus MSVC, BUILD_TESTING, PROJECT_IS_TOP_LEVEL) is built into CMake
option(POMODORO_WARNINGS_AS_ERRORS "Treat compiler warnings as errors" OFF)

# ---------------------------------------------------------------------------
# targets = the named things CMake knows about. every add_library / add_executable
# makes one. most produce a file (libcore.a, app, test_greeter), some are just a
# named bundle of settings (pomodoro_warnings). see them all with:
#   cmake --build --preset debug --target help
# ---------------------------------------------------------------------------

# shared warning flags, applied to my own targets only
# INTERFACE library = compiles nothing, it's a bundle of settings (flags, include paths, etc.)
# that gets applied to whatever links to it. so pomodoro_warnings is "a sticker that says
# use these warning flags" and linking it puts the sticker on core, app and the tests
# every CMake command takes parentheses, even empty ones: if() / else() / endif()
# CMake has no braces, so blocks get closed with endif()
add_library(pomodoro_warnings INTERFACE)
if(MSVC)
    # MSVC = Microsoft's compiler on Windows (yuck), only true when you're using it
    # /W4 = lots of warnings, /permissive- = strict standard C++, /WX = warnings as errors
    target_compile_options(pomodoro_warnings INTERFACE /W4 /permissive-)
    if(POMODORO_WARNINGS_AS_ERRORS)
        target_compile_options(pomodoro_warnings INTERFACE /WX)
    endif()
else()
    # GCC / Clang (this is the branch that runs on Fedora)
    # -Wall -Wextra       common mistakes like unused variables
    # -Wpedantic          non-standard C++
    # -Wshadow            an inner variable with the same name as an outer one
    # -Wconversion        silent narrowing like double -> int
    # -Wsign-conversion   silent int <-> unsigned mixing
    # -Werror             warnings as errors
    target_compile_options(pomodoro_warnings INTERFACE
        -Wall -Wextra -Wpedantic -Wshadow -Wconversion -Wsign-conversion)
    if(POMODORO_WARNINGS_AS_ERRORS)
        target_compile_options(pomodoro_warnings INTERFACE -Werror)
    endif()
endif()

# ---------------------------------------------------------------------------
# library: all the real logic lives here so the app and the tests share the
# same code without compiling it twice. builds to libcore.a
# ---------------------------------------------------------------------------
add_library(core
    src/greeter.cpp
)

# ALIAS = a second name for the same target, so pomodoro::core IS core.
# the :: is purely a naming convention: when CMake sees pomodoro::core it knows it must be
# a target, so a typo gives a clear error. a typo in plain "core" can silently turn into
# "link a file called core". (unrelated to C++'s :: scope operator)
add_library(pomodoro::core ALIAS core)

# who gets each setting:
#   PRIVATE   = only core's own .cpp files
#   INTERFACE = only targets that link core
#   PUBLIC    = both
# include/ is PUBLIC: core's .cpp includes its own header AND app/tests include it too
target_include_directories(core PUBLIC ${PROJECT_SOURCE_DIR}/include)
# PUBLIC: core needs C++20, and anything including core's headers needs it too
target_compile_features(core PUBLIC cxx_std_20)
# PRIVATE: warnings apply to core's files only and don't leak to whoever links core
target_link_libraries(core PRIVATE pomodoro_warnings)

# ---------------------------------------------------------------------------
# executable: a runnable program. builds to build/<preset>/app
# ---------------------------------------------------------------------------
add_executable(app
    app/main.cpp
)
# app gets core (and through it the PUBLIC include path + C++20) plus its own warnings sticker
target_link_libraries(app PRIVATE pomodoro::core pomodoro_warnings)

# ---------------------------------------------------------------------------
# tests: include(CTest) turns on testing so ctest can find the add_test() entries,
# and creates the BUILD_TESTING switch (ON by default, -DBUILD_TESTING=OFF skips the tests).
# PROJECT_IS_TOP_LEVEL is false when someone else pulls my project in as a dependency,
# so they don't have to build my tests
# ---------------------------------------------------------------------------
include(CTest)
if(BUILD_TESTING AND PROJECT_IS_TOP_LEVEL)
    add_subdirectory(tests) # runs tests/CMakeLists.txt
endif()
