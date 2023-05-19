#pragma once

#include <chrono>
#include <functional>
#include <iostream>
#include <map>
#include <string>
#include <thread>
#include <vector>

#include "exporter/game_of_life_file_exporter.hpp"
#include "exporter/game_of_life_png_exporter.hpp"
#include "game_of_life.hpp"
#include "user_interface/input_option.hpp"
#include "user_interface/user_interface.hpp"

class TheGame {
 private:
  // Instance of ‘UserInterface’ for communication with the end user.
  std::shared_ptr<UserInterface> user_interface_;
 public:
  TheGame(std::shared_ptr<UserInterface> user_interface);

  void ExecuteInitialSimulation(std::shared_ptr<GameOfLife> game_of_life);

  // The method returns a collection of all allowed actions in a map structure
  // where the 'key' is the enum value of the action,
  // and the 'value' is the lambda function that performs the appropriate action.
  static std::map<InputOption, bool (*)(std::shared_ptr<GameOfLife>& game_of_life,
                                        std::shared_ptr<UserInterface>&)>
  GetActions();

  // Performs a selected action on a specified object.
  bool ExecuteAction(
      std::map<InputOption, bool (*)(std::shared_ptr<GameOfLife>& gameOfLife,
                                     std::shared_ptr<UserInterface>&)>
          actions,
      InputOption option, std::shared_ptr<GameOfLife>& game_of_life);

  // Generates board state to png file.
  static void SaveStateToPng(const std::shared_ptr<GameOfLife>& game_of_life);

  // Starts game
  void Start(std::shared_ptr<GameOfLife>& game_of_life);
};
