/***********************************************************
*Car.cpp
*By: Julian Stanton
*Assignment: Final Project
*Due 5/11/20
*
*Program Description:
*	Car Class does the calculations for the car and keeps
*	track of the stats
*
*************************************************************/

#include "Car.h"

//creates a car object with some base stats
Car::Car(char ratingClass) {
	cout << "Creating Car: Class " << ratingClass << endl;
	this->ratingClass = toupper(ratingClass);

	switch (toupper(ratingClass)) {
	case 'A':
		frontArea = 16.8 * metSqu;
		weight = 2200;
		dragCo = .20;
		break;
	case 'B':
		frontArea = 18.1 * metSqu;
		weight = 3400;
		dragCo = .22;
		break;
	case 'C':
	default:
		frontArea = 23.3 * metSqu;
		weight = 5000;
		dragCo = .3;
		break;
	}

	drivetrain = new Drivetrain(ratingClass);

	calcTopSpeedPerGear();
}
//deletes created objects
Car::~Car() {
	delete drivetrain;
}

//upgrade turbo stats
void Car::upgradeTurbo() {
	drivetrain->upgradeTurbo();
	drivetrain->loadTcuve();
	calcTopSpeedPerGear();
}

//upgrade Car stats
bool Car::upgradeCar() {

	if (ratingClass[0] == 'C') {
		drivetrain->setRating('B');
		ratingClass = "B";
		frontArea = 19.1 * metSqu;
		weight = 4500;
		dragCo = .26;

	} else if (ratingClass[0] == 'B') {
		drivetrain->setRating('A');
		ratingClass = "A";
		frontArea = 16.8 * metSqu;
		weight = 3000;
		dragCo = .22;


	} else return false;

	drivetrain->loadTcuve();
	drivetrain->loadGearRatios();
	calcTopSpeedPerGear();
	return true;
}
//upgrade engine states
bool Car::upgradeEng() {
	if (drivetrain->getEngine()->cRating == 'C') {
		drivetrain->setEngineClass('B');
		cout << "Upgrading Engine to " << 'B' << endl;
		calcTopSpeedPerGear();
		return true;

	} else if (drivetrain->getEngine()->cRating == 'B') {
		drivetrain->setEngineClass('A');
		cout << "Upgrading Engine to " << 'A' << endl;
		calcTopSpeedPerGear();
		return true;

	}


	return false;
}

//returns the max gear
int Car::getMaxGear() {
	return drivetrain->getTransmistion()->highestGear;
}
//returns the top speed possible in the gear
double Car::getTopSpeed(int gear) {
	return topSpeedperGear[gear];
}
//returns the max rpms
int Car::getMaxRPM() {
	return drivetrain->getEngine()->maxRpm;
}

//returns the cars drivetrain object
Drivetrain* Car::getDrivetrain() {
	return drivetrain;
}

//returns a string of the cars gear ratios
std::string Car::getGearRatios() {
	string temp;
	stringstream tempStream;
	for (size_t i = 0; i < drivetrain->getTransmistion()->highestGear+1; i++) {
		tempStream << fixed << setprecision(2) << drivetrain->getTransmistion()->gearRatio[i] << ",  ";
	}

	temp = tempStream.str();
	cout << temp << endl;
	return temp;
}

//calculates the acceleration of the car taking into account wind drag
double Car::getAccel(int gear, int rpm, double speed) {
	double acceleration;
	double resistance;
	double W;

	double toque = getExactT(rpm);
	double dif = drivetrain->getTransmistion()->diferentialRatio;
	double gearR = drivetrain->getTransmistion()->gearRatio[gear];

	double tAtWheel = (toque * dif * gearR) / (wheelD / 12);

	double spd = (speed * .3048) * (speed * .3048);

	acceleration = tAtWheel / weight; //g's

	resistance = .5 * (AIR_DENSITY * spd * frontArea * dragCo);
	W= weight * acceleration;
	acceleration = (W - resistance) / weight;


	return acceleration;
}

//calculates the resistance taking into account wind drag and rolling drag ish
double Car::CalcResistance(double spd) {

	double 	resistance;
	double tirePressure = 2.9;
	double kph = spd * 1.09728;


	double rollR;
	double rollC;


	rollC = 0.005 + (1 / tirePressure) * (0.01 + 0.0095 * pow((kph / 100.0), 2));

	rollR = rollC * (weight * 0.453592) * (9.81);


	resistance = rollR + (.5 * (AIR_DENSITY * spd * frontArea * dragCo));
	return resistance;
}

//calculates the toque of the car
double Car::calcToque(int rpm, int gear) {

	double differential = drivetrain->getTransmistion()->diferentialRatio;
	double gearRatio = drivetrain->getTransmistion()->gearRatio[gear];


	double tAtWheel = (getExactT(rpm) * differential * gearRatio) / (wheelD / 12);

	return tAtWheel;
}


//calculates the toque of the car in between vals on torque table
double Car::getExactT(int targetRPM) {
	int revCount = drivetrain->getEngine()->maxRpm;
	double lastVal;
	double nextVal;
	double lastI;
	double m;
	double newVal;;

	if (targetRPM < 1000) {
		return 0;
	}
	//cout << vCount << endl;

	//return 0;
	for (int i = 0; i < (revCount)-999; i++) {
		if (i % 100 == 0) {

			lastVal = drivetrain->getEngine()->tCurve[i / 100];
			//cout << lastVal << endl;
			lastI = i;
			if (i / 100 < revCount - 1) {
				nextVal = drivetrain->getEngine()->tCurve[(i / 100) + 1];
			}
		} else {

			m = (nextVal - lastVal) / 100;

			newVal = m * (i - lastI) + lastVal;
			//cout << newVal << endl;
		}
		if (i == targetRPM) {
			return newVal;
		}

	}
	return 0;
}
//calculates top speed per gear
void Car::calcTopSpeedPerGear() {
	double topSpeed;
	double tireMovePre10;
	double rearRatio;
	double speed;
	double dif = drivetrain->getTransmistion()->diferentialRatio;

	for (size_t i = 0; i < drivetrain->getTransmistion()->highestGear + 1.0; i++) {
		tireMovePre10 = wheelD * 3.14;
		rearRatio = drivetrain->getTransmistion()->gearRatio[i] * dif;
		speed = getMaxRPM() * 60.0 / rearRatio * tireMovePre10; //gear ratio speed = inches per hour
		topSpeed = speed / (5280 * 12.0);
		topSpeedperGear[i] = topSpeed;

	}

	topSpeedperGear[0] = 0;
}
