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
	Drivetrain(char ratingClass = 'C') {
		cout << "Creating Drive Train: Class " << ratingClass << endl;

		rClass = toupper(ratingClass);

		switch (rClass[0]) {
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
		engine.cRating = rClass[0];
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

	void upgradeTurbo() {
		engine.turbo += 20;
	}

	char getEngineClass() {
		return engine.cRating;
	}
	
	int getTurboRating() {
		return engine.turbo;
	}

	void setEngineClass(char ratingClass) {
		
		engine.cRating = ratingClass;

		switch (ratingClass) {
		case 'A':
			engine.horsePower = 500;
			engine.turbo += 30;
			trans.diferentialRatio = 3.0;
			break;
		case 'B':
			engine.horsePower = 300;
			engine.turbo += 10;
			trans.diferentialRatio = 3.3;
			break;
		case 'C':
			engine.horsePower = 100;
			engine.turbo += 0;
			trans.diferentialRatio = 3.6;
			break;
		default:
			break;
		}

		loadTcuve();

	}


	void loadTcuve() {
		engine.maxT = 0;
		engine.minT = 1000;
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
			temp += +((engine.horsePower +engine.turbo) / 10);

			if (temp> engine.maxT) {
				engine.maxT = temp;
			} else if(temp < engine.minT) {
				engine.minT = temp;
			}

			engine.tCurve[tempCount] = temp;
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

