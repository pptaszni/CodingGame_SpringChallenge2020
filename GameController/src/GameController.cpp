
#include "GameController/Debug.hpp"
#include "GameController/GameController.hpp"
#include "GameController/Pacman.hpp"
#include "GameController/Pellet.hpp"
#include "GameController/Point.hpp"

#define BIG_DIST 100000

int dist(int x1, int y1, int x2, int y2)
{
    return (x2-x1)*(x2-x1) + (y2-y1)*(y2-y1);
}

namespace codingame
{
namespace gamecontroller
{

GameController::GameController(std::istream& input):
  input_(input),
  my_score_(0),
  opponent_score_(0),
  my_pacs_(),
  opponent_pacs_(),
  pellets_()
{
  int width; // size of the grid
  int height; // top left corner is (x=0, y=0)
  input_ >> width >> height; input_.ignore();
  for (int i = 0; i < height; i++) {
    std::string row;
    std::getline(input_, row);
  }
}

bool GameController::readInput()
{
  DEBUG("readInput");
  my_pacs_.clear();
  opponent_pacs_.clear();
  pellets_.clear();
  input_ >> my_score_ >> opponent_score_; input_.ignore();
  int visiblePacCount; // all your pacs and enemy pacs in sight
  input_ >> visiblePacCount; input_.ignore();
  DEBUG("reading pacs");
  for (int i = 0; i < visiblePacCount; i++) {
    Pacman p;
    input_ >> p; input_.ignore();
    if (p.mine)
    {
      my_pacs_.push_back(p);
    }
    else
    {
      opponent_pacs_.push_back(p);
    }
  }
  int visiblePelletCount; // all pellets in sight
  input_ >> visiblePelletCount; input_.ignore();
  DEBUG("reading pellets");
  for (int i = 0; i < visiblePelletCount; i++) {
    Pellet p;
    input_ >> p; input_.ignore();
    pellets_.push_back(p);
  }
  DEBUG("reading DONE");
  return true;
}

std::vector<std::string> GameController::computeSolution()
{
  std::vector<std::string> result;
  for (const auto& pack : my_pacs_)
  {
    int small_distance = BIG_DIST;
    int big_distance = BIG_DIST;
    bool big_one = false;
    Point small_target_({0, 0});
    Point big_target_({0, 0});
    for (const auto& pellet : pellets_)
    {
      if (pellet.value == 10)
      {
        big_one = true;
        if (distance(pack.position, pellet.position) < big_distance)
        {
          big_distance = distance(pack.position, pellet.position);
          big_target_ = pellet.position;
        }
      }
      else
      {
        if (distance(pack.position, pellet.position) < small_distance)
        {
          small_distance = distance(pack.position, pellet.position);
          small_target_ = pellet.position;
        }
      }
    }
    if (big_one)
    {
      result.push_back("MOVE " + std::to_string(pack.id) + " " + std::to_string(big_target_.x)
        + " " + std::to_string(big_target_.y));
    }
    else
    {
      result.push_back("MOVE " + std::to_string(pack.id) + " " + std::to_string(small_target_.x)
        + " " + std::to_string(small_target_.y));
    }
  }
  return result;
}

}  // namespace gamecontroller
}  // namespace codingame
