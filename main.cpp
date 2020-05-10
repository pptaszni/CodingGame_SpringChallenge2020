#include <iostream>

#include "GameController/GameController.hpp"

using codingame::gamecontroller::GameController;

int main()
{
  GameController gc(std::cin);
  while (true)
  {
    gc.readInput();
    std::cout << gc.computeSolution() << std::endl;
  }
  return 0;
}
