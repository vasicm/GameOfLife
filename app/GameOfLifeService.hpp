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
#include "GameOfLifeLoader.hpp"

class GameOfLifeService {
 private:
 public:
  std::shared_ptr<GameOfLife> GetFromStdIn() {
    std::cout << "Enter width: ";
    size_t width = 50;
    std::cin >> width;

    std::cout << "Enter height: ";
    size_t height = 20;
    std::cin >> height;

    std::cout << "Number of generations: ";
    int genNumber = 10;
    std::cin >> genNumber;

    std::cout << "Time increment in ms: ";
    int timeIncrementInMs = 1000;
    std::cin >> timeIncrementInMs;
    std::cout << std::endl;
    std::shared_ptr<GameOfLifeLoader> loader =
        std::make_shared<RandomValuesGameOfLifeLoader>(width, height, genNumber,
                                                       timeIncrementInMs);

    return loader->create();
  }

  std::shared_ptr<GameOfLife> GetFromFile(std::string filename) {
    std::shared_ptr<GameOfLifeLoader> loader =
        std::make_shared<GameOfLifeFromFileLoader>(filename);

    return loader->create();
  }

  void executeInitialSimulation(std::shared_ptr<GameOfLife> gameOfLife) {
    printGameOfLife(*gameOfLife);
    for (int i = 0; i < gameOfLife->getInitialNumberOfGenerations(); i++) {
      std::this_thread::sleep_for(
          std::chrono::milliseconds(gameOfLife->getTimeIncrementInMs()));
      gameOfLife->goForward();
      printGameOfLife(*gameOfLife);
      saveStateToPng(*gameOfLife);
    }
  }

  static void goBack(GameOfLife& gameOfLife) {
    std::cout << "Choosed: 'Go back one generation'" << std::endl;
    gameOfLife.goBack();
    printGameOfLife(gameOfLife);
  }

  static void goForward(GameOfLife& gameOfLife) {
    std::cout << "Choosed: 'Go forward one generation'" << std::endl;
    gameOfLife.goForward();
    printGameOfLife(gameOfLife);
  }

  static void saveStateToFile(GameOfLife& gameOfLife) {
    std::cout << "Choosed: 'Save current state to a file'" << std::endl;
    std::string filename;
    std::cout << "Enter filename: ";
    std::cin >> filename;
    GameOfLifeFileExporter exporter{filename};
    exporter.exportState(gameOfLife);
    std::cout << "State exported to file: " << filename << std::endl;
  }

  static void printGameOfLife(GameOfLife& gameOfLife) {
    std::cout << gameOfLife.getCurrentBoardState()->toString("x", "-")
              << std::endl;
  }

  int getInput() {
    int choice;
    std::cout << "Choose an option [default: 4]: ";
    std::cin >> choice;
    return choice;
  }

  void displayMainMenu() {
    std::cout << "1. Go back one generation" << std::endl;
    std::cout << "2. Go forward one generation" << std::endl;
    std::cout << "3. Save current state to a file" << std::endl;
    std::cout << "4. Quit" << std::endl;
  }

  std::map<int, void (*)(GameOfLife& gameOfLife)> getActions() {
    std::map<int, void (*)(GameOfLife & gameOfLife)> actions;
    actions.emplace(1, goBack);
    actions.emplace(2, goForward);
    actions.emplace(3, saveStateToFile);
    return actions;
  }

  void executeAction(std::map<int, void (*)(GameOfLife& gameOfLife)> actions,
                     int option, GameOfLife& gameOfLife) {
    auto action = actions.find(option);

    if (action != actions.end()) {
      action->second(gameOfLife);
    } else if (option != 4) {
      std::cout << "Invalid action, try again!" << std::endl;
    }
  }

  static void saveStateToPng(GameOfLife& gameOfLife) {
    std::ostringstream filename;
    filename << "gen" << gameOfLife.getCurrentNumberOfGenerations() << ".png";
    GameOfLifePngExporter pngExporter{filename.str(), 20};
    pngExporter.exportState(gameOfLife);
  }

  void executeSimulation(std::shared_ptr<GameOfLife> gameOfLife) {
    executeInitialSimulation(gameOfLife);

    auto actions = getActions();

    int option = 4;
    do {
      displayMainMenu();
      option = getInput();
      executeAction(actions, option, *gameOfLife);
      saveStateToPng(*gameOfLife);
    } while (option != 4);
  }
};
