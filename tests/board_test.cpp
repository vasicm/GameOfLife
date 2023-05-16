#include <gtest/gtest.h>
#include "core/board.hpp"

TEST(BoardTest, TestGetWidthMethod)
{
  Board board{10, 20};
  ASSERT_EQ(board.GetWidth(), 10);
}

TEST(BoardTest, TestGetHeightMethod)
{
  Board board{10, 20};
  ASSERT_EQ(board.GetHeight(), 20);
}

TEST(BoardTest, TestToStringMethod)
{
  Board board{10, 20};
  ASSERT_FALSE(board.ToString() == "");
}
