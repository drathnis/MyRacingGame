#pragma once
#include "Page.h"
#include "button.h"
class EditCarPage :public Page {



private:

	GameData pageInfo;

	Player *p;

	sf::RectangleShape background;
	sf::Font font;
	std::map<std::string, Button*> buttons;

	sf::Text torqueText;
	sf::Text gearText;


public:


	EditCarPage(GameData pageData) :Page(pageData) {
		pageInfo = pageData;

		p = pageInfo.player;

		background.setFillColor(sf::Color(60, 6, 96));
		background.setSize(sf::Vector2f(pageInfo.window->getSize().x, pageInfo.window->getSize().y));


		initFonts();
		initGraphics();
		initButtons();

	}

	void initButtons() {

		buttons["BACK_STATE"] = new Button(
			800, 50,
			150, 50,
			&font, "BACK", 40,
			sf::Color::Red, sf::Color::Green, sf::Color::Blue,
			sf::Color::Blue, sf::Color::Magenta, sf::Color::Cyan
		);
		

		buttons["TORQUE_STATE"] = new Button(
			300, 50,
			400, 50,
			&font, "Show gear / Torque Info", 40,
			sf::Color::Red, sf::Color::Green, sf::Color::Blue,
			sf::Color::Blue, sf::Color::Magenta, sf::Color::Cyan
		);

		
	}

	void initGraphics() {

		initCarStats();
		
	}

	void initCarStats() {

		string temp = "";

		temp = p->raceCar.getGearRatios();

		gearText.setFillColor(sf::Color::White);
		gearText.setFont(font);
		gearText.setString(temp);
		gearText.setCharacterSize(30);
		gearText.setPosition(sf::Vector2f(100, 300));


	}

	void graphT() {



// 		for (size_t i = 0; i < p->raceCar.getMaxRPM(); i++) {
// 			p->raceCar;
// 		}


	}

	void initFonts() {
		if (!font.loadFromFile("Fonts/Roboto-Regular.ttf")) {
			return; //TODO
		}




	}



	void render(sf::RenderTarget* wind) {

		wind->draw(background);
		renderButtons(wind);

		wind->draw(gearText);

	}

	void renderButtons(sf::RenderTarget* target) {
		for (auto& it : this->buttons) {
			it.second->render(*target);

		}
	}




	void update(const double& time) {
		updateButtons();
		updateMousePositions();

	}


	void updateButtons() {
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




	}



};

