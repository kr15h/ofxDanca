#pragma once

#include "SharedData.h"
#include "ofxCv.h"
#include "Camera.h"

namespace ofx {
namespace danca {

class Vision {
    public:
        Vision(Camera * c){
			_camera = c;
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
			ofScale((float)ofGetWidth() / (float)SharedData::instance()->cameraWidth,
				(float)ofGetHeight() / (float)SharedData::instance()->cameraHeight);
			
			_contourFinder.draw();
			
			ofPopMatrix();
		}
	
		ofxCv::ContourFinder & getContourFinder(){
			return _contourFinder;
		}
	
	private:
		Camera * _camera;
		ofxCv::ContourFinder _contourFinder;
};

} // namespace danca
} // namespace ofx