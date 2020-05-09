#pragma once
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


	public:

		MainPage(GameData pageData);;

		~MainPage();;



		void renderButtons(sf::RenderTarget& target);;
		
		void initFonts();;


		void initButtons();


		void resetGui();

		void checkForEnd();
		

		void update(const double& time);;

		void updateButtons();

		void renderButtons(sf::RenderTarget* wind);

		void render(sf::RenderTarget* wind);;


};
