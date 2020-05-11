
/***********************************************************
*MainPage.cpp
*By: Julian Stanton
*Assignment: Final Project
*Due 5/11/20
*
*Program Description:
*	The 'Title' page
*
*************************************************************/

#include "MainPage.h"


MainPage::MainPage(GameData *pageData) :Page(pageData) {

	cout << "MainPage" << endl;
	pageInfo = *pageData;

	background.setSize(sf::Vector2f((float)pageInfo.window->getSize().x, (float)pageInfo.window->getSize().y));


	initFonts();
	initButtons();

	if (initBackGournd()) {
		
		background.setRotation(270);
		background.setPosition(100, (float)pageInfo.window->getSize().y);

		background.setTexture(&backgroundTexture);
	} else {
		background.setFillColor(sf::Color(14, 25, 179));

	}

}



MainPage::~MainPage() {
	auto it = buttons.begin();
	for (it = buttons.begin(); it != buttons.end(); ++it) {
		delete it->second;
	}


}

bool MainPage::initBackGournd() {

	if (!backgroundTexture.loadFromFile("Resources/FontPage.jpg")) {
		return false;
	}

	return true;
}


void MainPage::initButtons() {
	buttons["GAME_STATE"] = new Button(
		350, 400,
		325, 80,
		&font, "Play Game", 60,
		sf::Color::Red, sf::Color::Green, sf::Color::Black,
		sf::Color::Transparent, sf::Color::Transparent, sf::Color::Cyan
	);

	buttons["EXIT_STATE"] = new Button(
		450, 500,
		150, 80,
		&font, "EXIT", 60,
		sf::Color(0, 0, 0), sf::Color(0, 0, 0), sf::Color(0, 0, 0),
		sf::Color::Transparent, sf::Color(100, 0, 0), sf::Color(255, 0, 0)
	);
}


void MainPage::update(const double& time) {
	updateMousePositions();
	updateButtons();

}

void MainPage::updateButtons() {

	for (auto& it : this->buttons) {
		it.second->update(mousePosView);

	}

	if (buttons["EXIT_STATE"]->isPressed()) {
		this->quit = true;
	}

	if (buttons["GAME_STATE"]->isPressed()) {
		cout << "GAME_STATE" << endl;

		while (buttons["GAME_STATE"]->isPressed()) {
			//pause so we don't get double clicks
			for (auto& it : buttons) {
				it.second->update(mousePosView);
			}
		}

		this->pageInfo.states->push(new GamePage(&pageInfo));

	}


}


void MainPage::renderButtons(sf::RenderTarget* wind) {


	for (auto& it : this->buttons) {
		it.second->render(*wind);
	}
}


void MainPage::initFonts() {
	if (!this->font.loadFromFile("Fonts/Roboto-Regular.ttf")) {
		return; //TODO
	}
}

void MainPage::render(sf::RenderTarget* wind) {
	
	pageInfo.window->draw(background);
	renderButtons(wind);
}
