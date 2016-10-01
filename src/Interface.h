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
			
			// Collect momentary acceleration values of all edges
			AccelEntry entryTop;
			entryTop.time = ofGetElapsedTimef();
			entryTop.acceleration =
				(float)_rect.y - (float)_prevRect.y;
			_accelTopCollection.push_back(entryTop);
			
			AccelEntry entryRight;
			entryRight.time = ofGetElapsedTimef();
			entryRight.acceleration =
				(float)(_rect.x + _rect.width) -
				(float)(_prevRect.x + _prevRect.width);
			_accelRightCollection.push_back(entryRight);
			
			AccelEntry entryBottom;
			entryBottom.time = ofGetElapsedTimef();
			entryBottom.acceleration =
				(float)(_rect.y + _rect.height) -
				(float)(_prevRect.y + _prevRect.height);
			_accelBottomCollection.push_back(entryBottom);
			
			AccelEntry entryLeft;
			entryLeft.time = ofGetElapsedTimef();
			entryLeft.acceleration =
				(float)_rect.x - (float)_prevRect.x;
			_accelLeftCollection.push_back(entryLeft);
			
			// Calculate actual acceleration values as pixels per second for each of the edges
			float sumTop = 0.0f;
			unsigned int numSamplesTop = 0;
			for(unsigned int i = 0; i < _accelTopCollection.size(); ++i){
				if(_accelTopCollection[i].time + 1.0f >= ofGetElapsedTimef()){
					sumTop += _accelTopCollection[i].acceleration;
					numSamplesTop += 1;
				}
			}
			_accelerationTop = sumTop / (float)numSamplesTop;
			
			float sumRight = 0.0f;
			unsigned int numSamplesRight = 0;
			for(unsigned int i = 0; i < _accelRightCollection.size(); ++i){
				if(_accelRightCollection[i].time + 1.0f >= ofGetElapsedTimef()){
					sumRight += _accelRightCollection[i].acceleration;
					numSamplesRight += 1;
				}
			}
			_accelerationRight = sumRight / (float)numSamplesRight;
			
			float sumBottom = 0.0f;
			unsigned int numSamplesBottom = 0;
			for(unsigned int i = 0; i < _accelBottomCollection.size(); ++i){
				if(_accelBottomCollection[i].time + 1.0f >= ofGetElapsedTimef()){
					sumBottom += _accelBottomCollection[i].acceleration;
					numSamplesBottom += 1;
				}
			}
			_accelerationBottom = sumBottom / (float)numSamplesBottom;
			
			float sumLeft = 0.0f;
			unsigned int numSamplesLeft = 0;
			for(unsigned int i = 0; i < _accelLeftCollection.size(); ++i){
				if(_accelLeftCollection[i].time + 1.0f >= ofGetElapsedTimef()){
					sumLeft += _accelLeftCollection[i].acceleration;
					numSamplesLeft += 1;
				}
			}
			_accelerationLeft = sumLeft / (float)numSamplesLeft;
			
			// Clean up vectors from values that we don't need anymore
			for(unsigned int i = 0; i < _accelTopCollection.size(); ++i){
				if(_accelTopCollection[i].time + 1.0f < ofGetElapsedTimef()){
					_accelTopCollection.erase(_accelTopCollection.begin() + i);
					if(i > 0){
						--i;
					}
				}
			}
			
			for(unsigned int i = 0; i < _accelRightCollection.size(); ++i){
				if(_accelRightCollection[i].time + 1.0f < ofGetElapsedTimef()){
					_accelRightCollection.erase(_accelRightCollection.begin() + i);
					if(i > 0){
						--i;
					}
				}
			}
			
			for(unsigned int i = 0; i < _accelBottomCollection.size(); ++i){
				if(_accelBottomCollection[i].time + 1.0f < ofGetElapsedTimef()){
					_accelBottomCollection.erase(_accelBottomCollection.begin() + i);
					if(i > 0){
						--i;
					}
				}
			}
			
			for(unsigned int i = 0; i < _accelLeftCollection.size(); ++i){
				if(_accelLeftCollection[i].time + 1.0f < ofGetElapsedTimef()){
					_accelLeftCollection.erase(_accelLeftCollection.begin() + i);
					if(i > 0){
						--i;
					}
				}
			}
			
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
			
			// Debug vectors
			stringstream ss;
			ss << "top samples: " << _accelTopCollection.size() << "\n" <<
				"right samples: " << _accelRightCollection.size() << "\n" <<
				"bottom samples: " << _accelBottomCollection.size() << "\n" <<
				"left samples: " << _accelLeftCollection.size() << "\n";
			ofDrawBitmapString(ss.str(), 10, 20);
		}
	
		struct AccelEntry {
			float time;
			float acceleration;
		};
	
	private:
		shared_ptr<SharedData> _sharedData;
		Vision * _vision;
		cv::Rect _rect; // The rectangle being tracked and measured
		cv::Rect _prevRect;
	
		vector <AccelEntry> _accelTopCollection;
		vector <AccelEntry> _accelRightCollection;
		vector <AccelEntry> _accelBottomCollection;
		vector <AccelEntry> _accelLeftCollection;
	
		float _accelerationTop;
		float _accelerationRight;
		float _accelerationBottom;
		float _accelerationLeft;
};

} // namespace danca
} // namespace ofx