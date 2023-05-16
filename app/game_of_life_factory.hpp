#include "game_of_life.hpp"
#include "loader/game_of_life_from_file_loader.hpp"
#include "loader/random_values_game_of_life_loader.hpp"
#include "user_interface/user_interface.hpp"

class GameOfLifeFactory {
 private:
  std::shared_ptr<UserInterface> user_interface;

  std::shared_ptr<GameOfLifeLoader> GetFromStdIn() {
    size_t width = user_interface->GetWidth();
    size_t height = user_interface->GetHeight();
    int genNumber = user_interface->GetNumberOfGenerations();
    int timeIncrementInMs = user_interface->GetTimeIncrementInMs();

    std::shared_ptr<GameOfLifeLoader> loader =
        std::make_shared<RandomValuesGameOfLifeLoader>(width, height, genNumber,
                                                       timeIncrementInMs);

    return loader;
  }

  std::shared_ptr<GameOfLifeLoader> GetFromFile(std::string filename) {
    std::shared_ptr<GameOfLifeLoader> loader =
        std::make_shared<GameOfLifeFromFileLoader>(filename);

    return loader;
  }

 public:
  GameOfLifeFactory(std::shared_ptr<UserInterface> user_interface)
      : user_interface(user_interface) {}

  std::shared_ptr<GameOfLifeLoader> GetLoader(std::string filename) {
    std::shared_ptr<GameOfLifeLoader> loader;

    if (filename.empty()) {
      loader = GetFromStdIn();
    } else {
      loader = GetFromFile(filename);
    }

    return loader;
  }
};
