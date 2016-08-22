#pragma once

#include <vector>
#include <utility>

#include <ofMain.h>


class ofApp : public ofBaseApp{
private:
	ofPoint pos;
	double steer, heading;
	int speed;

	std::vector< std::pair<ofPoint, ofPoint> > positionLog;

public:
	void setup();
	void update();
	void draw();

	void keyPressed(int key);
};
