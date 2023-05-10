#pragma once

#include <string>

#include "GameOfLife.hpp"

// struct GameOfLifeExporter {
//   virtual void exportState(GameOfLife const& sim);
// };

class GameOfLifeFileExporter {
  std::string m_filename;

 public:
  GameOfLifeFileExporter(std::string filename) : m_filename(filename) {}

  void exportState(GameOfLife const& sim) {
    // Create and open a text file
    std::ofstream MyFile(m_filename);

    MyFile << sim.getCurrentBoardState()->getWidth() << " "
           << sim.getCurrentBoardState()->getHeight() << std::endl;

    MyFile << sim.getInitialNumberOfGenerations() << " "
           << sim.getTimeIncrementInMs() << std::endl;
    // Write to the file
    MyFile << sim.getCurrentBoardState()->toString() << std::endl;

    // Close the file
    MyFile.close();
  }
};

// class GameOfLifePngExporter : public GameOfLifeExporter {
//   std::string m_filename;

//  public:
//   GameOfLifePngExporter(std::string filename) : m_filename(filename) {}

//   void exportState(GameOfLife const& sim) {
//     // todo
//   }
// };