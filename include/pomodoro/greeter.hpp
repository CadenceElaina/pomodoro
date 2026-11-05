#pragma once

#include <string>
#include <string_view>

namespace pomodoro {

// Returns "Hello, <name>!" (or "Hello, world!" when name is empty).
[[nodiscard]] std::string greet(std::string_view name);

}  // namespace pomodoro
