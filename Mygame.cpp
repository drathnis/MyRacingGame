/***********************************************************
*MyGame.cpp
*By: Julian Stanton
*Assignment: Final Project
*Due 5/11/20
*
*Program Description:
*	The class that controls all the pages
*
*************************************************************/

#include "MyGame.h"


MyGame::MyGame() {


	initPlayer();
	initVariables();
	initWindow();
	initStateData();
	initPages();

	gameLoop();



}


MyGame::~MyGame() {
	delete window;

	while (!pages.empty()) {

		delete pages.top();

		pages.pop();
	}
}

void MyGame::gameLoop() {
	cout << "Run"<<endl;
	while (window->isOpen()) {

		show();
		update();

	}
}

void MyGame::initPlayer() {

	gameData.player = new Player;
	cout << "Created Player"<< endl;	
	gameData.player->setPlayerCar(new Car('C'));

}

void MyGame::initVariables() {
	window = NULL;

	gameData.gridSize = 64.f;
}

void MyGame::initStateData() {

	gameData.window = window;

	gameData.states = &pages;
}

void MyGame::initPages() {
	pages.push(new MainPage(&gameData));
}

bool MyGame::initWindow() {
	window = new sf::RenderWindow(sf::VideoMode(1000, 800), "My Race Game");

	if (!window) {
		cout << "NO WINDOW!!" << endl;
		return false;
	}

	return true;
}

void MyGame::update() {
	
	checkEvents();

	if (!pages.empty()) {
		pages.top()->update(0);

		if (pages.top()->getQuit()) {
			pages.top()->quitePage();
			delete pages.top();
			pages.pop();
		}

	}
	else {

		window->close();
	}
}

void MyGame::show() {
	window->clear();

	if (!pages.empty())
		pages.top()->render(window);

	window->display();
}

void MyGame::checkEvents() {

	while (window->pollEvent(event)) {
		if (event.type == sf::Event::Closed)
			window->close();
	}
}

