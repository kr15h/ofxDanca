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
			
			std::vector<cv::Point> points =
				_vision->getContourFinder().getConvexHull(0);
			ofPolyline polyline;
			
			for(unsigned int i = 0; i < points.size(); ++i){
				polyline.addVertex(points[i].x, points[i].y);
			}
			
			ofPushMatrix();
			ofScale((float)ofGetWidth() / (float)_sharedData.get()->cameraWidth,
				(float)ofGetHeight() / (float)_sharedData.get()->cameraHeight);
			
			ofPushStyle();
			ofSetLineWidth(3);
			ofSetColor(255, 255, 0);
			polyline.setClosed(true);
			polyline.draw();
			ofPopStyle();
			
			ofPushStyle();
			ofSetColor(255, 255, 0);
			for(unsigned int i = 0; i < points.size(); ++i){
				ofDrawCircle(points[i].x, points[i].y, 2);
			}
			ofPopStyle();
			
			ofPopMatrix();
		}
	private:
		shared_ptr<SharedData> _sharedData;
		Vision * _vision;
};

} // namespace danca
} // namespace ofx