/***********************************************************
*Drivetrain.cpp
*By: Julian Stanton
*Assignment: Final Project
*Due 5/11/20
*
*Program Description:
*	The powerhouse of the car, has the transmission and engine
*
*************************************************************/

#include "Drivetrain.h"

Drivetrain::Drivetrain(Engine eng, Transmistion tran) {
	engine = eng;
	trans = tran;
}

Drivetrain::Drivetrain(char ratingClass /*= 'C'*/) {
	cout << "Creating Drivetrain: Class " << ratingClass << endl;

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

Transmistion* Drivetrain::getTransmistion() {
	return &trans;
}

Engine* Drivetrain::getEngine() {
	return &engine;
}

void Drivetrain::upgradeTurbo() {
	engine.turbo += 60;
}

char Drivetrain::getEngineClass() {
	return engine.cRating;
}

int Drivetrain::getTurboRating() {
	return engine.turbo;
}

void Drivetrain::setEngineClass(char ratingClass) {

	engine.cRating = ratingClass;

	switch (ratingClass) {
	case 'A':
		engine.horsePower = 800;
		engine.turbo += 50;
		trans.diferentialRatio = 3.0;
		break;
	case 'B':
		engine.horsePower = 560;
		engine.turbo += 30;
		trans.diferentialRatio = 3.3;
		break;
	case 'C':
		engine.horsePower = 300;
		engine.turbo += 0;
		trans.diferentialRatio = 3.6;
		break;
	default:
		break;
	}

	loadTcuve();
}

void Drivetrain::setRating(char r) {
	rClass = r;
	trans.cRating = r;
}

void Drivetrain::loadTcuve() {
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
		cout << "Could not Open " << fileName << " using 0s" << endl;

		for (size_t i = 0; i < RPM_MAX; i++) {
			engine.tCurve[tempCount] = 0;
		}

		return;
	}

	while (!myfile.eof()) {

		myfile >> temp1 >> temp2;
		temp = stod(temp2);
		temp += +((engine.horsePower + engine.turbo) / 10);

		if (temp > engine.maxT) {
			engine.maxT = temp;
		} else if (temp < engine.minT) {
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

void Drivetrain::loadGearRatios() {
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
		trans.gearRatio[++tempCount] = stod(temp1);

	}
	trans.gearRatio[0] = 0;
	trans.highestGear = tempCount;

	for (size_t i = tempCount + 1; i < GEAR_MAX; i++) {
		trans.gearRatio[i] = 0; //test this
	}


	myfile.close();
}
