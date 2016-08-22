#include "ofApp.h"

#define WHEEL_BASE  80


void ofApp::setup(){
	heading = steer = 0.0;
	speed = 0;
	pos.x = ofGetWidth() / 2.0;
	pos.y = ofGetHeight() / 2.0;

	positionLog.clear();

	ofNoFill();
	ofSetBackgroundColor(ofColor::black);
	ofSetFrameRate(60);
	ofEnableBlendMode(OF_BLENDMODE_ADD);
}


void ofApp::update(){
	positionLog.push_back({
		pos,
		ofPoint(
			pos.x + cos(heading - PI/2) * WHEEL_BASE,
			pos.y + sin(heading - PI/2) * WHEEL_BASE
		)
	});
	while(positionLog.size() >= 240){
		positionLog.erase(positionLog.begin());
	}

	if(-0.01 <= steer && steer <= 0.01){
		pos.x += cos(heading - PI/2) * speed;
		pos.y += sin(heading - PI/2) * speed;
	}else{
		const double center_angle = PI/2 - steer;
		const double center_distance = WHEEL_BASE * cos(steer) / cos(center_angle);

		const double run_angle = speed / center_distance;
		const double shift_angle = (PI - run_angle) / 2.0;
		const double shift_length = center_distance * sin(run_angle) / sin(shift_angle);

		if(speed != 0){
			pos.x += cos(heading - shift_angle) * shift_length;
			pos.y += sin(heading - shift_angle) * shift_length;
			heading += run_angle;
		}
	}
}


void ofApp::draw(){
	for(auto p: positionLog){
		ofSetColor(ofColor::green, 64);
		ofDrawCircle(p.first, 6);
		ofSetColor(ofColor::blue, 64);
		ofDrawCircle(p.second, 6);
	}

	ofPushMatrix();

	ofTranslate(pos);
	ofRotate(heading * 180 / PI);
	ofSetColor(ofColor::white, 255);
	ofDrawRectangle(-20, -WHEEL_BASE - 10, 40, WHEEL_BASE + 20);

	ofDrawRectangle(-40, -10, 80, 20);

	ofSetColor(ofColor::green, 200);
	ofDrawLine(-1000, 0, 1000, 0);

	ofTranslate(0, -WHEEL_BASE);
	ofRotate(steer * 180 / PI);
	ofSetColor(ofColor::white, 255);
	ofDrawRectangle(-40, -10, 80, 20);

	ofSetColor(ofColor::green, 200);
	ofDrawLine(-1000, 0, 1000, 0);

	ofPopMatrix();
}


void ofApp::keyPressed(int key){
	switch(key){
	case OF_KEY_RIGHT:
		steer += 0.05;
		break;
	case OF_KEY_LEFT:
		steer -= 0.05;
		break;
	case OF_KEY_UP:
		speed += 1;
		break;
	case OF_KEY_DOWN:
		speed -= 1;
		break;
	case 'd':
		heading += 0.05;
		break;
	case 'a':
		heading -= 0.05;
		break;
	case ' ':
		setup();
		break;
	}
}
