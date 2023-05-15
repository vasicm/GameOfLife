  #include "GameOfLifeFileExporter.hpp"

  GameOfLifeFileExporter::GameOfLifeFileExporter(std::string filename) : m_filename(filename) {}

  void GameOfLifeFileExporter::exportState(const std::shared_ptr<GameOfLife> &gameOfLife) {
    // Create and open a text file
    std::ofstream MyFile(m_filename);

    MyFile << gameOfLife->getCurrentBoardState()->getWidth() << " "
           << gameOfLife->getCurrentBoardState()->getHeight() << std::endl;

    MyFile << gameOfLife->getInitialNumberOfGenerations() << " "
           << gameOfLife->getTimeIncrementInMs() << std::endl;
    // Write to the file
    MyFile << gameOfLife->getCurrentBoardState()->toString("1", "0") << std::endl;

    // Close the file
    MyFile.close();
  }
