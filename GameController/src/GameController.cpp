
#include <algorithm>
#include <optional>
#include <random>
#include <set>
#include <string>
#include <utility>
#include <vector>

#include "GameController/Debug.hpp"
#include "GameController/GameController.hpp"
#include "GameController/Pacman.hpp"
#include "GameController/Pellet.hpp"
#include "GameController/Point.hpp"

#define BIG_DIST 100000

// helper functions
namespace
{
std::string moveCmd(int id, const codingame::gamecontroller::Point& p)
{
  return "MOVE " + std::to_string(id) + " " + std::to_string(p.x)  + " " + std::to_string(p.y);
}
std::string switchCmd(int id, const std::string& type)
{
  return "SWITCH " + std::to_string(id) + " " + type;
}
std::string speedCmd(int id)
{
  return "SPEED " + std::to_string(id);
}
bool winsAgainst(const std::string& mine, const std::string& theirs)
{
  if (mine == "ROCK" && theirs == "SCISSORS") return true;
  else if (mine == "PAPER" && theirs == "ROCK") return true;
  else if (mine == "SCISSORS" && theirs == "PAPER") return true;
  else return false;
}
std::string getWinningType(const std::string& theirs)
{
  if (theirs == "ROCK") return "PAPER";
  if (theirs == "PAPER") return "SCISSORS";
  if (theirs == "SCISSORS") return "ROCK";
  return "ERROR";
}
bool insideBounds(const codingame::gamecontroller::Point& p, int lb, int ub)
{
  if (p.x >= lb && p.x < ub) return true;
  else return false;
}
}

