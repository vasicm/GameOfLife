#include "game.hpp"

TheGame::TheGame(std::shared_ptr<UserInterface> user_interface)
    : user_interface_(user_interface) {}

void TheGame::ExecuteInitialSimulation(std::shared_ptr<GameOfLife> game_of_life) {
  user_interface_->ShowBoard(game_of_life->GetCurrentBoardState(), game_of_life->GetCurrentNumberOfGenerations());
  SaveStateToPng(game_of_life);
  for (int i = 0; i < game_of_life->GetInitialNumberOfGenerations(); i++) {
    auto begin = std::chrono::system_clock::now();
    auto target_time =
        begin + std::chrono::milliseconds(game_of_life->GetTimeIncrementInMs());

    game_of_life->GoForward();
    user_interface_->ShowBoard(game_of_life->GetCurrentBoardState(), game_of_life->GetCurrentNumberOfGenerations());
    SaveStateToPng(game_of_life);

    std::this_thread::sleep_until(target_time);
  }
}

std::map<InputOption, bool (*)(std::shared_ptr<GameOfLife>& game_of_life,
                               std::shared_ptr<UserInterface>&)>
TheGame::GetActions() {
  std::map<InputOption, bool (*)(std::shared_ptr<GameOfLife> & game_of_life,
                                 std::shared_ptr<UserInterface>&)>
      actions;

  actions.emplace(
      InputOption::kDefault,
      [](std::shared_ptr<GameOfLife>& game_of_life,
         std::shared_ptr<UserInterface>& user_interface) {
        user_interface->ShowErrorMessage("Invalid action, try again!");
        return true;
      });

  actions.emplace(InputOption::kGoBack,
                  [](std::shared_ptr<GameOfLife>& game_of_life,
                     std::shared_ptr<UserInterface>& user_interface) {

                    try
                    {
                      game_of_life->GoBack();
                      SaveStateToPng(game_of_life);
                      user_interface->ShowBoard(game_of_life->GetCurrentBoardState(), game_of_life->GetCurrentNumberOfGenerations());
                    }
                    catch(const std::length_error& e)
                    {
                        user_interface->ShowErrorMessage("It's not possible to go back");
                    }
                    catch(...)
                    {
                        user_interface->ShowErrorMessage("Intertnal error!!!");
                    }

                    return true;
                  });

  actions.emplace(InputOption::kGoForward,
                  [](std::shared_ptr<GameOfLife>& game_of_life,
                     std::shared_ptr<UserInterface>& user_interface) {
                    game_of_life->GoForward();
                    SaveStateToPng(game_of_life);
                    user_interface->ShowBoard(game_of_life->GetCurrentBoardState(), game_of_life->GetCurrentNumberOfGenerations());
                    return true;
                  });

  actions.emplace(InputOption::kSaveToFile,
                  [](std::shared_ptr<GameOfLife>& game_of_life,
                     std::shared_ptr<UserInterface>& user_interface) {

                    std::string filename = user_interface->GetFileName();

                    while(GameOfLifeFileExporter::CheckIfFileExists(filename)) {
                        user_interface->ShowErrorMessage("The file already exists!!!");
                        filename = user_interface->GetFileName();
                    }

                    GameOfLifeFileExporter::ExportState(
                        game_of_life->GetCurrentBoardState(),
                        game_of_life->GetCurrentNumberOfGenerations(),
                        game_of_life->GetTimeIncrementInMs(),
                        filename);
                    return true;
                  });

  actions.emplace(
      InputOption::kQuit,
      [](std::shared_ptr<GameOfLife>& game_of_life,
         std::shared_ptr<UserInterface>& user_interface) { return false; });

  return actions;
}

bool TheGame::ExecuteAction(
    std::map<InputOption, bool (*)(std::shared_ptr<GameOfLife>& gameOfLife,
                                   std::shared_ptr<UserInterface>&)>
        actions,
    InputOption option, std::shared_ptr<GameOfLife>& game_of_life) {
  auto action = actions.find(option);
  action =
      action != actions.end() ? action : actions.find(InputOption::kDefault);

  bool value = action->second(game_of_life, user_interface_);

  return value;
}

void TheGame::SaveStateToPng(const std::shared_ptr<GameOfLife>& game_of_life) {
  std::ostringstream file_name;
  file_name << "gen" << game_of_life->GetCurrentNumberOfGenerations() << ".png";
  GameOfLifePngExporter::ExportState(game_of_life->GetCurrentBoardState(), file_name.str(), 20);
}

void TheGame::Start(std::shared_ptr<GameOfLife>& game_of_life) {
  ExecuteInitialSimulation(game_of_life);

  auto actions = GetActions();

  while (ExecuteAction(actions, user_interface_->GetInputOption(), game_of_life));
}
