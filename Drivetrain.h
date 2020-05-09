#pragma once

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

	int horsePower;
	int turbo;
	double tCurve[RPM_MAX];
	int maxRpm;
};


struct Transmistion {

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

	Drivetrain() {

		rClass = 'C';
		engine.horsePower = 100;
		engine.turbo = 0;
		trans.diferentialRatio = 3.6;
		loadGearRatios();
		loadTcuve();

	}


	Drivetrain(char ratingClass) {

		rClass = toupper(ratingClass);

		switch (ratingClass) {
		case 'A':
			engine.horsePower = 500;
			engine.turbo = 30;
			trans.diferentialRatio = 3.0;
			break;
		case 'B':
			engine.horsePower = 300;
			engine.turbo = 10;
			trans.diferentialRatio = 3.3;
			break;
		case 'C':
			engine.horsePower = 100;
			engine.turbo = 0;
			trans.diferentialRatio = 3.6;

			break;
		default:
			break;
		}

		loadGearRatios();
		loadTcuve();

	}

	Drivetrain(Engine eng, Transmistion tran) {

		engine = eng;
		trans = tran;

	}

	Transmistion* getTransmistion() {

		return &trans;
	}

	Engine*	getEngine(){

		return &engine;
	}

	void loadTcuve() {

		int tempCount = 0;
		double temp = 0;
		string fileName = "torque/class" + rClass + "_t.txt";
		cout << fileName << endl;
		ifstream  myfile;
		myfile.open(fileName);
		string temp1;
		string temp2;
		if (!myfile) {
			cout << "Could not Open " << fileName<<" using 0s" << endl;

			for (size_t i = 0; i < RPM_MAX; i++) {
				engine.tCurve[tempCount] =0;
			}

			return;
		}

		while (!myfile.eof()) {

			myfile >> temp1 >> temp2;
			temp = stod(temp2);
			engine.tCurve[tempCount] = temp + (engine.horsePower / 10);
			engine.maxRpm = stoi(temp1);
			tempCount++;
		}

		for (size_t i = tempCount; i < RPM_MAX; i++) {
			engine.tCurve[i] = 0; //test this
		}

		//rpmMax = 6800;
		myfile.close();

	}

	void loadGearRatios() {

		int tempCount = 0;

		string fileName = "torque/class" + rClass + "_r.txt";
		cout << fileName << endl;
		ifstream  myfile;
		myfile.open(fileName);
		string temp1;
		if (!myfile) {
			cout << "Could not Open " << fileName << " using 0s" << endl;

			for (size_t i = 0; i < GEAR_MAX; i++) {
				trans.gearRatio[tempCount] = 0;
			}
			trans.highestGear = GEAR_MAX;
			return;
		}

		while (!myfile.eof()) {

			myfile >> temp1;
			trans.gearRatio[tempCount++] = stod(temp1);

		}

		trans.highestGear = tempCount;
		
		for (size_t i = tempCount; i < GEAR_MAX; i++) {
			trans.gearRatio[i] = 0; //test this
		}


		myfile.close();

	}

};

