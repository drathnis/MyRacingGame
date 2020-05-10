#include "Player.h"


int Player::pCount = 0;
Player::Player() {

	money = 100000;
	carUprageCost = 20000;
	engUprageCost = 1000;
	turbUprageCost = 100;
	int cInc = 20000;
	int eInc = 1000;
	int tInc = 100;

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

