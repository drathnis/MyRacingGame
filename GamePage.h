#pragma once


#ifndef _GAMEPAGE_H_
#define _GAMEPAGE_H_

#include "Page.h"

#include "button.h"

#include "RacePage.h"

#include "EditCarPage.h"

class GamePage :public Page {



private:

	std::map<std::string, Button*> buttons;
	sf::Font font;
	sf::RectangleShape background;
	sf::RectangleShape btnBackground;
	sf::RectangleShape infoBox;

	sf::Text infoTxt;
	sf::Text moneyTxt;
	sf::Text moneyVal;

	sf::Texture backgroundTexture;

	GameData pageData;


public:

	GamePage(GameData *pageData);;

	~GamePage();;
	void initFonts();;

	void initButtons();



	void render(sf::RenderTarget *wind);
	void renderButtons(sf::RenderTarget *target);

	void update(const double& time);




	void updatePlayerInfo();

	void updateButtons();

	void initPlayerInfo();

	void renderPlayerInfo();



};

#endif