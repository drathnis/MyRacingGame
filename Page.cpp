#include "Page.h"

GameData::~GameData() {

}

Page::Page(GameData *page) {
	this->gameData = page;



}

void Page::quitePage() {
	quit = true;
}

bool Page::getQuit() {
	return quit;
}

void Page::updateMousePositions(sf::View* view /*= NULL*/) {
	this->mousePosScreen = sf::Mouse::getPosition();
	this->mousePosWindow = sf::Mouse::getPosition(*gameData->window);

	if (view) {
		//gameData.window->setView(*view);
		gameData->window->setView(*view);
	}




	mousePosView = gameData->window->mapPixelToCoords(sf::Mouse::getPosition(*gameData->window));
	this->mousePosGrid =
		sf::Vector2i(
			static_cast<int>(this->mousePosView.x) / static_cast<int>(gameData->gridSize),
			static_cast<int>(this->mousePosView.y) / static_cast<int>(gameData->gridSize)
		);

	gameData->window->setView(gameData->window->getDefaultView());
}
