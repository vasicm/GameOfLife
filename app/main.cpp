#include <pngwriter.h>
#include <spdlog/spdlog.h>

#include <iostream>
#include <regex>
#include <string>

#include "game.hpp"
#include "game_of_life_factory.hpp"
#include "user_interface/std_user_interface.hpp"

int main(int argc, char* argv[]) {
  std::shared_ptr<StdUserInterface> stdUserInterface =
      std::make_shared<StdUserInterface>();

  GameOfLifeFactory factory{stdUserInterface};

  TheGame service{stdUserInterface};

   std::shared_ptr<GameOfLife> game_of_life =
       factory.GetLoader(argc == 2 ? argv[1] : "")->Create();

  service.Start(game_of_life);
  return 0;
}
