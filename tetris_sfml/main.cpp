#include "Application.h"
#include "DataAsset.h"
#include "TetrisGame.h"
#include "TetrisIcon.h"
#include "easylogging++.h"

INITIALIZE_EASYLOGGINGPP

using namespace tetris;

int main(int argc, char *argv[])
{
	START_EASYLOGGINGPP(argc, argv);

	ApplicationSettings appSettings;
	appSettings.windowSize = { 640, 640 };
	appSettings.fullscreen = false;
	appSettings.title = "Tetris";
	appSettings.iconSize = { TETRIS_ICON.width, TETRIS_ICON.height };
	appSettings.iconPixelData = TETRIS_ICON.pixel_data;

	Application *app = Application::getInstance();
	TetrisGame game;
	
	app->run(game, appSettings);

	return 0;
}