namespace codingame
{
namespace gamecontroller
{

GameController::GameController(std::istream& input):
  input_(input),
  width_(0),
  heigth_(0),
  my_score_(0),
  opponent_score_(0),
  my_pacs_(),
  opponent_pacs_(),
  pellets_()
{
  input_ >> width_ >> heigth_; input_.ignore();
  DEBUG(width_ << " " << heigth_);
  for (int i = 0; i < heigth_; i++) {
    std::string row;
    std::getline(input_, row);
    for (int j=0; (unsigned)j < row.size(); j++)
    {
      if (row[j] == ' ') all_possible_fields_.push_back(Point({j, i}));
    }
    DEBUG(row);
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

bool GameController::printInput()
{
  DEBUG(my_score_ << " " << opponent_score_);
  DEBUG(my_pacs_.size() + opponent_pacs_.size());
  for (const auto& p : my_pacs_)
    DEBUG(p);
  for (const auto& p : opponent_pacs_)
    DEBUG(p);
  DEBUG(pellets_.size());
  for (const auto& p : pellets_)
    DEBUG(p);
  return true;
}

std::vector<std::string> GameController::computeSolution()
{
  return sectorsStrategy();
}

/*
 * Basically assign some set of coordinates where each of the pacs can operate;
 * Then choose to either collect big pellets, small pellets, fight;
 * Works more or less, however there are still some situations when pacs can lock each other
 * It is partially resolved by going to random point in the sector, when there is nothing better to do;
 * There is a lot of unnecessary sorting and copy, but mehh whatever, it's fast enough
 */
std::vector<std::string> GameController::sectorsStrategy()
{
  DEBUG("sectorsStrategy");
  std::vector<std::string> result;
  int sector_width = width_/my_pacs_.size();  // integer division, last sector might be bigger
  // sector.first - beginning of sector
  // sector.second - past the end of sector
  std::vector<std::pair<int, int> > sectors(my_pacs_.size());
  for (size_t i = 0; i < my_pacs_.size(); i++)
  {
    sectors[i] = std::make_pair(i*sector_width, (i+1)*sector_width);
  }
  sectors.back().second = width_;  // last sector past the end correction due to integer division
  auto sectors2PacsMap = assignSectors2Pacs(sectors);
  for (size_t i = 0; i < sectors.size(); i++)
  {
    result.push_back(collectOrFight(sectors2PacsMap[i], sectors[i].first, sectors[i].second));
  }
  return result;
}

std::map<int, Pacman> GameController::assignSectors2Pacs(const std::vector<std::pair<int, int> >&)
{
  std::map<int, Pacman> result;
  auto sorted_pacs = my_pacs_;
  std::sort(sorted_pacs.begin(), sorted_pacs.end(), [](const Pacman& lhs, const Pacman& rhs)
  {
    return lhs.position.x < rhs.position.x;
  });
  for (size_t i = 0; i < sorted_pacs.size(); i++)
  {
    result[i] = sorted_pacs[i];
    DEBUG("pac " << sorted_pacs[i].id << " assigned " << i);
  }
  return result;
}

std::string GameController::collectOrFight(const Pacman& pac, int lb, int ub)
{
  DEBUG("collectOrFight");
  auto pac_comparator = [&pac](const Pacman& lhs, const Pacman& rhs)
  {
    return distance(pac.position, lhs.position) < distance(pac.position, rhs.position);
  };
  auto sorted_opponents = opponent_pacs_;
  DEBUG("sorting");
  std::sort(sorted_opponents.begin(), sorted_opponents.end(), pac_comparator);
  // fight!
  if (!sorted_opponents.empty() && distance(sorted_opponents.front().position, pac.position) == 1)
  {
    DEBUG("fighting");
    if (winsAgainst(pac.type_id, sorted_opponents.front().type_id))
    {
      return moveCmd(pac.id, sorted_opponents.front().position);
    }
    else
    {
      return switchCmd(pac.id, getWinningType(sorted_opponents.front().type_id));
    }
  }
  if (pac.ability_cooldown == 0)
  {
    return speedCmd(pac.id);
  }
  std::optional<Pellet> closest_big_pellet;
  std::optional<Pellet> closest_small_pellet;
  DEBUG("looking for closest point");
  for (const auto& p : pellets_)
  {
    if (p.value == 10)
    {
      if (!closest_big_pellet)
      {
        closest_big_pellet = p;
        continue;
      }
      if (distance(p.position, pac.position) < distance(closest_big_pellet->position, pac.position))
      {
        closest_big_pellet = p;
        continue;
      }
    }
    else
    {
      if (!closest_small_pellet)
      {
        closest_small_pellet = p;
        continue;
      }
      if (distance(p.position, pac.position) < distance(closest_small_pellet->position, pac.position))
      {
        closest_small_pellet = p;
        continue;
      }
    }
  }
  if (closest_big_pellet && insideBounds(closest_big_pellet->position, lb, ub))
  {
    DEBUG("go for big one in your sector");
    return moveCmd(pac.id, closest_big_pellet->position);
  }
  // chase the opponent!!!
  if (!sorted_opponents.empty() && insideBounds(sorted_opponents.front().position, lb, ub))
  {
    DEBUG("go for closest opponent in your sector");
    return moveCmd(pac.id, sorted_opponents.front().position);
  }
  if (closest_small_pellet && insideBounds(closest_small_pellet->position, lb, ub))
  {
    DEBUG("go for small one in your sector");
    return moveCmd(pac.id, closest_small_pellet->position);
  }
  // if nothing else to do, just go for anything
  DEBUG("go for whatever possible, random select from your sector");
  std::vector<Point> points_in_sector;
  for (const auto& p : all_possible_fields_)
  {
    if (insideBounds(p, lb, ub)) points_in_sector.push_back(p);
  }
  if (points_in_sector.empty())
  {
    DEBUG("No points in my sector, I will just stay here");
    return moveCmd(pac.id, pac.position);
  }
  std::random_device r;
  std::default_random_engine e1(r());
  std::uniform_int_distribution<int> uniform_dist(0, points_in_sector.size()-1);
  return moveCmd(pac.id, points_in_sector[uniform_dist(e1)]);
}

}  // namespace gamecontroller
}  // namespace codingame
