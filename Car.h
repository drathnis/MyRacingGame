#pragma once

#ifndef _CAR_H_
#define _CAR_H_



#include "Drivetrain.h"

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



public:

	Car(char ratingClass = 'C'){

		cout << "Creating Car: Class "<<ratingClass << endl;
		this->ratingClass = toupper(ratingClass);

		switch (toupper(ratingClass)) {
		case 'A':
			frontArea = 16.8 * metSqu;
			weight = 3000;
			dragCo = .22;
			break;
		case 'B':
			frontArea = 19.1 * metSqu;
			weight = 4500;
			dragCo = .26;
			break;
		case 'C':
		default:
			frontArea = 23.3 * metSqu;
			weight = 5000;
			dragCo = .3;
			break;
		}

		drivetrain = new Drivetrain(ratingClass);

		//calcTopSpeedPerGear();
		calRPMInc();

	};


	~Car() {
		delete drivetrain;

	}
	void upgradeTurbo() {
		drivetrain->upgradeTurbo();
		drivetrain->loadTcuve();

	}

	bool upgradeCar() {
		
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
		return true;

	}


	bool upgradeEng() {

		if (drivetrain->getEngine()->cRating == 'C') {
			drivetrain->setEngineClass('B');
			cout << "Upgrading Engine to " << 'B' << endl;
			return true;

		} else if (drivetrain->getEngine()->cRating== 'B') {
			drivetrain->setEngineClass('A');
			cout << "Upgrading Engine to " << 'A' << endl;
			return true;

		}


		return false;

	}


	char getCarClass() {
		return ratingClass[0];
	}

	int getMaxGear() {
		return drivetrain->getTransmistion()->highestGear;

	}
	double getTopSpeed(int gear) {
		return topSpeedperGear[gear];
	}

	int getMaxRPM() {
		return drivetrain->getEngine()->maxRpm;
	}

	Drivetrain* getDrivetrain() {
		return drivetrain;
	}

	string getGearRatios() {

		string temp;
		stringstream tempStream;
		for (size_t i = 0; i < drivetrain->getTransmistion()->highestGear; i++) {
			tempStream << fixed << setprecision(2) << drivetrain->getTransmistion()->gearRatio[i]<<" ";
		}
		temp = tempStream.str();
		return temp;
	}

	int getGearSpeeds(int index) {

		return gearSpeeds[index];
	}

	void calRPMInc() {

		double resault;

		int max = drivetrain->getTransmistion()->highestGear+1;
		gearSpeeds[0] = 60;

		for (size_t i = 1; i < max; i++) {
			 resault = drivetrain->getTransmistion()->gearRatio[i - 1] * 15;
			 gearSpeeds[i] = resault;
			 //cout << gearSpeeds[i] << endl;
		}

		

	}


	double getAccel(int gear, int rpm, double speed) {



		double accTest;
		double resistance;
		double fronal = frontArea;
		if (rpm < 1000) {
			return 0;
		} else if (rpm > RPM_MAX) {
				return 0;
		}
		

		int rpmIndex = (rpm / 100) - 10;
		double toque = drivetrain->getEngine()->tCurve[rpmIndex];


		double torq = toque;
		double dif = drivetrain->getTransmistion()->diferentialRatio;
		double gearR = drivetrain->getTransmistion()->gearRatio[gear-1];


		double tAtWhell = (torq * dif * gearR) / (wheelD / 12);
		
		//printf("Torque %.03f\n", tAtWhell);

		double spd = (speed * .3048) * (speed * .3048);
		accTest = tAtWhell / weight; //g's



		//double Drag = dCd * A * r * (.5 * V);

		resistance = .5 * (AIR_DENSITY * spd * frontArea * dragCo);
		double W = weight * accTest;
		accTest = (W - resistance) / weight;
		

		//cout << "Resistance " << resistance  << endl;
		//cout << accTest << "G's with drag" << endl;


		return accTest;

	}


	void calcTopSpeedPerGear() {



		double topSpeed;
		double tireMovePre10;
		double rearRatio;
		double speed;
		double dif = drivetrain->getTransmistion()->diferentialRatio;

		for (size_t i = 1; i < drivetrain->getTransmistion()->highestGear +1.0; i++) {
			tireMovePre10 = wheelD * 3.14;
			rearRatio = drivetrain->getTransmistion()->gearRatio[i-1] * dif;
			speed = getMaxRPM() * 60.0 / rearRatio * tireMovePre10; //gear ratio speed = inches per hour
			topSpeed = speed / (5280 * 12.0);
			topSpeedperGear[i]= topSpeed;
			cout << "Top Speed: " << topSpeed << " in gear: " << i << endl;
		}

		topSpeedperGear[0] = 0;


	}





};

#endif