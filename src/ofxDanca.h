#pragma once

#include "Camera.h"
#include "Vision.h"

// TODO: consider SharedData object

class ofxDanca {
	public:
		void setup(){
			_camera.setup();
			_vision.setup(&_camera);
		}
	
		void update(){
			_camera.update();
			_vision.update(&_camera);
		}
	
		void draw(){
			_camera.draw();
			_vision.draw(&_camera);
		}
	
	private:
		ofx::danca::Camera _camera;
		ofx::danca::Vision _vision;
};