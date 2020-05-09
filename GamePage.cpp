#include "GamePage.h"

GamePage::GamePage(GameData pageData) :Page(pageData) {
	pageInfo = pageData;
	background.setFillColor(sf::Color(60, 6, 96));
	background.setSize(sf::Vector2f((float)pageInfo.window->getSize().x, (float)pageInfo.window->getSize().y));

	initFonts();
	initButtons();
	initPlayerInfo();



}

GamePage::~GamePage() {
	auto it = this->buttons.begin();
	for (it = this->buttons.begin(); it != this->buttons.end(); ++it) {
		delete it->second;
	}
}

void GamePage::initFonts() {
	if (!this->font.loadFromFile("Fonts/Roboto-Regular.ttf")) {
		return; //TODO
	}
}

void GamePage::initButtons() {
	buttons["UPGRADE_CAR"] = new Button(
		500, 100,
		150, 80,
		&font, "Upgrade Car", 30,
		sf::Color::Red, sf::Color::Green, sf::Color::Blue,
		sf::Color::Blue, sf::Color::Magenta, sf::Color::Cyan
	);

	buttons["RACE"] = new Button(
		500, 200,
		150, 80,
		&font, "Race", 30,
		sf::Color::Red, sf::Color::Green, sf::Color::Blue,
		sf::Color::Blue, sf::Color::Magenta, sf::Color::Cyan
	);


	buttons["BACK_STATE"] = new Button(
		500, 300,
		150, 80,
		&font, "BACK", 30,
		sf::Color::Red, sf::Color::Green, sf::Color::Blue,
		sf::Color::Blue, sf::Color::Magenta, sf::Color::Cyan
	);
}

void GamePage::render(sf::RenderTarget* wind) {
	
	wind->draw(background);
	renderButtons(wind);
	renderPlayerInfo();
}

void GamePage::renderButtons(sf::RenderTarget* target) {
	
	for (auto& it : buttons) {
		it.second->render(*target);

	}
}

void GamePage::update(const double& time) {
	
	updateMousePositions();

	updateButtons();

	updatePlayerInfo();
}


void GamePage::updatePlayerInfo() {

	stringstream tempStream;
	tempStream << fixed << setprecision(2) << pageInfo.player->getMoney();
	string temp = tempStream.str();

	moneyVal.setString(temp);

}

void GamePage::updateButtons() {
	for (auto& it : buttons) {
		it.second->update(mousePosView);
	}

	if (buttons["BACK_STATE"]->isPressed()) {

		while (buttons["BACK_STATE"]->isPressed()) {
			//pause so we don't get double clicks
			for (auto& it : buttons) {
				it.second->update(mousePosView);
			}
		}
		quitePage();
	}

	if (buttons["UPGRADE_CAR"]->isPressed()) {
		cout << "UPGRADE_CAR" << endl;
		buttons["UPGRADE_CAR"]->update(mousePosView);
		while (buttons["UPGRADE_CAR"]->isPressed()) {
			for (auto& it : buttons) {
				it.second->update(mousePosView);
			}
		}

		pageData.states->push(new EditCarPage(pageData));
	}

	if (buttons["RACE"]->isPressed()) {


		while (buttons["RACE"]->isPressed()) {
			buttons["RACE"]->update(mousePosView);
		}
		pageData.states->push(new RacePage(pageData));

	}
}


#include "GamePage.h"




void GamePage::initPlayerInfo() {




	infoBox.setSize(sf::Vector2f(400, 400));
	infoBox.setOutlineColor(sf::Color::Red);
	infoBox.setPosition(60, 50);
	infoBox.setFillColor(sf::Color(60, 6, 96));
	infoBox.setOutlineThickness(5);
	
	infoTxt.setFillColor(sf::Color::Yellow);
	infoTxt.setFont(font);
	infoTxt.setString("Player Info:");
	infoTxt.setCharacterSize(40);
	infoTxt.setPosition(sf::Vector2f(66, 50));

	moneyTxt.setFillColor(sf::Color::White);
	moneyTxt.setFont(font);
	moneyTxt.setString("Money: $");
	moneyTxt.setCharacterSize(35);
	moneyTxt.setPosition(sf::Vector2f(65, 90));


	stringstream tempStream;
	tempStream << fixed << setprecision(2) << pageInfo.player->getMoney();
	string temp = tempStream.str();

	moneyVal.setFillColor(sf::Color::White);
	moneyVal.setFont(font);
	moneyVal.setString(temp);
	moneyVal.setCharacterSize(35);
	moneyVal.setPosition(sf::Vector2f(210, 90));


}

void GamePage::renderPlayerInfo() {

	pageInfo.window->draw(infoBox);
	pageInfo.window->draw(moneyTxt);
	pageInfo.window->draw(moneyVal);
	pageInfo.window->draw(infoTxt);
}