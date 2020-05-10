#pragma once

#include <istream>
#include <string>
#include <vector>

#include "GameController/Pacman.hpp"
#include "GameController/Pellet.hpp"
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
  std::vector<std::string> computeSolution();

private:
  std::istream& input_;
  int my_score_;
  int opponent_score_;
  std::vector<Pacman> my_pacs_;
  std::vector<Pacman> opponent_pacs_;
  std::vector<Pellet> pellets_;
};

}  // namespace gamecontroller
}  // namespace codingame
