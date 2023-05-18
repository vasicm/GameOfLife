#include "game.hpp"

TheGame::TheGame(std::shared_ptr<UserInterface> user_interface)
    : user_interface(user_interface) {}

void TheGame::ExecuteInitialSimulation(std::shared_ptr<GameOfLife> gameOfLife) {
  user_interface->ShowBoard(gameOfLife->GetCurrentBoardState(), gameOfLife->GetCurrentNumberOfGenerations());
  SaveStateToPng(gameOfLife);
  for (int i = 0; i < gameOfLife->GetInitialNumberOfGenerations(); i++) {
    auto begin = std::chrono::system_clock::now();
    auto target_time =
        begin + std::chrono::milliseconds(gameOfLife->GetTimeIncrementInMs());

    gameOfLife->GoForward();
    user_interface->ShowBoard(gameOfLife->GetCurrentBoardState(), gameOfLife->GetCurrentNumberOfGenerations());
    SaveStateToPng(gameOfLife);

    std::this_thread::sleep_until(target_time);
  }
}

std::map<InputOption, bool (*)(std::shared_ptr<GameOfLife>& gameOfLife,
                               std::shared_ptr<UserInterface>&)>
TheGame::GetActions() {
  std::map<InputOption, bool (*)(std::shared_ptr<GameOfLife> & gameOfLife,
                                 std::shared_ptr<UserInterface>&)>
      actions;

  actions.emplace(
      InputOption::kDefault,
      [](std::shared_ptr<GameOfLife>& gameOfLife,
         std::shared_ptr<UserInterface>& user_interface) {
        user_interface->ShowErrorMessage("Invalid action, try again!");
        return true;
      });

  actions.emplace(InputOption::kGoBack,
                  [](std::shared_ptr<GameOfLife>& gameOfLife,
                     std::shared_ptr<UserInterface>& user_interface) {

                    try
                    {
                      gameOfLife->GoBack();
                      SaveStateToPng(gameOfLife);
                      user_interface->ShowBoard(gameOfLife->GetCurrentBoardState(), gameOfLife->GetCurrentNumberOfGenerations());
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
                  [](std::shared_ptr<GameOfLife>& gameOfLife,
                     std::shared_ptr<UserInterface>& user_interface) {
                    gameOfLife->GoForward();
                    SaveStateToPng(gameOfLife);
                    user_interface->ShowBoard(gameOfLife->GetCurrentBoardState(), gameOfLife->GetCurrentNumberOfGenerations());
                    return true;
                  });

  actions.emplace(InputOption::kSaveToFile,
                  [](std::shared_ptr<GameOfLife>& gameOfLife,
                     std::shared_ptr<UserInterface>& user_interface) {

                    std::string filename = user_interface->GetFileName();

                    while(GameOfLifeFileExporter::CheckIfFileExists(filename)) {
                        user_interface->ShowErrorMessage("The file already exists!!!");
                        filename = user_interface->GetFileName();
                    }

                    GameOfLifeFileExporter::ExportState(
                        gameOfLife->GetCurrentBoardState(),
                        gameOfLife->GetCurrentNumberOfGenerations(),
                        gameOfLife->GetTimeIncrementInMs(),
                        filename);
                    return true;
                  });

  actions.emplace(
      InputOption::kQuit,
      [](std::shared_ptr<GameOfLife>& gameOfLife,
         std::shared_ptr<UserInterface>& user_interface) { return false; });

  return actions;
}

bool TheGame::ExecuteAction(
    std::map<InputOption, bool (*)(std::shared_ptr<GameOfLife>& gameOfLife,
                                   std::shared_ptr<UserInterface>&)>
        actions,
    InputOption option, std::shared_ptr<GameOfLife>& gameOfLife) {
  auto action = actions.find(option);
  action =
      action != actions.end() ? action : actions.find(InputOption::kDefault);

  bool value = action->second(gameOfLife, user_interface);

  return value;
}

void TheGame::SaveStateToPng(const std::shared_ptr<GameOfLife>& gameOfLife) {
  std::ostringstream filename;
  filename << "gen" << gameOfLife->GetCurrentNumberOfGenerations() << ".png";
  GameOfLifePngExporter::ExportState(gameOfLife->GetCurrentBoardState(), filename.str(), 20);
}

void TheGame::Start(std::shared_ptr<GameOfLife>& gameOfLife) {
  ExecuteInitialSimulation(gameOfLife);

  auto actions = GetActions();

  while (ExecuteAction(actions, user_interface->GetInputOption(), gameOfLife));
}
