#pragma once

#include "SharedData.h"
#include "ofxCv.h"
#include "Camera.h"

namespace ofx {
namespace danca {

class Vision {
    public:
        Vision(Camera * c, shared_ptr<SharedData> sd){
			_camera = c;
			_sharedData = sd;
		}
    
        void setup(){
			_contourFinder.setMinAreaRadius(10);
			_contourFinder.setMaxAreaRadius(50000);
			//_contourFinder.setThreshold(50);
			_contourFinder.setInvert(false);
			_contourFinder.setSimplify(true);
			
			_contourFinder.setSortBySize(true);
			_contourFinder.setAutoThreshold(true);
			_contourFinder.setFindHoles(false);
		}
	
		void update(){
			if(_camera->getFrame().empty()){
				return;
			}
			_contourFinder.findContours(_camera->getFrame());
		}
	
		void draw(){
			if(_contourFinder.size() <= 0){
				return;
			}
			
			ofPushMatrix();
			ofScale((float)ofGetWidth() / (float)_sharedData.get()->cameraWidth,
				(float)ofGetHeight() / (float)_sharedData.get()->cameraHeight);
			
			_contourFinder.draw();
			
			ofPopMatrix();
		}
	
		ofxCv::ContourFinder & getContourFinder(){
			return _contourFinder;
		}
	
	private:
		shared_ptr<SharedData> _sharedData;
		Camera * _camera;
		ofxCv::ContourFinder _contourFinder;
};

} // namespace danca
} // namespace ofx