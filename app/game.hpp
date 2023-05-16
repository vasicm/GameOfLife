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
  std::shared_ptr<UserInterface> user_interface;

 public:
  TheGame(std::shared_ptr<UserInterface> user_interface);
  void executeInitialSimulation(std::shared_ptr<GameOfLife> gameOfLife);
  static std::map<InputOption, bool (*)(std::shared_ptr<GameOfLife>& gameOfLife,
                                        std::shared_ptr<UserInterface>&)>
  getActions();
  bool executeAction(
      std::map<InputOption, bool (*)(std::shared_ptr<GameOfLife>& gameOfLife,
                                     std::shared_ptr<UserInterface>&)>
          actions,
      InputOption option, std::shared_ptr<GameOfLife>& gameOfLife);
  static void saveStateToPng(const std::shared_ptr<GameOfLife>& gameOfLife);
  void executeSimulation(std::shared_ptr<GameOfLife>& gameOfLife);
};
