#include <gtest/gtest.h>
#include "game_of_life.hpp"
#include "gmock/gmock.h"

class MockBoard : public Board {
  public:
   static Cell alive;
   static Cell dead;
   MockBoard(): Board(0, 0) {}
   MOCK_METHOD(size_t, GetWidth, (), (const, override));
   MOCK_METHOD(size_t, GetHeight, (), (const, override));
   MOCK_METHOD1(BracketOp, Cell&(const Index&));
   virtual Cell& operator[](const Index& index) {
    return BracketOp(index);
   }
};

Cell MockBoard::alive = Cell::kAlive;
Cell MockBoard::dead = Cell::kDead;

TEST(GameOfLife, TestCheckCellMethod)
{
  MockBoard* board = new MockBoard();
  EXPECT_CALL(*board, GetWidth())
    .Times(1)
    .WillOnce(testing::Return(8));
  EXPECT_CALL(*board, GetHeight())
    .Times(1)
    .WillOnce(testing::Return(12));

  EXPECT_CALL(*board, BracketOp(testing::_))
    .Times(10)
    .WillOnce(testing::ReturnRef(MockBoard::alive))
    .WillOnce(testing::ReturnRef(MockBoard::alive))
    .WillOnce(testing::ReturnRef(MockBoard::alive))
    .WillRepeatedly(testing::ReturnRef(MockBoard::dead));

  std::shared_ptr<GameOfLife> gof = std::make_shared<GameOfLife>(std::shared_ptr<MockBoard>(board), 10, 10);

  ASSERT_EQ(gof->CheckCell(3, 3), Cell::kAlive);
}

TEST(GameOfLife, TestActiveNeighborCountMethod)
{
  MockBoard* board = new MockBoard();

  EXPECT_CALL(*board, GetWidth())
    .Times(1)
    .WillOnce(testing::Return(8));
  EXPECT_CALL(*board, GetHeight())
    .Times(1)
    .WillOnce(testing::Return(12));

  EXPECT_CALL(*board, BracketOp(testing::_))
    .Times(9)
    .WillOnce(testing::ReturnRef(MockBoard::alive))
    .WillOnce(testing::ReturnRef(MockBoard::alive))
    .WillOnce(testing::ReturnRef(MockBoard::alive))
    .WillOnce(testing::ReturnRef(MockBoard::alive))
    .WillRepeatedly(testing::ReturnRef(MockBoard::dead));

  std::shared_ptr<GameOfLife> gof = std::make_shared<GameOfLife>(std::shared_ptr<MockBoard>(board), 10, 10);

  ASSERT_EQ(gof->ActiveNeighborCount(3, 3), 4);
}
