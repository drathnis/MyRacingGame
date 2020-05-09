#pragma once

#ifndef _CAR_H_
#define _CAR_H_



//#include "Page.h"

#include "Engine.h"
#include <fstream>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>

using namespace std;


class Car {

private:

	static const int MAX_NUMBER_OF_GEARS = 9;

	double metSqu = 0.092903;

	double AIR_DENSITY = 1.225;
	double topSpeedperGear[MAX_NUMBER_OF_GEARS] = {0};
	int maxGear;
	int rpmMax;
	double tCurve[100];
	double wheelD = 12;
	double weight;
	double frontArea;
	double dragCo;

	double gearRatio[MAX_NUMBER_OF_GEARS];// { 4,2.75,1.77,1.33,.95, .71 };
	double diferentialRatio = 3.5;

	int gearSpeeds[MAX_NUMBER_OF_GEARS];// 55, 45, 35, 20, 10, 5 };

	string ratingClass;

	int hp;


public:



	Car(char ratingClass = 'C'){


		this->ratingClass = toupper(ratingClass);

		switch (ratingClass) {
		case 'A':
			frontArea = 16.8 * metSqu;
			weight = 3000;
			dragCo = .22;
			hp = 400;
			break;
		case 'B':
			frontArea = 19.1 * metSqu;
			weight = 4500;
			dragCo = .26;
			hp = 260;
			break;
		case 'C':
			frontArea = 23.3* metSqu;
			weight = 5000;
			dragCo = .3;
			hp = 100;
			break;
		default:
			break;
		}


		if (!loadTcuve()){
			return;
		}
		loadGearRatios();
		calcTopSpeedPerGear();
		calRPMInc();

		//debug();

		//cout << "Created Car"<<endl;
	};


	//void debug() {

	//	double spd = 10 * 0.3048;
	//	double resistance;// = .5 * (AIR_DENSITY * spd * frontArea * dragCo);

	//	//resistance = dragCo * ((AIR_DENSITY * (spd * spd)) / 2) * frontArea;

	//	//D = Cd * A * .5 * r * V^2

	//	double dCd = .3;
	//	double A = frontArea;
	//	double r = 1.225;

	//	A = 2.164;
	//	double V = spd * spd;

	//	double Drag = (dCd * A * r);// *(.5 * V);
	//	Drag *= (.5 * V);
	//    printf("debug %.03f\n", Drag);

	//}

	~Car() {
		cout << "deleted"<<endl;
		//TODO delete [] tCurve;

	}

	int getMaxGear() {
		return maxGear;

	}
	double getTopSpeed(int gear) {
		return topSpeedperGear[gear];
	}

	int getMaxRPM() {
		return rpmMax;
	}
	string getGearRatios() {

		string temp;
		//string temp2;
		stringstream tempStream;
		for (size_t i = 0; i < maxGear; i++) {
			tempStream << fixed << setprecision(2) << gearRatio[i]<<" ";
			//temp += tempStream.str();
			//temp += "    ";
			//tempStream.clear();
		}
		temp = tempStream.str();
		return temp;
	}

	int getGearSpeeds(int index) {

		return gearSpeeds[index];
	}

	void calRPMInc() {

		double resault;

		int max = maxGear +1;
		gearSpeeds[0] = 60;

		for (size_t i = 1; i < max; i++) {
			 resault = gearRatio[i - 1] * 15;
			 gearSpeeds[i] = resault;
			 cout << gearSpeeds[i] << endl;
		}

		

	}


	double getAccel(int gear, int rpm, double speed) {

		double accTest;
		double resistance;
		double fronal = frontArea;
		if (rpm < 1000) {
			return 0;
		}

		int rpmIndex = (rpm / 100) - 10;
		double toque = tCurve[rpmIndex];


		double torq = toque;
		double dif =diferentialRatio;
		double gearR = gearRatio[gear-1];


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

	bool loadTcuve() {

		int tempCount = 0;
		double temp = 0;
		string fileName = "torque/class" + ratingClass + "_t.txt";
		ifstream  myfile;
		myfile.open(fileName);
		string temp1;
		string temp2;
		if (!myfile) {
			cout << "Could not Open" << fileName << endl;
			return 0;
		}

		while (!myfile.eof()) {

			myfile >> temp1 >> temp2;
			temp = stod(temp2);
			tCurve[tempCount] = temp + (hp/10);
			rpmMax = stoi(temp1);
			tempCount++;
		}
		rpmMax = 6800;
		myfile.close();
		return 1;
	}
	
	void loadGearRatios() {

		int tempCount = 0;
		string fileName = "torque/class" + ratingClass + "_r.txt";
		ifstream  myfile;
		myfile.open(fileName);
		string temp1;
		if (!myfile) {
			cout << "Could not Open" << fileName << endl;
			return;
		}

		while (!myfile.eof()) {

			myfile >> temp1;
			gearRatio[tempCount++] = stod(temp1);

		}
		maxGear = tempCount;
		myfile.close();

	}

	void calcTopSpeedPerGear() {

		double topSpeed;
		double tireMovePre10;
		double rearRatio;
		double speed;
		for (size_t i = 1; i < maxGear+1; i++) {
			tireMovePre10 = wheelD * 3.14;
			rearRatio = gearRatio[i-1] * diferentialRatio;
			speed = rpmMax * 60.0 / rearRatio * tireMovePre10; //gear ratio speed = inches per hour
			topSpeed = speed / (5280 * 12.0);
			topSpeedperGear[i]= topSpeed;
			cout << "Top Speed: " << topSpeed << " in gear: " << i << endl;
		}

		topSpeedperGear[0] = 0;

	}





};

#endif