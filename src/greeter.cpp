#include "pomodoro/greeter.hpp"

namespace pomodoro
{

  std::string greet(std::string_view name)
  {
    if (name.empty())
    {
      name = "world";
    }
    std::string result{"Hello, "};
    result.append(name);
    result.append("!");
    return result;
  }

} // namespace pomodoro
