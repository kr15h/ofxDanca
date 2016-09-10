#pragma once

#include "ofMain.h"
#include "SharedData.h"

namespace ofx {
namespace danca {

class Interface {
	public:
		Interface(Vision * v){
			_vision = v;
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
			ofScale((float)ofGetWidth() / (float)SharedData::instance()->cameraWidth,
				(float)ofGetHeight() / (float)SharedData::instance()->cameraHeight);
			
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
		Vision * _vision;
};

} // namespace danca
} // namespace ofx