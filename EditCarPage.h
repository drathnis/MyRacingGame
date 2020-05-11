/***********************************************************
*EditCarPage.h
*By: Julian Stanton
*Assignment: Final Project
*Due 5/11/20
*
*Program Description:
*	THe page where you can modify your car;
*
*************************************************************/
#ifndef _EDIT_CAR_PAGE_
#define _EDIT_CAR_PAGE_

#include "Page.h"
#include "button.h"


class EditCarPage :public Page {



private:

	Player *p;

	sf::RectangleShape background;
	sf::Font font;
	std::map<std::string, Button*> buttons;

	sf::Text torqueText;
	sf::Text gearText;
	
	sf::Text costText;
	sf::Text infoText;
	
	sf::VertexArray tGraph;
	
	sf::RectangleShape graphBox;

	sf::Texture backgroundTexture;

	string gearRatios = "";
	string infoString;
	string costStr;
	stringstream tempStream;


	bool buyT;
	bool buyE;
	bool buyC;


	int sizeX , sizeY;


	bool initBackGournd();

	void initButtons();

	void initGraphics();

	void initCarStats();

	void loadToqueData();

	double getNewVals(double a, double b, int index);

	void initFonts();

	void renderButtons(sf::RenderTarget* target);


	void updateCostText();

	void updateButtons();;


	bool buyPart(CarPart part);
	
public:


	EditCarPage(GameData *pageData);
	~EditCarPage();


	void render(sf::RenderTarget* wind);

	void update(const double& time);

};

#endif