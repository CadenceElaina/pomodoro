#include "pomodoro/greeter.hpp"

namespace pomodoro
{
  std::string greet(std::string_view name)
  {
    if (name.empty())
    {
      return "Hello, World!!";
    }
    else
    {
      std::string res = "Hello, ";
      res += name;
      res += "!! :3";
      return res;
    }
  }

  std::string farewell(std::string_view name)
  {
    if (name.empty())
    {
      return "Bye! :3";
    }
    else
    {
      std::string res = "Bye, ";
      res += name;
      res += "!! :3";
      return res;
    }
  }

} // namespace pomodoro
