#pragma once

#include "Camera.h"

class ofxDanca {
	public:
		void setup(){
			_camera.setup();
		}
	
		void update(){
			_camera.update();
		}
	
		void draw(){
			_camera.draw();
		}
	
	private:
		ofx::danca::Camera _camera;
};