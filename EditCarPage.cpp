/***********************************************************
*EditCarPage.cpp
*By: Julian Stanton
*Assignment: Final Project
*Due 5/11/20
*
*Program Description:
*	THe page where you can modify your car;
*
*************************************************************/

#include "EditCarPage.h"

EditCarPage::EditCarPage(GameData* pageData) :Page(pageData) {

	p = pageData->player;

	background.setSize(sf::Vector2f(pageData->window->getSize().x, pageData->window->getSize().y));

	if (initBackGournd()) {

		background.setTexture(&backgroundTexture);

	} else {
		background.setFillColor(sf::Color(60, 6, 96));
	}



	sizeX = pageData->window->getSize().x;
	sizeY = pageData->window->getSize().y;

	initFonts();
	initGraphics();
	initButtons();
	buyC = false;
	buyE = false;
	buyT = false;
}

EditCarPage::~EditCarPage() {

}

bool EditCarPage::initBackGournd() {
	if (!backgroundTexture.loadFromFile("Resources/UpgradePage.jpg")) {
		return false;
	}

	return true;
}

void EditCarPage::initButtons() {
	buttons["BACK_STATE"] = new Button(
		800, 50,
		150, 50,
		&font, "BACK", 40,
		sf::Color::Red, sf::Color::Green, sf::Color::Blue,
		sf::Color::Blue, sf::Color::Magenta, sf::Color::Cyan
	);

	buttons["TURBO_STATE"] = new Button(
		100, 50,
		250, 50,
		&font, "Buy Turbos", 40,
		sf::Color::Red, sf::Color::Green, sf::Color::Blue,
		sf::Color::Blue, sf::Color::Magenta, sf::Color::Cyan
	);
	buttons["ENGINE_STATE"] = new Button(
		100, 110,
		250, 50,
		&font, "Buy Engines", 40,
		sf::Color::Red, sf::Color::Green, sf::Color::Blue,
		sf::Color::Blue, sf::Color::Magenta, sf::Color::Cyan
	);

	buttons["CAR_STATE"] = new Button(
		100, 170,
		250, 50,
		&font, "Buy Cars", 40,
		sf::Color::Red, sf::Color::Green, sf::Color::Blue,
		sf::Color::Blue, sf::Color::Magenta, sf::Color::Cyan
	);

	buttons["T_UP_STATE"] = new Button(
		400, 50,
		270, 50,
		&font, "Upgrade Turbo", 40,
		sf::Color::Red, sf::Color::Green, sf::Color::Blue,
		sf::Color::Blue, sf::Color::Magenta, sf::Color::Cyan
	);

	buttons["E_UP_STATE"] = new Button(
		400, 50,
		270, 50,
		&font, "Upgrade Engine", 40,
		sf::Color::Red, sf::Color::Green, sf::Color::Blue,
		sf::Color::Blue, sf::Color::Magenta, sf::Color::Cyan
	);

	buttons["C_UP_STATE"] = new Button(
		400, 50,
		270, 50,
		&font, "Upgrade Car", 40,
		sf::Color::Red, sf::Color::Green, sf::Color::Blue,
		sf::Color::Blue, sf::Color::Magenta, sf::Color::Cyan
	);
}

void EditCarPage::initGraphics() {
	initCarStats();

	costText.setFillColor(sf::Color::Red);
	costText.setFont(font);
	costText.setString(costStr);
	costText.setCharacterSize(50);
	costText.setPosition(sf::Vector2f(400, 100));

	infoText.setFillColor(sf::Color::Red);
	infoText.setFont(font);
	infoText.setString(infoString);
	infoText.setCharacterSize(50);
	infoText.setPosition(sf::Vector2f(400, 200));
}

