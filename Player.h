#pragma once
#ifndef _PLAYER_H_
#define _PLAYER_H_


#include "Car.h"

class Player {
	static int pCount;

private:
	double money;


public:
	Car raceCar;
	Player();

	

	void addMoney(const double amount);
	void subtractMoney(const double amount);
	double getMoney();

	Car getCar() {
		return raceCar;
	}

};

#endif