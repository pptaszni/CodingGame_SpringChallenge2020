#pragma once

#include <istream>
#include <map>
#include <string>
#include <utility>
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
  bool printInput();
  std::vector<std::string> computeSolution();

private:
  std::vector<std::string> sectorsStrategy();
  std::map<int, Pacman> assignSectors2Pacs(const std::vector<std::pair<int, int> >& sectors);
  std::string collectOrFight(const Pacman& pac, int lb, int ub);
  std::istream& input_;
  int width_;
  int heigth_;
  int my_score_;
  int opponent_score_;
  std::vector<Point> all_possible_fields_;
  std::vector<Pacman> my_pacs_;
  std::vector<Pacman> opponent_pacs_;
  std::vector<Pellet> pellets_;
};

}  // namespace gamecontroller
}  // namespace codingame
