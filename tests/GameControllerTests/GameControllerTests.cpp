#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <fstream>
#include <memory>

#include "GameController/GameController.hpp"

using codingame::gamecontroller::GameController;

class GameControllerFixture: public ::testing::Test {
 protected:
  GameControllerFixture():
    test_data_dir_(__FILE__)
  {
    test_data_dir_ = test_data_dir_.substr(0, test_data_dir_.find("GameControllerTests.cpp"));
    test_data_dir_ += "../test_data/";
  }
  std::string test_data_dir_;
  std::unique_ptr<GameController> sut_;
};

/*
 * Nothing special in this testcase, just checking if all the data is read correctly
 * without leaving things in the buffer;
 */
TEST_F(GameControllerFixture, readInputAndComputeSolutionCorrectly)
{
  std::ifstream game_data(test_data_dir_ + "35_13_map_2rounds.dat");
  sut_.reset(new GameController(game_data));
  ASSERT_TRUE(sut_->readInput());
  ASSERT_TRUE(!sut_->computeSolution().empty());
  ASSERT_TRUE(sut_->readInput());
  ASSERT_TRUE(!sut_->computeSolution().empty());
}
