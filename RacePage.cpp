#include "RacePage.h"

RacePage::RacePage(GameData pageData) :Page(pageData) {
	pageInfo = pageData;
	background.setFillColor(sf::Color(60, 6, 96));
	background.setSize(sf::Vector2f(pageInfo.window->getSize().x, pageInfo.window->getSize().y));


	if (!initFonts()) {
		this->quitePage();
	}

	initButtons();
	if (!intitGraphics()){
		this->quitePage();
	}

	playerCar = pageInfo.player->getCar();

	debounceTimer.setInterval(milliseconds(200));

	raceTimer.setInterval(milliseconds(30));

	gear = 0;
	speed = 0;
	rpms = 0;

	opCar = Car('A');
   // playerCar = Car('A');
	
	if (pageInfo.player->getMoney()>500){
		enoughMoney = true;
		infoString = "Press Start To Begin";
		infoString2 = " ";
	} else {
		enoughMoney = false;
		infoString = "You do not have enough";
		infoString2 = "money to race";
	}

	pageInfo.player->subtractMoney(10000);

}

void RacePage::initLights() {
	sf::CircleShape tempCircle;
	tempCircle.setRadius(25);
	tempCircle.setFillColor(sf::Color(255, 119, 0));
	tempCircle.setPosition(320, 20);
	circles[0] = tempCircle;


	tempCircle.setPosition(320, 80);
	circles[1] = tempCircle;


	tempCircle.setPosition(320, 140);
	circles[2] = tempCircle;

	tempCircle.setFillColor(sf::Color(25, 114, 7));
	tempCircle.setPosition(320, 200);
	circles[3] = tempCircle;
}

bool RacePage::initFonts() {
	if (!wordFont.loadFromFile("Fonts/Roboto-Regular.ttf")) {
		return 0;
	}
	if (!numberFont.loadFromFile("Fonts/JerseyM54-aLX9.ttf")) {
		cout << "Could Not Load Font" << endl;
		return 0; 

	}
	return 1;
}

void RacePage::initButtons() {
	buttons["START_STATE"] = new Button(
		500, 50,
		150, 60,
		&wordFont, "START", 50,
		sf::Color::Red, sf::Color::Green, sf::Color::Blue,
		sf::Color::Blue, sf::Color::Magenta, sf::Color::Cyan
	);


	buttons["BACK_STATE"] = new Button(
		800, 50,
		150, 50,
		&wordFont, "BACK", 40,
		sf::Color::Red, sf::Color::Green, sf::Color::Blue,
		sf::Color::Blue, sf::Color::Magenta, sf::Color::Cyan
	);
}

bool RacePage::intitGraphics() {
	

	if (!tachometerTexture.loadFromFile("Resources/tech.png")) {
		return false;
	}

	tachometerSprite.setTexture(tachometerTexture);
	tachometerSprite.setPosition(0, 0);


	if (!needleTexture.loadFromFile("Resources/needle.png")) {
		return false;
	}
	rpms = 1000;
	needleSpite.setTexture(needleTexture);
	needleSpite.setOrigin(15, 137);
	needleSpite.setPosition(137, 140);

	initLights();


	currentGearText.setFillColor(sf::Color::White);
	currentGearText.setFont(numberFont);
	currentGearText.setString(to_string(gear+1));
	currentGearText.setCharacterSize(80);
	currentGearText.setPosition(sf::Vector2f(117, 157));
	
	tempStream.str("");
	tempStream << fixed << setprecision(0) << speed << " mph";

	
	currentSpeedText.setFillColor(sf::Color::White);
	currentSpeedText.setFont(numberFont);
	currentSpeedText.setString(tempStream.str());
	currentSpeedText.setCharacterSize(40);
	currentSpeedText.setPosition(sf::Vector2f(90, 250));

	playerProg.setSize(sf::Vector2f(10,40));
	playerProg.setFillColor(sf::Color::Green);
	playerProg.setPosition(200, 400);


	playerProgBase.setSize(sf::Vector2f(660, 40));
	playerProgBase.setFillColor(sf::Color::Red);
	playerProgBase.setPosition(200, 400);

	opProg.setSize(sf::Vector2f(10, 40));
	opProg.setFillColor(sf::Color::Green);
	opProg.setPosition(200, 445);
	
	opProgBase.setSize(sf::Vector2f(660, 40));
	opProgBase.setFillColor(sf::Color::Red);
	opProgBase.setPosition(200, 445);


	infoText.setFillColor(sf::Color::White);
	infoText.setFont(wordFont);
	infoText.setString(infoString);
	infoText.setCharacterSize(40);
	infoText.setPosition(400,150);

	infoText2.setFillColor(sf::Color::White);
	infoText2.setFont(wordFont);
	infoText2.setString(infoString2);
	infoText2.setCharacterSize(40);
	infoText2.setPosition(400, 200);



	initWaterTemp();

	return true;
}

