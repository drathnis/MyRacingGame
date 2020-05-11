/***********************************************************
*Car.h
*By: Julian Stanton
*Assignment: Final Project
*Due 5/11/20
*
*Program Description:
*	Car Class
*
*************************************************************/

#ifndef _CAR_H_
#define _CAR_H_



#include "Drivetrain.h"
#include <cmath>
enum class CarPart {
	body,
	engine,
	turbo

};

class Car {

private:


	Drivetrain *drivetrain;

	//static const int MAX_NUMBER_OF_GEARS = 9;

	double metSqu = 0.092903;

	double AIR_DENSITY = 1.225;
	double topSpeedperGear[GEAR_MAX];

	double wheelD = 12;
	double weight;
	double frontArea;
	double dragCo;

	//double gearRatio[MAX_NUMBER_OF_GEARS];


	int gearSpeeds[GEAR_MAX];

	string ratingClass;

	void calcTopSpeedPerGear();

	double getExactT(int targetRPM);

public:

	Car(char ratingClass = 'C');;

	~Car();
	
	void upgradeTurbo();

	bool upgradeCar();

	bool upgradeEng();

	int getMaxGear();

	double getTopSpeed(int gear);

	int getMaxRPM();

	Drivetrain* getDrivetrain();

	string getGearRatios();

	double getAccel(int gear, int rpm, double speed);


	double CalcResistance(double spd);

	double calcToque(int rpm, int gear);


};

#endif