#include "game.hpp"

TheGame::TheGame(std::shared_ptr<UserInterface> user_interface)
    : user_interface(user_interface) {}

void TheGame::ExecuteInitialSimulation(std::shared_ptr<GameOfLife> gameOfLife) {
  user_interface->ShowBoard(gameOfLife->GetCurrentBoardState());
  for (int i = 0; i < gameOfLife->GetInitialNumberOfGenerations(); i++) {
    auto begin = std::chrono::system_clock::now();
    auto target_time =
        begin + std::chrono::milliseconds(gameOfLife->GetTimeIncrementInMs());

    gameOfLife->GoForward();
    user_interface->ShowBoard(gameOfLife->GetCurrentBoardState());
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
                    gameOfLife->GoBack();
                    return true;
                  });

  actions.emplace(InputOption::kGoForward,
                  [](std::shared_ptr<GameOfLife>& gameOfLife,
                     std::shared_ptr<UserInterface>& user_interface) {
                    gameOfLife->GoForward();
                    return true;
                  });

  actions.emplace(InputOption::kSaveToFile,
                  [](std::shared_ptr<GameOfLife>& gameOfLife,
                     std::shared_ptr<UserInterface>& user_interface) {
                    std::string filename = user_interface->GetFileName();
                    GameOfLifeFileExporter exporter{filename};
                    exporter.ExportState(gameOfLife);
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
  user_interface->ShowBoard(gameOfLife->GetCurrentBoardState());

  return value;
}

void TheGame::SaveStateToPng(const std::shared_ptr<GameOfLife>& gameOfLife) {
  std::ostringstream filename;
  filename << "gen" << gameOfLife->GetCurrentNumberOfGenerations() << ".png";
  GameOfLifePngExporter pngExporter{filename.str(), 20};
  pngExporter.ExportState(gameOfLife);
}

void TheGame::ExecuteSimulation(std::shared_ptr<GameOfLife>& gameOfLife) {
  ExecuteInitialSimulation(gameOfLife);

  auto actions = GetActions();

  InputOption option = InputOption::kQuit;
  bool continueExecution = false;
  do {
    option = user_interface->GetInputOption();
    continueExecution = ExecuteAction(actions, option, gameOfLife);
    SaveStateToPng(gameOfLife);
  } while (continueExecution);
}
