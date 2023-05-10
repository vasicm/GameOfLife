#include <gtest/gtest.h>
#include "GameOfLifeService.hpp"

TEST(BoardTest, TestGetWidthMethod)
{
  Board board{10, 20};
  ASSERT_EQ(board.getWidth(), 10);
}

TEST(BoardTest, TestGetHeightMethod)
{
  Board board{10, 20};
  ASSERT_EQ(board.getHeight(), 20);
}

TEST(BoardTest, TestToStringMethod)
{
  Board board{10, 20};
  ASSERT_FALSE(board.toString() == "");
}

int main(int argc, char **argv)
{
 testing::InitGoogleTest(&argc, argv);
 return RUN_ALL_TESTS();
}
