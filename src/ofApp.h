#pragma once

#include <vector>

#include <ofMain.h>


class ofApp : public ofBaseApp{
private:
	ofPoint pos;
	double steer, heading;
	int speed;

	std::vector<ofPoint> positionLog;

public:
	void setup();
	void update();
	void draw();

	void keyPressed(int key);
};
