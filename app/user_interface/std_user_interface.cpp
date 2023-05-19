#include "std_user_interface.hpp"

void StdUserInterface::DisplayMainMenu() {
  std::cout << "1. Go back one generation" << std::endl;
  std::cout << "2. Go forward one generation" << std::endl;
  std::cout << "3. Save current state to a file" << std::endl;
  std::cout << "4. Quit" << std::endl;
}

void StdUserInterface::CleanInput() {
  std::string dump;
  std::getline(std::cin, dump);
}

int StdUserInterface::GetWidth() {
  std::cout << "Enter width: ";
  size_t width = 50;
  std::cin >> width;
  CleanInput();
  return width;
};

int StdUserInterface::GetHeight() {
  std::cout << "Enter height: ";
  size_t height = 20;
  std::cin >> height;
  CleanInput();
  return height;
};

int StdUserInterface::GetNumberOfGenerations() {
  std::cout << "Number of generations: ";
  int gen_number = 10;
  std::cin >> gen_number;
  CleanInput();
  return gen_number;
};

int StdUserInterface::GetTimeIncrementInMs() {
  std::cout << "Time increment in ms: ";
  int time_increment_in_ms = 1000;
  std::cin >> time_increment_in_ms;
  CleanInput();
  return time_increment_in_ms;
};

InputOption StdUserInterface::GetInputOption() {
  DisplayMainMenu();
  int choice = 4;
  std::cout << "Choose an option [default: 4]: ";
  std::string input;
  std::getline( std::cin, input );
  if (!input.empty()) {
    std::istringstream stream( input );
    stream >> choice;
  }

  return static_cast<InputOption>(choice);
};

std::string StdUserInterface::GetFileName() {
  std::string file_name;
  std::cout << "Enter filename: ";
  std::cin >> file_name;

  CleanInput();
  return file_name;
};

void StdUserInterface::ShowBoard(const std::shared_ptr<Board>& board, int generation) {
  std::cout << "Generation: " << generation << "." << std::endl;
  std::cout << board->ToString("x", "-") << std::endl;
}

void StdUserInterface::ShowErrorMessage(std::string message) {
  std::cout << "\033[31m" << message << "\033[0m" << std::endl;
}
