#include <iostream>

#include "GameController/Debug.hpp"
#include "GameController/GameController.hpp"

using codingame::gamecontroller::GameController;

int main()
{
  GameController gc(std::cin);
  while (true)
  {
    gc.readInput();
    for (const auto& cmd : gc.computeSolution())
    {
      std::cout << cmd << "|";
    }
    std::cout << std::endl;
  }
  return 0;
}
