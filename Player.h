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

#ifndef _PLAYER_H_
#define _PLAYER_H_


#include "Car.h"

class Player {
	static int pCount;

private:

	double money;
	double carUprageCost;
	double engUprageCost;
	double turbUprageCost;
	double cInc;
	double eInc;
	double tInc;

	Car* raceCar;

public:
	
	
	Player();
	~Player() {
		delete raceCar;
		
	};
	Car* playerCar();

	void setPlayerCar(Car *c) {
		raceCar = c;
		
	};
	
	void changeCost(CarPart id);

	double getEngUpgradeCost() const;

	double getCarUprageCost() const;
	
	double getTurbUprageCost() const;

	void addMoney(const double amount);

	void subtractMoney(const double amount);

	double getMoney()const;


};

#endif