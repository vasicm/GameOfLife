#pragma once

#include <chrono>
#include <functional>
#include <iostream>
#include <map>
#include <string>
#include <thread>
#include <vector>

#include "GameOfLife.hpp"
#include "GameOfLifeExporter.hpp"
#include "UserInterface.hpp"
#include "InputOption.hpp"

class TheGame {
 private:
    std::shared_ptr<UserInterface> user_interface;
 public:
  TheGame(std::shared_ptr<UserInterface> user_interface) : user_interface(user_interface) {}

  void executeInitialSimulation(std::shared_ptr<GameOfLife> gameOfLife) {
    user_interface->ShowBoard(gameOfLife->getCurrentBoardState());
    for (int i = 0; i < gameOfLife->getInitialNumberOfGenerations(); i++) {
      std::this_thread::sleep_for(
          std::chrono::milliseconds(gameOfLife->getTimeIncrementInMs()));
      gameOfLife->goForward();
      user_interface->ShowBoard(gameOfLife->getCurrentBoardState());
      saveStateToPng(gameOfLife);
    }
  }

  static std::map<InputOption, bool (*)(std::shared_ptr<GameOfLife> &gameOfLife, std::shared_ptr<UserInterface>&)> getActions() {

    std::map<InputOption, bool (*)(std::shared_ptr<GameOfLife> &gameOfLife, std::shared_ptr<UserInterface>&)> actions;

    actions.emplace(InputOption::Default, [](std::shared_ptr<GameOfLife>& gameOfLife, std::shared_ptr<UserInterface>& user_interface) {
        user_interface->ShowErrorMessage("Invalid action, try again!");
        return true;
    });

    actions.emplace(InputOption::GoBack, [](std::shared_ptr<GameOfLife>& gameOfLife, std::shared_ptr<UserInterface>& user_interface) {
        gameOfLife->goBack();
        return true;
    });
    actions.emplace(InputOption::GoForward, [](std::shared_ptr<GameOfLife>& gameOfLife, std::shared_ptr<UserInterface>& user_interface) {
        gameOfLife->goForward();
        return true;
    });
    actions.emplace(InputOption::SaveToFile, [](std::shared_ptr<GameOfLife>& gameOfLife, std::shared_ptr<UserInterface>& user_interface) {
        std::string filename = user_interface->GetFileName();
        GameOfLifeFileExporter exporter{filename};
        exporter.exportState(gameOfLife);
        return true;
    });

    actions.emplace(InputOption::Quit, [](std::shared_ptr<GameOfLife>& gameOfLife, std::shared_ptr<UserInterface>& user_interface) {
        return false;
    });

    return actions;
  }

  bool executeAction(std::map<InputOption, bool (*)(std::shared_ptr<GameOfLife> &gameOfLife, std::shared_ptr<UserInterface>&)> actions,
                     InputOption option,
                     std::shared_ptr<GameOfLife>& gameOfLife) {
    auto action = actions.find(option);
    action = action != actions.end() ? action : actions.find(InputOption::Default);

    bool value = action->second(gameOfLife, user_interface);
    user_interface->ShowBoard(gameOfLife->getCurrentBoardState());

    return value;
  }

  static void saveStateToPng(const std::shared_ptr<GameOfLife>& gameOfLife) {
    std::ostringstream filename;
    filename << "gen" << gameOfLife->getCurrentNumberOfGenerations() << ".png";
    GameOfLifePngExporter pngExporter{filename.str(), 20};
    pngExporter.exportState(gameOfLife);
  }

  void executeSimulation(std::shared_ptr<GameOfLife>& gameOfLife) {
    executeInitialSimulation(gameOfLife);

    auto actions = getActions();

    InputOption option = InputOption::Quit;
    bool continueExecution = false;
    do {
      option = user_interface->GetInputOption();
      continueExecution = executeAction(actions, option, gameOfLife);
      saveStateToPng(gameOfLife);
    } while (continueExecution);
  }
};
