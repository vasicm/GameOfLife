#pragma once

#include <iostream>

#include "user_interface.hpp"

class StdUserInterface : public UserInterface {
 private:
  void DisplayMainMenu();

 public:
  int GetWidth();
  int GetHeight();
  int GetNumberOfGenerations();
  int GetTimeIncrementInMs();
  InputOption GetInputOption();
  std::string GetFileName();
  void ShowBoard(const std::shared_ptr<Board>& board);
  void ShowErrorMessage(std::string message);
};
