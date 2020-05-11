/***********************************************************
*MyGame.h
*By: Julian Stanton
*Assignment: Final Project
*Due 5/11/20
*
*Program Description:
*	The class that controls all the pages
*
*************************************************************/


#ifndef _MY_GAME_H_
#define _MY_GAME_H_

#include "Page.h"
#include "GamePage.h"
#include "MainPage.h"


class MyGame {


private:

	sf::Event event;
	sf::RenderWindow *window = nullptr;
	sf::Clock clock;



	GameData gameData;


	stack<Page*> pages;

	void gameLoop();

	void initPlayer();

	void initVariables();

	void initStateData();

	void initPages();

	bool initWindow();

	void update();

	void show();

	void checkEvents();

	

public:
	
	MyGame();
	~MyGame();


};

#endif