#pragma once

#include <iostream>
#include "UserInterface.hpp"

class StdUserInterface : public UserInterface {
private:

  void DisplayMainMenu() {
    std::cout << "1. Go back one generation" << std::endl;
    std::cout << "2. Go forward one generation" << std::endl;
    std::cout << "3. Save current state to a file" << std::endl;
    std::cout << "4. Quit" << std::endl;
  }

public:
    StdUserInterface(){};

    int GetWidth() {
        std::cout << "Enter width: ";
        size_t width = 50;
        std::cin >> width;
        return width;
    };

    int GetHeight() {
        std::cout << "Enter height: ";
        size_t height = 20;
        std::cin >> height;
        return height;
    };

    int GetNumberOfGenerations() {
        std::cout << "Number of generations: ";
        int genNumber = 10;
        std::cin >> genNumber;
        return genNumber;
    };

    int GetTimeIncrementInMs() {
        std::cout << "Time increment in ms: ";
        int timeIncrementInMs = 1000;
        std::cin >> timeIncrementInMs;
        return timeIncrementInMs;
    };

    InputOption GetInputOption() {
        DisplayMainMenu();
        int choice;
        std::cout << "Choose an option [default: 4]: ";
        std::cin >> choice;
        return static_cast<InputOption>(choice);
    };

    std::string GetFileName() {
        std::string filename;
        std::cout << "Enter filename: ";
        std::cin >> filename;
        return filename;
    };

    void ShowBoard(const std::shared_ptr<Board>& board) {
        std::cout << board->toString("x", "-")
              << std::endl;
    }

    void ShowErrorMessage(std::string message) {
        std::cout << message << std::endl;
    }
};
