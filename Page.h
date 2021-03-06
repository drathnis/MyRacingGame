/***********************************************************
*Page.h
*By: Julian Stanton
*Assignment: Final Project
*Due 5/11/20
*
*Program Description:
*	The Base class that the other pages are built on
*	inspired / based on code from Headturna on github
*	I was looking for a good way to implement a gui and this
*	seemed like a great way SFML is pretty cool
*************************************************************/


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
	~GameData();

	float gridSize = 1;
	sf::RenderWindow* window;

	std::stack<Page*>* states;

	Player *player;

};


class Page {



protected:
	sf::Vector2i mousePosScreen;
	sf::Vector2i mousePosWindow;
	sf::Vector2f mousePosView;
	sf::Vector2i mousePosGrid;

	GameData *gameData;

private:


	vector<sf::Texture> textures;


public:


	bool quit = false;
	Page(GameData *page);

	virtual void quitePage();
	bool getQuit();
	virtual void update(const double &time) =0;
	virtual void render(sf::RenderTarget* wind = nullptr ) = 0;
	virtual void updateMousePositions(sf::View* view = NULL);

};

#endif