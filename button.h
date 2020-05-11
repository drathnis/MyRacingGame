/***********************************************************
*button.h
*By: Julian Stanton
*Assignment: Final Project
*Due 5/11/20
*
*Program Description:
*	Button class to make buttons
*
*************************************************************/


#ifndef _BUTTON_H_
#define _BUTTON_H_



#include "Page.h"

using namespace std;

enum button_states { BTN_IDLE = 0, BTN_HOVER, BTN_ACTIVE };

class Button {
	
private:

	GameData pageInfo;
	bool test = false;
	sf::Event InputEvent;

	short unsigned buttonState = BTN_IDLE;
	short unsigned id;

	sf::RectangleShape shape;
	sf::Font* font;
	sf::Text text;

	sf::Color textIdleColor;
	sf::Color textHoverColor;
	sf::Color textActiveColor;

	sf::Color idleColor;
	sf::Color hoverColor;
	sf::Color activeColor;

	sf::Color outlineIdleColor;
	sf::Color outlineHoverColor;
	sf::Color outlineActiveColor;

public:
	Button(float x, float y, float width, float height,
		sf::Font* font, std::string text, unsigned character_size,
		sf::Color text_idle_color, sf::Color text_hover_color, sf::Color text_active_color,
		sf::Color idle_color, sf::Color hover_color, sf::Color active_color,
		sf::Color outline_idle_color = sf::Color::Transparent, sf::Color outline_hover_color = sf::Color::Transparent, sf::Color outline_active_color = sf::Color::Transparent,
		short unsigned id = 0);

	bool isPressed() const;
	
	void update(const sf::Vector2f& mousePosWindow);
	void render(sf::RenderTarget& target);
};

#endif