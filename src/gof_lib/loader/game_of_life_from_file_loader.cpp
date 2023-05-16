#include "game_of_life_from_file_loader.hpp"
#include <regex>

GameOfLifeFromFileLoader::GameOfLifeFromFileLoader(std::string fileName)
    : m_fileName(fileName) {}

void GameOfLifeFromFileLoader::ValidateIfFileReachedEnd(std::ifstream& myfile) {
  std::string line;
  if(getline(myfile, line)) {
    throw(std::logic_error("The file is not in a valid format. The file has too many lines."));
  }
}

std::istringstream GameOfLifeFromFileLoader::GetLineAsStream(std::ifstream& myfile, const std::regex& regex) noexcept(false) {

  std::string line;

  if(!getline(myfile, line)) {
    throw(std::logic_error("The file is not in a valid format. The file does not have enough lines."));
  }

  if (!regex_match(line, regex)) {
    throw(std::logic_error("The file is not in a valid format. Invalid line: '" + line +"'"));
  }

  std::istringstream is(line);

  return is;
}

std::regex GameOfLifeFromFileLoader::GetRegexForBoardLine(size_t width) {
  std::stringstream ss;
  ss << "^[01]{" << width << "}$";
  std::string str = ss.str();

  return std::regex(str);
}

std::shared_ptr<GameOfLife> GameOfLifeFromFileLoader::Create() {
  std::ifstream myfile;
  std::regex twoIntegers("^\\d+\\s\\d+$");

  myfile.open(m_fileName);

  std::istringstream is = GetLineAsStream(myfile, twoIntegers);

  size_t width = 0;
  is >> width;
  size_t height = 0;
  is >> height;

  is = GetLineAsStream(myfile, twoIntegers);
  int genNumber = 0;
  is >> genNumber;
  int timeIncrementInMs = 0;
  is >> timeIncrementInMs;

  auto board = std::make_shared<Board>(width, height);
  std::regex boardLineRegex = GetRegexForBoardLine(width);

  for (size_t i = 0; i < board->GetHeight(); i++) {
    std::string str;
    is = GetLineAsStream(myfile, boardLineRegex);
    is >> str;

    for (size_t j = 0; j < board->GetWidth(); j++) {
      (*board)[{i, j}] = (str.at(j) == '1' ? Cell::kAlive : Cell::kDead);
    }
  }
  ValidateIfFileReachedEnd(myfile);
  myfile.close();

  return std::make_shared<GameOfLife>(board, genNumber, timeIncrementInMs);
}
