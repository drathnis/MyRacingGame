#include "Player.h"


int Player::pCount = 0;
Player::Player() {
	money = 0;
	pCount ++;
	cout << "There is" << pCount << " Players" << endl;
}

void Player::addMoney(const double amount) {
	money += amount;
}

void Player::subtractMoney(const double amount) {
	money -= amount;
}

double Player::getMoney() {
	return money;
}

