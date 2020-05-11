/***********************************************************
*Player.h
*By: Julian Stanton
*Assignment: Final Project
*Due 5/11/20
*
*Program Description:
*	The Class the keep track of all the player stats and car
*
*************************************************************/

#include "Player.h"


int Player::pCount = 0;
Player::Player() {

	money = 15000;
	carUprageCost = 20000;
	engUprageCost = 2300;
	turbUprageCost = 500;
	cInc = 20000;
	eInc = 1000;
	tInc = 100;

}

Car* Player::playerCar() {
	return raceCar;
}

void Player::changeCost(CarPart id) {
	switch (id) {
	case CarPart::body:
		carUprageCost += cInc += 10000.0;
		break;
	case CarPart::engine:
		engUprageCost += eInc += 500;
		break;
	case CarPart::turbo:
		turbUprageCost += tInc += 50;
		break;
	default:
		break;
	}
}

double Player::getEngUpgradeCost() const {
	return engUprageCost;
}

double Player::getCarUprageCost() const {
	return carUprageCost;
}

double Player::getTurbUprageCost() const {
	return turbUprageCost;
}

void Player::addMoney(double amount) {
	money += amount;
}

void Player::subtractMoney(double amount) {
	money -= amount;
}

double Player::getMoney() const {
	return money;
}

