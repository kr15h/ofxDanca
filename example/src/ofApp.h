#pragma once

#include "ofMain.h"
#include "ofxDanca.h"

class ofApp : public ofBaseApp {
    
public:
	void setup(){
		danca.setup();
	}

	void update(){
		danca.update();
	}

	void draw(){
		danca.draw();
	}

	ofxDanca danca;
};
