#include "game_of_life.hpp"
#include "loader/game_of_life_from_file_loader.hpp"
#include "loader/random_values_game_of_life_loader.hpp"
#include "user_interface/user_interface.hpp"

class GameOfLifeFactory {
 private:
  // Instance of ‘UserInterface’ for communication with the end user.
  std::shared_ptr<UserInterface> user_interface_;


  // Returns loaders that create an instance of 'GameOfLife' based on the entered values
  // from the standard input. And fill board fields with random values.
  std::shared_ptr<GameOfLifeLoader> GetRandomValuesLoader();

  // Returns loaders that create an instance of 'GameOfLife' based on data in a text file,
  // which location can be specified by the argument
  std::shared_ptr<GameOfLifeLoader> GetFromFileLoader(std::string file_name);

 public:
  GameOfLifeFactory(std::shared_ptr<UserInterface> user_interface);

  // Returns loaders that create an instance of 'GameOfLife' based on data in a text file if the filename is specified.
  // Otherwise, it returns loaders that create an instance of 'GameOfLife' based on the entered values.
  std::shared_ptr<GameOfLifeLoader> GetLoader(std::string file_name);
};
