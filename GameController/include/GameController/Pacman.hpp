#pragma once

#include <iostream>
#include <string>

#include "GameController/Point.hpp"

namespace codingame
{
namespace gamecontroller
{

struct Pacman
{
  int id;
  bool mine;
  Point position;
  std::string type_id;
  int speed_turns_left;
  int ability_cooldown;
};

}  // namespace gamecontroller
}  // namespace codingame

inline std::istream& operator >>(std::istream& is, codingame::gamecontroller::Pacman& pac)
{
  is >> pac.id >> pac.mine >> pac.position.x >> pac.position.y >> pac.type_id;
  is >> pac.speed_turns_left >> pac.ability_cooldown;
  return is;
}

inline std::ostream& operator <<(std::ostream &os, const codingame::gamecontroller::Pacman& pac)
{
  os << pac.id << " ";
  os << pac.mine << " ";
  os << pac.position.x << " ";
  os << pac.position.y << " ";
  os << pac.type_id << " ";
  os << pac.speed_turns_left << " ";
  os << pac.ability_cooldown;
  return os;
}
