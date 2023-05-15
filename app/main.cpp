#include <iostream>
#include <string>

#include "TheGame.hpp"
#include "user_interface/StdUserInterface.hpp"
#include "GameOfLifeFactory.hpp"

#include <spdlog/spdlog.h>
#include <pngwriter.h>
#include <string>

int main(int argc, char* argv[]) {
    std::shared_ptr<StdUserInterface> stdUserInterface = std::make_shared<StdUserInterface>();

    GameOfLifeFactory factory{stdUserInterface};

    TheGame service{stdUserInterface};

    std::shared_ptr<GameOfLife> gameOfLife =
                factory
                .GetLoader(argc == 2 ? argv[1] : "")
                ->create();

    service.executeSimulation(gameOfLife);
    return 0;
}
