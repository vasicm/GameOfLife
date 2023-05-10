#include <iostream>
#include <string>

#include "GameOfLifeService.hpp"

int main(int argc, char* argv[]) {
  std::cout << std::endl << argc << std::endl;
  std::cout << argv[0] << std::endl;

  if (argc == 2) {
    std::string str = argv[1];
    std::cout << str << std::endl;
  }
  GameOfLifeService service;
  service.executeSimulation();

  return 0;
}
