#include "game.hpp"

TheGame::TheGame(std::shared_ptr<UserInterface> user_interface)
    : user_interface(user_interface) {}

void TheGame::executeInitialSimulation(std::shared_ptr<GameOfLife> gameOfLife) {
  user_interface->ShowBoard(gameOfLife->getCurrentBoardState());
  for (int i = 0; i < gameOfLife->getInitialNumberOfGenerations(); i++) {
    auto begin = std::chrono::system_clock::now();
    auto target_time =
        begin + std::chrono::milliseconds(gameOfLife->getTimeIncrementInMs());

    gameOfLife->goForward();
    user_interface->ShowBoard(gameOfLife->getCurrentBoardState());
    saveStateToPng(gameOfLife);

    std::this_thread::sleep_until(target_time);
  }
}

std::map<InputOption, bool (*)(std::shared_ptr<GameOfLife>& gameOfLife,
                               std::shared_ptr<UserInterface>&)>
TheGame::getActions() {
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
                    gameOfLife->goBack();
                    return true;
                  });

  actions.emplace(InputOption::kGoForward,
                  [](std::shared_ptr<GameOfLife>& gameOfLife,
                     std::shared_ptr<UserInterface>& user_interface) {
                    gameOfLife->goForward();
                    return true;
                  });

  actions.emplace(InputOption::kSaveToFile,
                  [](std::shared_ptr<GameOfLife>& gameOfLife,
                     std::shared_ptr<UserInterface>& user_interface) {
                    std::string filename = user_interface->GetFileName();
                    GameOfLifeFileExporter exporter{filename};
                    exporter.exportState(gameOfLife);
                    return true;
                  });

  actions.emplace(
      InputOption::kQuit,
      [](std::shared_ptr<GameOfLife>& gameOfLife,
         std::shared_ptr<UserInterface>& user_interface) { return false; });

  return actions;
}

bool TheGame::executeAction(
    std::map<InputOption, bool (*)(std::shared_ptr<GameOfLife>& gameOfLife,
                                   std::shared_ptr<UserInterface>&)>
        actions,
    InputOption option, std::shared_ptr<GameOfLife>& gameOfLife) {
  auto action = actions.find(option);
  action =
      action != actions.end() ? action : actions.find(InputOption::kDefault);

  bool value = action->second(gameOfLife, user_interface);
  user_interface->ShowBoard(gameOfLife->getCurrentBoardState());

  return value;
}

void TheGame::saveStateToPng(const std::shared_ptr<GameOfLife>& gameOfLife) {
  std::ostringstream filename;
  filename << "gen" << gameOfLife->getCurrentNumberOfGenerations() << ".png";
  GameOfLifePngExporter pngExporter{filename.str(), 20};
  pngExporter.exportState(gameOfLife);
}

void TheGame::executeSimulation(std::shared_ptr<GameOfLife>& gameOfLife) {
  executeInitialSimulation(gameOfLife);

  auto actions = getActions();

  InputOption option = InputOption::kQuit;
  bool continueExecution = false;
  do {
    option = user_interface->GetInputOption();
    continueExecution = executeAction(actions, option, gameOfLife);
    saveStateToPng(gameOfLife);
  } while (continueExecution);
}
