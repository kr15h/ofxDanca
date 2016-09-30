#pragma once

#include "ofMain.h"
#include "SharedData.h"

namespace ofx {
namespace danca {

class Interface {
	public:
		Interface(Vision * v, shared_ptr<SharedData> sd){
			_vision = v;
			_sharedData = sd;
		}
	
		void setup(){
		
		}
	
		void update(){
		
		}
	
		void draw(){
			if(_vision->getContourFinder().size() <= 0){
				return;
			}
			
			_rect = _vision->getContourFinder().getBoundingRect(0);
			
			ofPushMatrix();
			ofScale((float)ofGetWidth() / (float)_sharedData.get()->cameraWidth,
				(float)ofGetHeight() / (float)_sharedData.get()->cameraHeight);
			
			ofPushStyle();
			ofSetLineWidth(3);
			ofNoFill();
			ofSetColor(255, 255, 0);
			
			ofDrawRectangle(_rect.x, _rect.y, _rect.width, _rect.height);
			
			ofPopStyle();
			
			ofPopMatrix();
		}
	private:
		shared_ptr<SharedData> _sharedData;
		Vision * _vision;
		cv::Rect _rect; // The rectangle being tracked and measured
};

} // namespace danca
} // namespace ofx