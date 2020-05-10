
#include "GameController/Debug.hpp"
#include "GameController/GameController.hpp"

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
  big_one_(false),
  dest_({0, 0}),
  alt_dest_({0, 0})
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
  int my_pos_x(0);
  int my_pos_y(0);
  int myScore;
  int opponentScore;
  input_ >> myScore >> opponentScore; input_.ignore();
  int visiblePacCount; // all your pacs and enemy pacs in sight
  input_ >> visiblePacCount; input_.ignore();
  DEBUG("reading pacs");
  for (int i = 0; i < visiblePacCount; i++) {
    int pacId; // pac number (unique within a team)
    bool mine; // true if this pac is yours
    int x; // position in the grid
    int y; // position in the grid
    std::string typeId; // unused in wood leagues
    int speedTurnsLeft; // unused in wood leagues
    int abilityCooldown; // unused in wood leagues
    input_ >> pacId >> mine >> x >> y >> typeId >> speedTurnsLeft >> abilityCooldown; input_.ignore();
    if (mine)
    {
      my_pos_x = x;
      my_pos_y = y;
    }
  }
  int visiblePelletCount; // all pellets in sight
  int distance = BIG_DIST;
  int alt_distance = BIG_DIST;
  input_ >> visiblePelletCount; input_.ignore();
  DEBUG("reading pellets");
  for (int i = 0; i < visiblePelletCount; i++) {
    int x;
    int y;
    int value; // amount of points this pellet is worth
    input_ >> x >> y >> value; input_.ignore();
    if (value == 10)
    {
      big_one_ = true;
      if (dist(my_pos_x, my_pos_y, x, y) < distance)
      {
        dest_.x = x;
        dest_.y = y;
        distance = dist(my_pos_x, my_pos_y, x, y);
      }
    }
    else
    {
      if (dist(my_pos_x, my_pos_y, x, y) < alt_distance)
      {
        alt_dest_.x = x;
        alt_dest_.y = y;
        alt_distance = dist(my_pos_x, my_pos_y, x, y);
      }
    }
  }
  DEBUG("reading DONE");
  return true;
}

std::string GameController::computeSolution()
{
  std::string result("MOVE 0 ");
  if (big_one_)
  {
    result += std::to_string(dest_.x);
    result += " ";
    result += std::to_string(dest_.y);
  }
  else
  {
    result += std::to_string(alt_dest_.x);
    result += " ";
    result += std::to_string(alt_dest_.y);
  }
  return result;
}

}  // namespace gamecontroller
}  // namespace codingame
