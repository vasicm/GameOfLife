#include <gtest/gtest.h>
#include "GameOfLifeService.hpp"

TEST(GameOfLife, TestCheckCellMethod)
{
  std::shared_ptr<Board> board = std::make_shared<Board>(10, 10);
  std::shared_ptr<GameOfLife> gof = std::make_shared<GameOfLife>(board, 10, 10);

  ASSERT_EQ(gof->CheckCell(3, 3), false);
}

TEST(GameOfLife, TestActiveNeighborCountMethod)
{
  std::shared_ptr<Board> board = std::make_shared<Board>(10, 10);
  std::shared_ptr<GameOfLife> gof = std::make_shared<GameOfLife>(board, 10, 10);

  ASSERT_EQ(gof->ActiveNeighborCount(3, 3), 0);
}
