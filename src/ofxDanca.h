#pragma once

#include "Camera.h"
#include "Vision.h"
#include "Interface.h"
#include "SharedData.h"

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
			shared_ptr<ofx::danca::SharedData> sd = make_shared<ofx::danca::SharedData>();
		
			camera = new ofx::danca::Camera(sd);
			camera->setup();
			
			vision = new ofx::danca::Vision(camera, sd);
			vision->setup();
			
			interface = new ofx::danca::Interface(vision, sd);
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