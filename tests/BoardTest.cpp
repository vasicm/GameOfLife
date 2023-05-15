#include <gtest/gtest.h>
#include "core/Board.hpp"

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
