#pragma once



#include "Page.h"
#include "GamePage.h"
#include "MainPage.h"



class Mygame {


private:

	sf::Event event;
	sf::RenderWindow *window = nullptr;
	sf::Clock clock;


	bool newEvent;
	double frameTime;

	GameData gameData;


	stack<Page*> pages;


public:
	
	Mygame();
	~Mygame();

	void gameLoop();

	void initPlayer();

	void initVariables();

	void initStateData();

	void initPages();

	bool initWindow();

	void getEvents();

	void update();

	void updateTime();

	void show();


	void checkEvents();

};

