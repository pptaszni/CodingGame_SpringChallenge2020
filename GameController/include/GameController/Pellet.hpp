#pragma once

#include <iostream>
#include <string>

#include "GameController/Point.hpp"

namespace codingame
{
namespace gamecontroller
{

struct Pellet
{
  Point position;
  int value;
};

}  // namespace gamecontroller
}  // namespace codingame

inline std::istream& operator >>(std::istream& is, codingame::gamecontroller::Pellet& pellet)
{
  is >> pellet.position.x >> pellet.position.y >> pellet.value;
  return is;
}

inline std::ostream& operator <<(std::ostream &os, const codingame::gamecontroller::Pellet& pellet)
{
  os << pellet.position.x << " ";
  os << pellet.position.y << " ";
  os << pellet.value << " ";
  return os;
}
