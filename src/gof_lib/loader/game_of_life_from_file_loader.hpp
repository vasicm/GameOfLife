#pragma once

#include <memory>
#include <string>
#include <regex>

#include "game_of_life_loader.hpp"

// A specific implementation of abstract class 'GameOfLifeLoader'.
// Allows loading/creating a 'GameOfLife' instance from a file.
class GameOfLifeFromFileLoader : public GameOfLifeLoader {
 private:
  // The name/location of the file from which the loading will be made.
  std::string m_fileName;

  // Checks if the file reached the end. If not, the method will
  // throw a validation exception. It is used at the end of parsing
  // to prove that there are no more lines in the file.
  // No more than it is specified.
  void ValidateIfFileReachedEnd(std::ifstream& myfile);

  // Read the next line from the 'ifstream'.
  // Validate the line with specified 'regex'.
  // Create 'istringstream' from taht line, to allow reading from that line.
  std::istringstream GetLineAsStream(std::ifstream& myfile, const std::regex& regex) noexcept(false);

  // Creates a 'regex' for validation of a board line.
  // The line depends on 'width' so it needs to be created dynamically.
  std::regex GetRegexForBoardLine(size_t width);
 public:

  // Constructor that accepts the name/location of the file from which the loading will be made.
  GameOfLifeFromFileLoader(std::string fileName);

  // Creates 'GameOfLife' instance
  std::shared_ptr<GameOfLife> Create() override;
};
