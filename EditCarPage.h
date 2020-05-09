#pragma once
#include "Page.h"
#include "button.h"


class EditCarPage :public Page {



private:

	GameData pageData;

	Player *p;

	sf::RectangleShape background;
	sf::Font font;
	std::map<std::string, Button*> buttons;

	sf::Text torqueText;
	sf::Text gearText;

	sf::RectangleShape *linesArry;
	int lineCount;
	sf::VertexArray tGraph;

public:


	EditCarPage(GameData *pageData) :Page(pageData) {
		this->pageData = *pageData;

		p = this->pageData.player;

		background.setFillColor(sf::Color(60, 6, 96));
		background.setSize(sf::Vector2f(this->pageData.window->getSize().x, this->pageData.window->getSize().y));
		cout << "setting new car" << endl;
		//pageInfo.player->raceCar = Car('c');
		cout << "Done setting new car" << endl;

		initFonts();
		initGraphics();
		initButtons();
		graphT();
	}
	~EditCarPage() {
		delete[] linesArry;

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

		int rpms = (p->raceCar.getDrivetrain()->getEngine()->maxRpm/100)-9;
		int val;
		cout<<"rpms " << rpms<<endl;

		lineCount = rpms;
		//lines = new sf::RectangleShape[lineCount];

 		tGraph = sf::VertexArray(sf::LineStrip, lineCount);
		
 
 		for (size_t i = 0; i < lineCount; i++) {
 			val = p->raceCar.getDrivetrain()->getEngine()->tCurve[i];
 			cout<< val <<endl;
 
 			tGraph[i].position = sf::Vector2f((i*5)+100, (val * -5)+pageData.window->getSize().y);
			tGraph[i].color = sf::Color::Red;



 		}





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

		sf::VertexArray lines(sf::LineStrip, 10);
		lines[0].position = sf::Vector2f(100, 10);
		lines[1].position = sf::Vector2f(120, 10);
		lines[2].position = sf::Vector2f(130, 15);
		lines[3].position = sf::Vector2f(140, 12);

		wind->draw(lines);

		

		wind->draw(tGraph);
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

