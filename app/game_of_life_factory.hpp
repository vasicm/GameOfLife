#include "game_of_life.hpp"
#include "loader/game_of_life_from_file_loader.hpp"
#include "loader/random_values_game_of_life_loader.hpp"
#include "user_interface/user_interface.hpp"

class GameOfLifeFactory {
 private:
  std::shared_ptr<UserInterface> user_interface;
  std::shared_ptr<GameOfLifeLoader> GetFromStdIn();
  std::shared_ptr<GameOfLifeLoader> GetFromFile(std::string filename);

 public:
  GameOfLifeFactory(std::shared_ptr<UserInterface> user_interface);
  std::shared_ptr<GameOfLifeLoader> GetLoader(std::string filename);
};
