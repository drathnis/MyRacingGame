
/***********************************************************
*button.cpp
*By: Julian Stanton
*Assignment: Final Project
*Due 5/11/20
*
*Program Description:
*	Button class to make buttons
*
*************************************************************/
#include "button.h"


//Constructor for button 

Button::Button(float x, float y, float width, float height,
	sf::Font* font, std::string text, unsigned character_size,
	sf::Color text_idle_color, sf::Color text_hover_color, sf::Color text_active_color,
	sf::Color idle_color, sf::Color hover_color, sf::Color active_color,
	sf::Color outline_idle_color, sf::Color outline_hover_color, sf::Color outline_active_color,
	short unsigned id) {


	this->buttonState = BTN_IDLE;
	this->id = id;

	this->shape.setPosition(sf::Vector2f(x, y));
	this->shape.setSize(sf::Vector2f(width, height));
	this->shape.setFillColor(idle_color);
	this->shape.setOutlineThickness(1.f);
	this->shape.setOutlineColor(outline_idle_color);

	this->font = font;
	this->text.setFont(*this->font);
	this->text.setString(text);
	this->text.setFillColor(text_idle_color);
	this->text.setCharacterSize(character_size);
	this->text.setPosition(
		this->shape.getPosition().x + (this->shape.getGlobalBounds().width / 2.f) - this->text.getGlobalBounds().width / 2.f,
		this->shape.getPosition().y
	);

	this->textIdleColor = text_idle_color;
	this->textHoverColor = text_hover_color;
	this->textActiveColor = text_active_color;

	this->idleColor = idle_color;
	this->hoverColor = hover_color;
	this->activeColor = active_color;

	this->outlineIdleColor = outline_idle_color;
	this->outlineHoverColor = outline_hover_color;
	this->outlineActiveColor = outline_active_color;
}


//returns true if button has been clicked
bool Button::isPressed() const {

	if (buttonState == BTN_ACTIVE)
		return true;

	return false;
}

//Updates button colors with mouse over and checks to see if button was pressed
void Button::update(const sf::Vector2f& mousePosWindow) {


	buttonState = BTN_IDLE;

	if (shape.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePosWindow))) {
		buttonState = BTN_HOVER;


		if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
			buttonState = BTN_ACTIVE;
		}
	}

	switch (buttonState) {
	case BTN_IDLE:
		shape.setFillColor(idleColor);
		text.setFillColor(textIdleColor);
		shape.setOutlineColor(outlineIdleColor);
		break;

	case BTN_HOVER:
		shape.setFillColor(hoverColor);
		text.setFillColor(textHoverColor);
		shape.setOutlineColor(outlineHoverColor);
		break;

	case BTN_ACTIVE:
		shape.setFillColor(activeColor);
		text.setFillColor(textActiveColor);
		shape.setOutlineColor(outlineActiveColor);

		break;

	default:
		shape.setFillColor(sf::Color::Red);
		text.setFillColor(sf::Color::Blue);
		shape.setOutlineColor(sf::Color::Green);
		break;
	}

}

//draws the button to the screen
void Button::render(sf::RenderTarget& target) {
	target.draw(this->shape);
	target.draw(this->text);
}
