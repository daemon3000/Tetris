#include "Application.h"
#include "DataAsset.h"
#include "TetrisGame.h"
#include "easylogging++.h"

INITIALIZE_EASYLOGGINGPP

using namespace tetris;

int main(int argc, char *argv[])
{
	START_EASYLOGGINGPP(argc, argv);

	ApplicationSettings appSettings;
	appSettings.windowSize.x = 640;
	appSettings.windowSize.y = 640;
	appSettings.fullscreen = false;
	appSettings.title = "Tetris";

	Application *app = Application::getInstance();
	TetrisGame game;
	
	app->run(game, appSettings);

	return 0;
}

