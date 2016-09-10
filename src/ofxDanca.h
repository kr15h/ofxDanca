#pragma once

#include "Camera.h"
#include "Vision.h"
#include "Interface.h"

class ofxDanca {
	public:
		ofxDanca(){
			camera = 0;
			vision = 0;
			interface = 0;
		}
	
		ofx::danca::Camera * camera;
		ofx::danca::Vision * vision;
		ofx::danca::Interface * interface;
	
		void setup(){
			camera = new ofx::danca::Camera();
			camera->setup();
			
			vision = new ofx::danca::Vision(camera);
			vision->setup();
			
			interface = new ofx::danca::Interface(vision);
			interface->setup();
		}
	
		void update(){
			camera->update();
			vision->update();
			interface->update();
		}
	
		void draw(){
			camera->draw();
			vision->draw();
			interface->draw();
		}
};