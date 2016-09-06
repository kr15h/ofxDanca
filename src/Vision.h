#pragma once

#include "ofxCv.h"
#include "Camera.h"

namespace ofx {
namespace danca {

class Vision {
    public:
        Vision(){
		
		}
    
        void setup(Camera * c){
			_contourFinder.setMinAreaRadius(10);
			_contourFinder.setMaxAreaRadius(50000);
			_contourFinder.setThreshold(50);
			_contourFinder.setInvert(false);
			_contourFinder.setSimplify(true);
		}
	
		void update(Camera * c){
			if(!c->getFrame().empty()){
				_contourFinder.setSortBySize(true);
				_contourFinder.findContours(c->getFrame());
			}else{
				return;
			}
    
			if(_contourFinder.size() <= 0){
				return;
			}
		}
	
		void draw(Camera * c){
			ofPushMatrix();
			ofScale((float)ofGetWidth() / (float)c->getWidth(),
				(float)ofGetHeight() / (float)c->getHeight());
			_contourFinder.draw();
			ofPopMatrix();
		}
	
	private:
		ofxCv::ContourFinder _contourFinder;
};

} // namespace danca
} // namespace ofx