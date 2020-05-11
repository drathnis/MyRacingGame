
/***********************************************************
*MainPage.h
*By: Julian Stanton
*Assignment: Final Project
*Due 5/11/20
*
*Program Description:
*	The 'Title' page
*
*************************************************************/



#ifndef _MAIN_PAGE_H_
#define _MAIN_PAGE_H_

#include "Page.h"

#include "button.h"
#include "GamePage.h"


class MainPage :public Page {


private:

	std::map<std::string, Button*> buttons;
	sf::Font font;
	sf::RectangleShape background;
	sf::RectangleShape btnBackground;
	sf::Texture backgroundTexture;

	GameData pageInfo;

	sf::Image backgroundImg;



	bool initBackGournd();

	void initFonts();;

	void initButtons();

	void updateButtons();

	void renderButtons(sf::RenderTarget* wind);
	
public:

	MainPage(GameData* pageData);;

	~MainPage();


	void update(const double& time);;


	void render(sf::RenderTarget* wind);;


};
#endif