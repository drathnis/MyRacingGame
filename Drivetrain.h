/***********************************************************
*Drivetrain.h
*By: Julian Stanton
*Assignment: Final Project
*Due 5/11/20
*
*Program Description:
*	The power of the car
*
*************************************************************/

#ifndef _DRIVETRAIN_H_
#define _DRIVETRAIN_H_

#include <string>
#include <iomanip>
#include <cctype>
#include <sstream>

#include <fstream>
#include <iostream>

using namespace std;


const int GEAR_MAX = 9; //8+neutral
const int RPM_MAX = 100; //x100

const string FILE_END = "_.txt"; //x100
struct Engine {

	char cRating;
	int horsePower;
	int turbo;
	double minT;
	double maxT;
	double tCurve[RPM_MAX];
	int maxRpm;
};


struct Transmistion {

	char cRating;
	int highestGear;
	double gearRatio[GEAR_MAX];
	double diferentialRatio;
	
};



class Drivetrain {


private:
	
	Transmistion trans;
	Engine engine;

	string rClass;



public:
	Drivetrain(char ratingClass = 'C');

	Drivetrain(Engine eng, Transmistion tran);

	Transmistion* getTransmistion();

	Engine*	getEngine();

	void upgradeTurbo();

	char getEngineClass();
	
	int getTurboRating();

	void setEngineClass(char ratingClass);

	void setRating(char r);

	void loadTcuve();

	void loadGearRatios();


};

#endif