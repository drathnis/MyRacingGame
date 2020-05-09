#include "Mygame.h"


Mygame::Mygame() {
	

	initPlayer();
	initVariables();
	initWindow();
	initStateData();
	initPages();

	gameLoop();



}

Mygame::~Mygame() {
	delete window;

	while (!pages.empty()) {
		delete pages.top();
		pages.pop();
	}
}

void Mygame::gameLoop() {
	cout << "Run";
	while (window->isOpen()) {

		updateTime();

		show();
		update();

	}
	cout << "EndLoop";
	return;
}

void Mygame::initPlayer() {

	gameData.player = new Player;
	cout << "Created Player"<< endl;	
	gameData.player->addMoney(10000);



	//TODO
}

void Mygame::initVariables() {
	window = NULL;

	frameTime = 0.f;

	gameData.gridSize = 64.f;
}

void Mygame::initStateData() {

	gameData.window = window;

	gameData.states = &pages;
}

void Mygame::initPages() {
	pages.push(new MainPage(&gameData));
	//pages.push(new RacePage(gameData));
}

bool Mygame::initWindow() {
	window = new sf::RenderWindow(sf::VideoMode(1000, 800), "My Race Game");

	if (!window) {
		cout << "NO WINDOW!!" << endl;
		return false;
	}

	return true;
}

void Mygame::getEvents() {

}

void Mygame::update() {
	
	checkEvents();

	if (!pages.empty()) {
		pages.top()->update(frameTime);

		if (pages.top()->getQuit()) {
			pages.top()->quitePage();
			delete pages.top();
			pages.pop();
		}

	}
	//Application end
	else {

		window->close();
	}
}

void Mygame::updateTime() {

	frameTime = clock.restart().asSeconds();
	//cout << frameTime << endl;
}

void Mygame::show() {
	window->clear();

	if (!pages.empty())
		pages.top()->render(window);

	window->display();
}

void Mygame::checkEvents() {

	//cout << "Checking" << endl;
	while (window->pollEvent(event)) {
		if (event.type == sf::Event::Closed)
			window->close();
	}
}
