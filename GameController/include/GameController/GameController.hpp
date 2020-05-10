#pragma once

#include <istream>
#include <string>

#include "GameController/Point.hpp"

namespace codingame
{
namespace gamecontroller
{

class GameController
{
public:
  GameController(std::istream& input);
  bool readInput();
  std::string computeSolution();

private:
  std::istream& input_;
  bool big_one_;
  Point dest_;
  Point alt_dest_;
};

}  // namespace gamecontroller
}  // namespace codingame
