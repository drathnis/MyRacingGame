#pragma once

#ifndef _PAGE_H_
#define _PAGE_H_

#include <vector>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/System.hpp>
#include <iostream>
#include <sstream>
#include <fstream>
#include <iomanip>
#include <map>
#include <stack>


#include "myTimer.h"
#include "Player.h"


using namespace std;

class Page;


class GameData {



public:
	~GameData() {


	};

	float gridSize = 1;
	sf::RenderWindow* window;

	std::map<std::string, int>* supportedKeys;
	std::stack<Page*>* states;

	Player *player;

};


class Page {



protected:
	sf::Vector2i mousePosScreen;
	sf::Vector2i mousePosWindow;
	sf::Vector2f mousePosView;
	sf::Vector2i mousePosGrid;

	GameData pageData;

private:


	vector<sf::Texture> textures;


public:

	bool quit = false;

	Page(GameData page) {

		this->pageData = page;
	};


	virtual void quitePage() {
		quit = true;

	};

	bool getQuit() {
		return quit;
	}


	virtual void update(const double &time) =0;
	virtual void render(sf::RenderTarget* wind = nullptr ) = 0;


	virtual void updateMousePositions(sf::View* view = NULL) {
		this->mousePosScreen = sf::Mouse::getPosition();
		this->mousePosWindow = sf::Mouse::getPosition(*this->pageData.window);

		if (view)
			this->pageData.window->setView(*view);

		

		this->mousePosView = this->pageData.window->mapPixelToCoords(sf::Mouse::getPosition(*this->pageData.window));
		this->mousePosGrid =
			sf::Vector2i(
				static_cast<int>(this->mousePosView.x) / static_cast<int>(this->pageData.gridSize),
				static_cast<int>(this->mousePosView.y) / static_cast<int>(this->pageData.gridSize)
			);

		this->pageData.window->setView(this->pageData.window->getDefaultView());
	}

};

#endif