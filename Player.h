#pragma once
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

public:
	
	Car *raceCar;
	Player();

	Car* playerCar() {
		return raceCar;
	}

	void changeCost(CarPart id) {
		switch (id) {
		case CarPart::body:
			carUprageCost += cInc+=10000.0;
			break;
		case CarPart::engine:
			engUprageCost += eInc += 500;
			break;
		case CarPart::turbo:
			turbUprageCost += tInc+=50;
			break;
		default:
			break;
		}
		
	}

	double getEngUpgradeCost() const{
		return engUprageCost;
	}

	double getCarUprageCost() const {
		return carUprageCost;
	}
	
	double getTurbUprageCost() const {
		return turbUprageCost;
	}

	void addMoney(const double amount);
	void subtractMoney(const double amount);
	double getMoney()const;



	//Car getCar() {
	//	return raceCar;
	//}

};

#endif