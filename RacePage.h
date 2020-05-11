/***********************************************************
*RacePage .h
*By: Julian Stanton
*Assignment: Final Project
*Due 5/11/20
*
*Program Description:
*	THe page where the magic happens lets race here!!!!
*
*************************************************************/
#ifndef _RACEPAGE_H_
#define _RACEPAGE_H_

#include "Page.h"
#include <cstdlib>

#include "button.h"

class RacePage : public Page {


private:

	std::map<std::string, Button*> buttons;
	sf::Font wordFont;
	sf::Font numberFont;
	sf::RectangleShape background;
	sf::RectangleShape btnBackground;

	sf::Image backgroundImg;
	sf::Texture backgroundTexture;

	sf::RectangleShape playerProg;
	sf::RectangleShape playerProgBase;
	sf::RectangleShape opProg;
	sf::RectangleShape opProgBase;

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
	

	sf::Text currentGearText;
	sf::Text currentSpeedText;
	sf::Text infoText;
	sf::Text infoText2;
	sf::Text controlsText;
	
	sf::SoundBuffer contDownBuff;
	sf::SoundBuffer contDownGOBuff;
	
	sf::Sound readySound;
	sf::Sound goSound;

	string infoString; 
	string infoString2;
	string controlsStr;

	GameData *pageData;
	Car *playerCar;
	Car *opCar;

	stringstream tempStream;


	int rpms;
	bool startRace;
	bool countDown;

	int countDownLights;
	int gear;


	double speed;


	double distanceCovered;
	double targetDistance;

	bool throttle;


	int opGear;
	int opRpms;
	double opSpeed;


	bool opThrottle;


	double opDistanceCovered;

	bool opFinished;
	bool playerFinished;

	double opFinishTime;
	double playerFinishTime;
	bool enoughMoney;

	MyTimer debounceTimer;
	MyTimer raceTimer;

	sf::Time elapsed;

	void initSounds();
	void initLights();
	bool initFonts();
	void initButtons();
	bool intitGraphics();

	void renderProgress();
	void renderGraphics();
	void renderButtons(sf::RenderTarget* target);

	void updateProgress();
	void updateSpeedAndGear();
	void updateInfoText();

	void race();
	void userRpms();
	void runRace();
	void simRace();
	void opRPMS();

	
	void drawLights(int count);

	void updatePlayerInput(const double& dt);

	void updateButtons();

	bool debounce();

	double mapVals(double x, double in_min, double in_max, double out_min, double out_max);

	bool initBackGournd();
	
public:

	RacePage(GameData *pageData);


	~RacePage();



	void render(sf::RenderTarget* wind);

	void update(const double& time);
	
};

#endif