void EditCarPage::initCarStats() {

	gearRatios = p->playerCar()->getGearRatios();
	gearText.setFillColor(sf::Color::White);
	gearText.setFont(font);
	gearText.setString(gearRatios);
	gearText.setCharacterSize(30);
	gearText.setPosition(sf::Vector2f(100, 300));

	torqueText.setFillColor(sf::Color::White);
	torqueText.setFont(font);
	torqueText.setCharacterSize(9.5);
	torqueText.setPosition(sf::Vector2f(8, 10));

	loadToqueData();
}

void EditCarPage::loadToqueData() {

	int rpms = p->playerCar()->getDrivetrain()->getEngine()->maxRpm;
	cout << "MAX: " << rpms << endl;
	string temp = "";

	stringstream tempStream;

	tempStream << ("Torque:\n");

	cout << "Loading T Data" << endl;

	double val;
	for (size_t i = 0; i < rpms / 100 - 9; i++) {
		val = p->playerCar()->getDrivetrain()->getEngine()->tCurve[i];
		//cout << "val: " << val << endl;
		//temp += to_string(val) + '\n';

		tempStream << fixed << setprecision(2) << val << "\n";

	}

	torqueText.setString(tempStream.str());
}

double EditCarPage::getNewVals(double a, double b, int index) {
	double newVal;
	double M;
	M = (b - a) / 100;
	newVal = M * (index)+a;
	//cout << newVal << endl;
	return newVal;
}

void EditCarPage::initFonts() {
	if (!font.loadFromFile("Fonts/Roboto-Regular.ttf")) {
		return; //TODO
	}
}

void EditCarPage::render(sf::RenderTarget* wind) {
	wind->draw(background);
	renderButtons(wind);
	wind->draw(gearText);
	wind->draw(torqueText);

	wind->draw(infoText);

	if (buyT || buyC || buyE) {
		wind->draw(costText);
	}
}

void EditCarPage::renderButtons(sf::RenderTarget* target) {
	for (auto& it : this->buttons) {

		//cout << it.first << endl;
		if (it.first == "T_UP_STATE") {
			if (buyT) {
				it.second->render(*target);
			} else {
				continue;
			}
		}
		if (it.first == "E_UP_STATE") {
			if (buyE) {
				it.second->render(*target);
			} else {
				continue;
			}
		}

		if (it.first == "C_UP_STATE") {
			if (buyC) {
				it.second->render(*target);
			} else {
				continue;
			}
		}


		it.second->render(*target);
	}
}

void EditCarPage::update(const double& time) {
	updateMousePositions();

	updateButtons();
	updateCostText();

	//infoString = "INFO!";
	infoText.setString(infoString);

	gearText.setString(gearRatios);
	//gearRatios = p->raceCar->getGearRatios();
}

void EditCarPage::updateCostText() {
	costText.setString("$" + costStr);
}

