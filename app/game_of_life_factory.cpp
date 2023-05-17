#include "game_of_life_factory.hpp"

std::shared_ptr<GameOfLifeLoader> GameOfLifeFactory::GetRandomValuesLoader() {
  size_t width = user_interface->GetWidth();
  size_t height = user_interface->GetHeight();
  int genNumber = user_interface->GetNumberOfGenerations();
  int timeIncrementInMs = user_interface->GetTimeIncrementInMs();

  std::shared_ptr<GameOfLifeLoader> loader =
      std::make_shared<RandomValuesGameOfLifeLoader>(width, height, genNumber,
                                                     timeIncrementInMs);

  return loader;
}

std::shared_ptr<GameOfLifeLoader> GameOfLifeFactory::GetFromFileLoader(
    std::string filename) {
  std::shared_ptr<GameOfLifeLoader> loader =
      std::make_shared<GameOfLifeFromFileLoader>(filename);

  return loader;
}

GameOfLifeFactory::GameOfLifeFactory(
    std::shared_ptr<UserInterface> user_interface)
    : user_interface(user_interface) {}

std::shared_ptr<GameOfLifeLoader> GameOfLifeFactory::GetLoader(
    std::string filename) {
  std::shared_ptr<GameOfLifeLoader> loader;

  if (filename.empty()) {
    loader = GetRandomValuesLoader();
  } else {
    loader = GetFromFileLoader(filename);
  }

  return loader;
}