void RacePage::initWaterTemp() {

	waterTemp = 0;

	waterTempFg.setSize(sf::Vector2f(10, waterTemp));
	waterTempFg.setFillColor(sf::Color::Red);
	waterTempFg.setPosition(290, 250);


	waterTempFg.rotate(180);

	waterTempBg.setSize(sf::Vector2f(10, 200));
	waterTempBg.setFillColor(sf::Color::Green);
	waterTempBg.setPosition(290, 250);
	
	waterTempBg.rotate(180);

}

void RacePage::renderProgress() {


	pageInfo.window->draw(playerProgBase);
	pageInfo.window->draw(opProgBase);

	pageInfo.window->draw(playerProg);
	pageInfo.window->draw(opProg);


}

void RacePage::renderGraphics() {

	pageInfo.window->draw(tachometerSprite);

	needleSpite.setRotation(mapVals(rpms, 0, playerCar.getMaxRPM(), 236, 485));

	pageInfo.window->draw(needleSpite);

	pageInfo.window->draw(currentGearText);

	pageInfo.window->draw(currentSpeedText);

	pageInfo.window->draw(infoText);
	pageInfo.window->draw(infoText2);

	renderWaterTemp();
	drawLights(countDownLights);
	renderProgress();

}

void RacePage::renderButtons(sf::RenderTarget* target) {
	for (auto& it : this->buttons) {
		it.second->render(*target);

	}
}

void RacePage::render(sf::RenderTarget* wind) {
	wind->draw(background);

	renderWaterTemp();
	renderGraphics();
	renderButtons(wind);
}

void RacePage::updateProgress() {

	playerProg.setSize(sf::Vector2f(distanceCovered / 2,40 ));
	opProg.setSize(sf::Vector2f(opDistanceCovered / 2, 40));
}

void RacePage::updateSpeedAndGear() {

	tempStream.str("");
	tempStream << fixed << setprecision(0) << speed << " mph";
	currentSpeedText.setString(tempStream.str());
	
	string gearText;
	if (gear==0) {
		gearText = 'N';
	}
	else {
		gearText = to_string(gear);
	}
	
	currentGearText.setString(gearText);


}

void RacePage::updateInfoText() {


	infoText.setString(infoString);
	infoText2.setString(infoString2);

}

void RacePage::update(const double& time) {
	updateMousePositions();

	updateSpeedAndGear();
	updateButtons();
	updatePlayerInput(time);

	if (startRace) {
		race();
	}

	updateInfoText();

	updateWaterTemp();
	updateProgress();

}

void RacePage::updateWaterTemp() {


	waterTempFg.setSize(sf::Vector2f(10, waterTemp));
}

void RacePage::race() {
	
	if (countDown) {
		sf::Time elapsed = clock.getElapsedTime();
		int elapsedTime = (int)elapsed.asSeconds();

		switch (elapsedTime) {
		case 0:
			circles[0].setFillColor(sf::Color::Yellow);
			break;
		case 1:
			circles[1].setFillColor(sf::Color::Yellow);

			 break;
		case 2:
			circles[2].setFillColor(sf::Color::Yellow);
			break;
		case 3:
			cout << "0" << endl;
			cout << "RACE!!!" << endl;
			circles[3].setFillColor(sf::Color::Green);
			countDown = false;
			raceStart.restart();
			opDt.restart();
			dt.restart();
			playerStart.restart();
			break;
		default:
			break;
		}

	} else if (opFinished && playerFinished) {
		startRace = false;
		cout << "Race Finished" << endl;

		if (playerFinishTime< opFinishTime){
			infoString = "You Won!";
			infoString2 = "";
			pageInfo.player->addMoney(1000);
		} else {

			infoString = "You Lost!  Time: " + to_string(playerFinishTime);
			infoString2 = "opponent's Time: " + to_string(opFinishTime);
			pageInfo.player->subtractMoney(500);
		}


		cout << "Player's time:" << playerFinishTime << endl;
		cout << "Opponent's time:" << opFinishTime << endl;
	} 

	if (raceTimer.isItTime()){
	   
		userRpms();
		if (!countDown) {
			simRace();
			runRace();
		}
		else if (gear>0){
			cout << "FALSE START!!" << endl;
			infoString = "FALSE START!!";
			infoString2 = "You Lose! ";
			pageInfo.player->subtractMoney(1000);
			startRace = false;

		}
		
	}


}

void RacePage::userRpms() {

	double dif;
	double maxSpeed = playerCar.getTopSpeed(gear);

	if (throttle) {
		rpms += playerCar.getGearSpeeds(gear);

		dif = speed - maxSpeed;
		//        printf("dif: %f\n", dif);
		if (speed > maxSpeed - 3) {
			dif = speed - maxSpeed;
			rpms += playerCar.getGearSpeeds(gear) + 30 + dif * 2;
		}


		// printf("inc by %d\n", playerCar.getGearSpeeds(gear));

		if (rpms > playerCar.getMaxRPM()) {
			rpms = playerCar.getMaxRPM();
		}

	} else {
		rpms -= 80;

		if (rpms < 500) {
			rpms = 500;
		}

	}

}

