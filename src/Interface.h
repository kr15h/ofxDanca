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
			if(_vision->getContourFinder().size() <= 0){
				return;
			}
		
			_rect = _vision->getContourFinder().getBoundingRect(0);
			
			// TODO: Transform it to format pixels/sec ?
			_accelerationTop =
				(float)_rect.y - (float)_prevRect.y;
			_accelerationRight =
				(float)(_rect.x + _rect.width) -
				(float)(_prevRect.x + _prevRect.width);
			_accelerationBottom =
				(float)(_rect.y + _rect.height) -
				(float)(_prevRect.y + _prevRect.height);
			_accelerationLeft =
				(float)_rect.x - (float)_prevRect.x;
			
			_prevRect = _rect;
		}
	
		void draw(){
			ofPushMatrix();
			ofScale((float)ofGetWidth() / (float)_sharedData.get()->cameraWidth,
				(float)ofGetHeight() / (float)_sharedData.get()->cameraHeight);
			
			ofPushStyle();
			ofSetLineWidth(3);
			ofNoFill();
			ofSetColor(255, 255, 0);
			
			// Draw rectangle
			ofDrawRectangle(_rect.x, _rect.y, _rect.width, _rect.height);
			
			// Draw acceleration values
			ofFill();
			
			// Top
			ofDrawBitmapStringHighlight(ofToString(_accelerationTop),
				(float)_rect.x + (float)_rect.width / 2.0f,
				(float)_rect.y + 20);
			
			// Right
			ofDrawBitmapStringHighlight(ofToString(_accelerationRight),
				_rect.x + _rect.width + 10,
				((float)_rect.y + (float)_rect.height / 2.0f));
			
			// Bottom
			ofDrawBitmapStringHighlight(ofToString(_accelerationBottom),
				(float)_rect.x + (float)_rect.width / 2.0f,
				_rect.y + _rect.height - 10);
			
			// Left
			ofDrawBitmapStringHighlight(ofToString(_accelerationLeft),
				_rect.x + 10,
				((float)_rect.y + (float)_rect.height / 2.0f));
			
			ofPopStyle();
			
			ofPopMatrix();
		}
	private:
		shared_ptr<SharedData> _sharedData;
		Vision * _vision;
		cv::Rect _rect; // The rectangle being tracked and measured
		cv::Rect _prevRect;
	
		float _accelerationTop;
		float _accelerationRight;
		float _accelerationBottom;
		float _accelerationLeft;
};

} // namespace danca
} // namespace ofx