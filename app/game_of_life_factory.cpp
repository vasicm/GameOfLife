#include "game_of_life_factory.hpp"

std::shared_ptr<GameOfLifeLoader> GameOfLifeFactory::GetRandomValuesLoader() {
  size_t width = user_interface_->GetWidth();
  size_t height = user_interface_->GetHeight();
  int gen_number = user_interface_->GetNumberOfGenerations();
  int time_increment_in_ms = user_interface_->GetTimeIncrementInMs();

  std::shared_ptr<GameOfLifeLoader> loader =
      std::make_shared<RandomValuesGameOfLifeLoader>(width, height, gen_number,
                                                     time_increment_in_ms);

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
    : user_interface_(user_interface) {}

std::shared_ptr<GameOfLifeLoader> GameOfLifeFactory::GetLoader(
    std::string file_name) {
  std::shared_ptr<GameOfLifeLoader> loader;

  if (file_name.empty()) {
    loader = GetRandomValuesLoader();
  } else {
    loader = GetFromFileLoader(file_name);
  }

  return loader;
}
