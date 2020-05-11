#pragma once

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

		calcTopSpeedPerGear();


	};


	~Car() {
		delete drivetrain;

	}
	
	void upgradeTurbo() {
		drivetrain->upgradeTurbo();
		drivetrain->loadTcuve();
		calcTopSpeedPerGear();

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
		drivetrain->loadGearRatios();
		calcTopSpeedPerGear();
		return true;

	}

	bool upgradeEng() {

		if (drivetrain->getEngine()->cRating == 'C') {
			drivetrain->setEngineClass('B');
			cout << "Upgrading Engine to " << 'B' << endl;
			calcTopSpeedPerGear();
			return true;

		} else if (drivetrain->getEngine()->cRating== 'B') {
			drivetrain->setEngineClass('A');
			cout << "Upgrading Engine to " << 'A' << endl;
			calcTopSpeedPerGear();
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

	double getAccel(int gear, int rpm, double speed) {

		double acceleration;
		double resistance;
		double airR;
		double rollR;
		double rollC;
		//int rpmIndex = (rpm / 100) - 10;
		//double toque 


		double toque = getExactT(rpm);
		double dif = drivetrain->getTransmistion()->diferentialRatio;
		double gearR = drivetrain->getTransmistion()->gearRatio[gear];


		double tAtWheel = (toque * dif * gearR) / (wheelD / 12);
		
		//printf("Torque %.03f\n", tAtWheel);

		double spd = (speed * .3048) * (speed * .3048);
		acceleration = tAtWheel / weight; //g's



		//double Drag = dCd * A * r * (.5 * V);

		airR = .5 * (AIR_DENSITY * spd * frontArea * dragCo);

		//Fr = 0.03 (1500 kg) (9.81 m / s2)

		//rollR = 0.03 (1500 kg) (9.81 m / s2);
		
		double tirePressure = 2.9;
		double kph = speed * 1.09728;
		
		//kph = 90;

		rollC = 0.005 + (1 / tirePressure) * (0.01 + 0.0095 * pow((kph / 100.0),2));
		//cout << "RC" << rollC<<endl;


		rollR = rollC*(weight* 0.453592)*(9.81);


	//	cout << "RR" << rollR << endl;

		resistance = airR;// +rollR;
		double W = weight * acceleration;
		acceleration = (W - resistance) / weight;
		

		//cout << "Resistance " << resistance  << endl;
		//cout << acceleration << "G's with drag" << endl;


		return acceleration;

	}

	double CalcResistance(double spd) {
		
		double 	resistance;
		double tirePressure = 2.9;
		double kph = spd * 1.09728;

		double airR;
		double rollR;
		double rollC;

		//kph = 90;

		rollC = 0.005 + (1 / tirePressure) * (0.01 + 0.0095 * pow((kph / 100.0), 2));

		rollR = rollC * (weight * 0.453592) * (9.81);

		
		resistance = rollR + (.5 * (AIR_DENSITY * spd * frontArea * dragCo));
		return resistance;
	}


	double calcToque(int rpm, int gear) {

		//double toque = getExactT(rpm);
		double differential = drivetrain->getTransmistion()->diferentialRatio;
		double gearRatio = drivetrain->getTransmistion()->gearRatio[gear];


		double tAtWheel = (getExactT(rpm) * differential * gearRatio) / (wheelD / 12);

		return tAtWheel;
	}

	double getExactT(int index) {

		//Car tCar('A');

		//tCar = *p->raceCar;

		//int revCount = p->raceCar->getDrivetrain()->getEngine()->maxRpm;
		int revCount = drivetrain->getEngine()->maxRpm;
		double lastVal;
		double nextVal;
		double lastI;
		double m;
		double newVal;;

		if (index < 1000) {
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
			if (i == index) {
				return newVal;
			}

		}
		return newVal;
	}


	void calcTopSpeedPerGear() {

		double topSpeed;
		double tireMovePre10;
		double rearRatio;
		double speed;
		double dif = drivetrain->getTransmistion()->diferentialRatio;

		for (size_t i = 0; i < drivetrain->getTransmistion()->highestGear +1.0; i++) {
			tireMovePre10 = wheelD * 3.14;
			rearRatio = drivetrain->getTransmistion()->gearRatio[i] * dif;
			speed = getMaxRPM() * 60.0 / rearRatio * tireMovePre10; //gear ratio speed = inches per hour
			topSpeed = speed / (5280 * 12.0);
			topSpeedperGear[i]= topSpeed;
			cout << "Top Speed: " << topSpeed << " in gear: " << i << endl;
		}

		topSpeedperGear[0] = 0;

	}


	


};

#endif