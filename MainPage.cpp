#include "MainPage.h"


MainPage::MainPage(GameData pageData) :Page(pageData) {

	cout << "MainPage" << endl;
	pageInfo = pageData;

	background.setFillColor(sf::Color(14, 25, 179));
	background.setSize(sf::Vector2f((float)pageInfo.window->getSize().x, (float)pageInfo.window->getSize().y));

	initFonts();
	initButtons();



}

MainPage::~MainPage() {
	auto it = buttons.begin();
	for (it = buttons.begin(); it != buttons.end(); ++it) {
		delete it->second;
	}
}

void MainPage::initButtons() {
	buttons["GAME_STATE"] = new Button(
		350, 100,
		325, 80,
		&font, "Play Game", 60,
		sf::Color::Red, sf::Color::Green, sf::Color::Blue,
		sf::Color::Blue, sf::Color::Magenta, sf::Color::Cyan
	);

	buttons["EXIT_STATE"] = new Button(
		450, 200,
		150, 80,
		&font, "EXIT", 60,
		sf::Color(0, 0, 0), sf::Color(0, 0, 0), sf::Color(0, 0, 0),
		sf::Color(230, 0, 0), sf::Color(100, 0, 0), sf::Color(255, 0, 0)
	);
}

void MainPage::resetGui() {
	auto it = buttons.begin();
	for (it = buttons.begin(); it != buttons.end(); ++it) {
		delete it->second;
	}
	buttons.clear();

	initButtons();
}

void MainPage::checkForEnd() {

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
		quit = true;
	}

	if (buttons["GAME_STATE"]->isPressed()) {
		cout << "GAME_STATE" << endl;

		while (buttons["GAME_STATE"]->isPressed()) {
			//pause so we don't get double clicks
			for (auto& it : buttons) {
				it.second->update(mousePosView);
			}
		}

		this->pageInfo.states->push(new GamePage(pageInfo));

	}




}


void MainPage::renderButtons(sf::RenderTarget* wind) {



	for (auto& it : this->buttons) {
		it.second->render(*wind);

	}
}

void MainPage::renderButtons(sf::RenderTarget& target) {

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
