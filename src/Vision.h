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
			//_contourFinder.setThreshold(50);
			_contourFinder.setInvert(false);
			_contourFinder.setSimplify(true);
			
			_contourFinder.setSortBySize(true);
			_contourFinder.setAutoThreshold(true);
			_contourFinder.setFindHoles(false);
		}
	
		void update(Camera * c){
			if(c->getFrame().empty()){
				return;
			}
		
			_contourFinder.findContours(c->getFrame());
		}
	
		void draw(Camera * c){
			if(_contourFinder.size() <= 0){
				return;
			}
			
			ofPushMatrix();
			ofScale((float)ofGetWidth() / (float)c->getWidth(),
				(float)ofGetHeight() / (float)c->getHeight());
			
			_contourFinder.draw();
			std::vector<cv::Point> points = _contourFinder.getConvexHull(0);
			
			ofPolyline polyline;
			
			for(unsigned int i = 0; i < points.size(); ++i){
				polyline.addVertex(points[i].x, points[i].y);
			}
			
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
		ofxCv::ContourFinder _contourFinder;
};

} // namespace danca
} // namespace ofx