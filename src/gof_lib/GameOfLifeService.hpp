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
    // cin >> width;

    std::cout << "Enter height: ";
    size_t height = 20;
    // cin >> height;

    std::cout << "Number of generations: ";
    int genNumber = 10;
    // cin >> genNumber;

    std::cout << "Time increment in ms: ";
    int timeIncrementInMs = 1000;
    // cin >> timeIncrementInMs;
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
    std::cout << gameOfLife->getCurrentBoardState()->toString() << std::endl;
    for (int i = 0; i < gameOfLife->getInitialNumberOfGenerations(); i++) {
      std::this_thread::sleep_for(
          std::chrono::milliseconds(gameOfLife->getTimeIncrementInMs()));
      gameOfLife->goForward();
      std::cout << gameOfLife->getCurrentBoardState()->toString() << std::endl
                << std::endl;
    }
  }

  static void goBack(GameOfLife& gameOfLife) {
    std::cout << "Choosed: 'Go back one generation'" << std::endl;
    gameOfLife.goBack();
    std::cout << gameOfLife.getCurrentBoardState()->toString() << std::endl;
  }

  static void goForward(GameOfLife& gameOfLife) {
    std::cout << "Choosed: 'Go forward one generation'" << std::endl;
    gameOfLife.goForward();
    std::cout << gameOfLife.getCurrentBoardState()->toString() << std::endl;
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

  void executeSimulation() {
    // auto GameOfLife = GetFromStdIn();
    // TODO: temporary solution
    auto gameOfLife = GetFromFile("/home/vasic/Documents/CppPractice/repo/GameOfLife/101.txt");

    executeInitialSimulation(gameOfLife);

    auto actions = getActions();

    int option = 4;
    do {
      displayMainMenu();
      option = getInput();
      executeAction(actions, option, *gameOfLife);
    } while (option != 4);
  }
};
