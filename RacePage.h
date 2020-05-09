#pragma once
#ifndef _RACEPAGE_H_
#define _RACEPAGE_H_

#include "Page.h"
#include <cstdlib>

//#include <fstream>
//#include <iostream>
//#include <iomanip>
//#include <sstream>

#include "button.h"

class RacePage : public Page {


private:

	std::map<std::string, Button*> buttons;
	sf::Font wordFont;
	sf::Font numberFont;
	sf::RectangleShape background;
	sf::RectangleShape btnBackground;

	sf::RectangleShape waterTempBg;
	sf::RectangleShape waterTempFg;


	sf::RectangleShape playerProg;
	sf::RectangleShape playerProgBase;
	sf::RectangleShape opProg;
	sf::RectangleShape opProgBase;

	sf::Texture backgroundTexture;
	sf::Texture tachometerTexture;
	sf::Texture needleTexture;
	sf::CircleShape circles[4];
	sf::Clock clock;
	sf::Clock dt;
	sf::Clock opDt;
	sf::Clock raceStart;
	sf::Clock playerStart;
	sf::Sprite tachometerSprite;
	sf::Sprite needleSpite;
	
	//double * tCurve;
	double dt_;
	double opDt_;
	sf::Text currentGearText;
	sf::Text currentSpeedText;
	sf::Text infoText;
	sf::Text infoText2;
	string infoString; 
	string infoString2;

	GameData pageInfo;
	Car playerCar;
	Car opCar;

	stringstream tempStream;

	int rpms;
	bool startRace = false;
	bool countDown = false;
	bool driveEngaged = false;
	int countDownLights = 0;
	int gear;
	int lastGear;

	bool startedMoving = false;

	double speed = 0;
	double lastspeed = 0;

	double distanceCovered = 0;
	double targetDistance = 1320;

	bool throttle = false;

	//opponent  vars
	double opAccelSpeed = 0;
	double opTopSpeed = 0;
	int opGear = 0;
	int lastOpGear = 0;
	int opNeedlePos = 0;
	double opSpeed = 0;
	int gearChangeTime;

	bool newGearTime = true;
	int gearTimeCount = 0;
	double opDistanceCovered = 0;

	bool opFinished = false;
	bool playerFinished = false;

	double opFinishTime;
	double playerFinishTime;

	int waterTemp;

	bool enoughMoney;

	MyTimer debounceTimer;

	MyTimer raceTimer;




public:

	RacePage(GameData pageData);

	~RacePage() {}



	void initLights();

	bool initFonts();
	
	void initButtons();

	bool intitGraphics();

	void initWaterTemp();

	void renderProgress();

	void renderGraphics();

	void renderButtons(sf::RenderTarget* target);
	
	void render(sf::RenderTarget* wind);

	void updateProgress();

	void updateSpeedAndGear();

	void updateInfoText();

	
	void update(const double& time);

	void updateWaterTemp();

	void race();

	void userRpms();

	void runRace();

	void simRace();

	void drawLights(int count);

	void renderWaterTemp();

	void updatePlayerInput(const double& dt);

	void updateButtons();

	bool debounce();

	double mapVals(double x, double in_min, double in_max, double out_min, double out_max);

};

#endif