#include <iostream>
#include <string>

#include "GameOfLifeService.hpp"

#include <spdlog/spdlog.h>
#include <pngwriter.h>
#include <string>

int main(int argc, char* argv[]) {
    std::shared_ptr<GameOfLife> gameOfLife;
    GameOfLifeService service;

    if (argc == 2) {
        std::string str = argv[1];
        gameOfLife = service.GetFromFile(str);
    }
    else {
        gameOfLife = service.GetFromStdIn();
    }
    service.executeSimulation(gameOfLife);
    return 0;
}