void RacePage::runRace() {

	double maxSpeed = playerCar.getTopSpeed(gear);
  

	if (gear > 1) {
		if (speed < playerCar.getTopSpeed(gear - 1)) {
		   // printf("STALL!\n");
		}
	
	}
   // if ((gear > 0)&&(speed < maxSpeed)){
	if ((gear > 0)) {
		if (speed == 0) {
			playerStart.restart();
		}


			double temp = playerCar.getAccel(gear, rpms, speed); //gs

			if (temp < 0) {
				temp = 0;
			}

			temp *= 32.174; // f/s^2

			double speedInc = (temp * dt.getElapsedTime().asSeconds());
		if ((speed < maxSpeed)) {
			speed = speed + speedInc;// (temp * dt.getElapsedTime().asSeconds());

			//printf("accel %.03f\n", speed);
		}
		else {
			speed += speedInc * .4;;
		}
		
	}

	if (rpms>playerCar.getMaxRPM()-500){

		waterTemp += 9;
		printf("heat: %d\n", waterTemp);
	} else {

		if (waterTemp>30) {
			waterTemp -= 1;
		}

	}


	distanceCovered += speed * dt.getElapsedTime().asSeconds();
	
	if (distanceCovered >= targetDistance){

		playerFinishTime = raceStart.getElapsedTime().asSeconds();
		cout << "Time: " << playerFinishTime << endl;
		playerFinished = true;
	}


	dt.restart();
}

void RacePage::simRace() {

	static double lastacc = 0;

	if (opFinished) {
		opNeedlePos = 1000;
		opGear = 0;
		return;
	}


	if (opGear > opCar.getMaxGear() - 1) {
		opGear = opCar.getMaxGear() - 1;
	} else if (opGear < 0) {
		opGear = 0;
	}

	if (opGear != lastOpGear) {
		lastOpGear = opGear;
		//cout << opGear << endl;
		opNeedlePos = 1000;

	}


	opNeedlePos += opCar.getGearSpeeds(opGear);

	if (opNeedlePos > opCar.getMaxRPM()) {
		opNeedlePos = opCar.getMaxRPM();

	}


	opTopSpeed = opCar.getTopSpeed(opGear);// getTopSpeed();


	opAccelSpeed = opCar.getAccel(opGear, opNeedlePos, opSpeed);


	if (opAccelSpeed > 0) {
		opSpeed += opAccelSpeed;

	} else {
		opAccelSpeed = 0;
	}

	opDt_ = opDt.getElapsedTime().asSeconds();
	opDt.restart();
	opDistanceCovered += opSpeed * opDt_ + opAccelSpeed * (opDt_ * opDt_);



	if (opSpeed > opTopSpeed) {
		opSpeed = opTopSpeed;
		//cout << "Change Gear?";
		//change gear here?
		opGear++;
	}

	if (opDistanceCovered >= targetDistance && !opFinished) {

		opFinishTime = raceStart.getElapsedTime().asSeconds();
		cout << "Time: " << opFinishTime<<endl;

		opFinished = true;

	}

	//system("CLS");
	//cout << opGear << endl;
	//cout << opSpeed << endl;
	//cout << opNeedlePos << endl;


}

void RacePage::drawLights(int count) {
	for (int i = 0; i < 4; i++) {
		pageInfo.window->draw(circles[i]);
	}
}

void RacePage::renderWaterTemp() {

	pageInfo.window->draw(waterTempBg);
	pageInfo.window->draw(waterTempFg);
}

void RacePage::updatePlayerInput(const double& dt) {
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W) && debounce()) {
		//cout << "W" << endl;
		gear++;
		rpms /= 3;
		if (gear > playerCar.getMaxGear()) {
			gear = playerCar.getMaxGear();
		}
		debounceTimer.reset();
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S) && debounce()) {
		//cout << "S" << endl;
		debounceTimer.reset();
		gear--;
		rpms *= 1.5;
		if (gear < 0) {
			gear = 0;
		}

	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space)) {
		throttle = true;
	}
	else {
		throttle = false;
	}

}

void RacePage::updateButtons() {
	for (auto& it : this->buttons) {
		it.second->update(mousePosView);
	}

	if (buttons["BACK_STATE"]->isPressed()) {

		while (buttons["BACK_STATE"]->isPressed()) {
			//pause so we don't get double clicks
			for (auto& it : this->buttons) {
				it.second->update(mousePosView);
			}

		}

		this->quitePage();
	}



	if (buttons["START_STATE"]->isPressed()) {

		while (buttons["START_STATE"]->isPressed()) {
			//pause so we don't get double clicks
			for (auto& it : this->buttons) {
				it.second->update(mousePosView);
			}

		}

		rpms = 1000;
		cout << "Start Racing" << endl;
		startRace = true;
		countDown = true;
		clock.restart();
	}
}

bool RacePage::debounce() {
	if (debounceTimer.isItTime()) {
		return true;
	}

	return false;
}

double RacePage::mapVals(double x, double in_min, double in_max, double out_min, double out_max) {
	return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}