void EditCarPage::updateButtons() {
	for (auto& it : this->buttons) {
		it.second->update(mousePosView);
	}

	if (buttons["BACK_STATE"]->isPressed()) {

		while (buttons["BACK_STATE"]->isPressed()) {
			//pause so we don't get double clicks
			for (auto& it : this->buttons) {
				it.second->update(mousePosView);
			}

		}

		this->quitePage();
	}

	if (buttons["TURBO_STATE"]->isPressed()) {
		infoString = " ";
		while (buttons["TURBO_STATE"]->isPressed()) {
			//pause so we don't get double clicks
			for (auto& it : this->buttons) {
				it.second->update(mousePosView);
			}

		}
		tempStream.str("");
		tempStream << fixed << setprecision(2) << p->getTurbUprageCost();
		costStr = tempStream.str();
		buyC = false;
		buyE = false;
		buyT = true;
	}
	if (buttons["ENGINE_STATE"]->isPressed()) {
		infoString = " ";
		while (buttons["ENGINE_STATE"]->isPressed()) {
			//pause so we don't get double clicks
			for (auto& it : this->buttons) {
				it.second->update(mousePosView);
			}

		}

		tempStream.str("");
		tempStream << fixed << setprecision(2) << p->getEngUpgradeCost();
		costStr = tempStream.str();

		buyC = false;
		buyE = true;
		buyT = false;
	}
	if (buttons["CAR_STATE"]->isPressed()) {
		infoString = " ";
		while (buttons["CAR_STATE"]->isPressed()) {
			//pause so we don't get double clicks
			for (auto& it : this->buttons) {
				it.second->update(mousePosView);
			}

		}

		tempStream.str("");
		tempStream << fixed << setprecision(2) << p->getCarUprageCost();
		costStr = tempStream.str();

		buyC = true;
		buyE = false;
		buyT = false;

	}

	if (buttons["T_UP_STATE"]->isPressed() && buyT) {
		infoString = " ";
		while (buttons["T_UP_STATE"]->isPressed()) {
			//pause so we don't get double clicks
			for (auto& it : this->buttons) {
				it.second->update(mousePosView);
			}

		}
		if (buyPart(CarPart::turbo)) {

			p->changeCost(CarPart::turbo);
			tempStream.str("");
			tempStream << fixed << setprecision(2) << p->getTurbUprageCost();
			costStr = tempStream.str();
			cout << "Updating Turbo!" << endl;
		}
	}


	if (buttons["E_UP_STATE"]->isPressed() && buyE) {
		infoString = " ";
		while (buttons["E_UP_STATE"]->isPressed()) {
			//pause so we don't get double clicks
			for (auto& it : this->buttons) {
				it.second->update(mousePosView);
			}

		}
		if (buyPart(CarPart::engine)) {

			p->changeCost(CarPart::engine);
			tempStream.str("");
			tempStream << fixed << setprecision(2) << p->getEngUpgradeCost();
			costStr = tempStream.str();
			cout << "Updating Engine!" << endl;
		}
	}
	if (buttons["C_UP_STATE"]->isPressed() && buyC) {
		infoString = " ";
		while (buttons["C_UP_STATE"]->isPressed()) {
			//pause so we don't get double clicks
			for (auto& it : this->buttons) {
				it.second->update(mousePosView);
			}

		}
		if (buyPart(CarPart::body)) {

			p->changeCost(CarPart::body);
			tempStream.str("");
			tempStream << fixed << setprecision(2) << p->getCarUprageCost();
			costStr = tempStream.str();
			cout << "Updating Car!" << endl;
		}
	}
}

bool EditCarPage::buyPart(CarPart part) {
	double playerMoney = p->getMoney();
	infoString = " ";
	switch (part) {
	case CarPart::body:
		if (p->getCarUprageCost() <= playerMoney) {

			if (p->playerCar()->upgradeCar()) {
				infoString = "Success";
				p->subtractMoney(p->getCarUprageCost());
				loadToqueData();
				gearRatios = p->playerCar()->getGearRatios();
				return true;
			} else {
				infoString = "You Have the best Car";
				return false;
			}

		} else {
			infoString = "Not Enough Money";
		}

		break;
	case CarPart::engine:

		if (p->getEngUpgradeCost() <= playerMoney) {
			infoString = "Success";
			if (p->playerCar()->upgradeEng()) {
				p->subtractMoney(p->getEngUpgradeCost());
				loadToqueData();
				gearRatios = p->playerCar()->getGearRatios();
				return true;
			} else {
				infoString = "You Have the best Engine";
				return false;
			}

		} else {
			infoString = "Not Enough Money";
		}


		break;
	case CarPart::turbo:

		if (p->getTurbUprageCost() <= playerMoney) {
			infoString = "Success";
			p->playerCar()->upgradeTurbo();
			p->subtractMoney(p->getTurbUprageCost());
			gearRatios = p->playerCar()->getGearRatios();
			loadToqueData();
			return true;
		} else {
			infoString = "Not Enough Money";
		}


		break;
	default:
		break;
	}

	return false;
}
