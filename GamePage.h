/***********************************************************
*GamePage.h
*By: Julian Stanton
*Assignment: Final Project
*Due 5/11/20
*
*Program Description:
*	the page with menu for switching between pages
*
*************************************************************/


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


	bool initBackGournd();


	void initFonts();;

	void initButtons();

	void updatePlayerInfo();

	void updateButtons();

	void initPlayerInfo();

	void renderPlayerInfo();

	void renderButtons(sf::RenderTarget* target);
	
public:

	GamePage(GameData *pageData);
	~GamePage();
	

	
	void render(sf::RenderTarget *wind);

	void update(const double& time);



};

#endif