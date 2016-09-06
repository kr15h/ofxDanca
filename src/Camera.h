#pragma once

#ifdef TARGET_RASPBERRY_PI
	#include "ofxCvPiCam.h"
#else
	#include "ofVideoGrabber.h"
#endif

#include "ofxCv.h"

namespace ofx {
namespace danca {

class Camera {
    public:
        Camera(){
			_width = 480;
			_height = 360;
		}
    
        void setup(){
			#ifdef TARGET_RASPBERRY_PI
				_camera.setup(_width, _height, false);
			#else
				_camera.setDeviceID(0);
				_camera.setDesiredFrameRate(60);
				_camera.initGrabber(_width, _height);
			#endif
		}
	
		void update(){
			#ifdef TARGET_RASPBERRY_PI
				if(settings->rotateCamera){
					_camera.setRotation(180);
				}else{
					_camera.setRotation(0);
				}
				_frame = _camera.grab();
			#else
				_camera.update();
				ofPixels p = _camera.getPixels();
				_frame = ofxCv::toCv(p);
			#endif
		}
	
		void draw(){
			ofxCv::drawMat(_frame, 0, 0, ofGetWidth(), ofGetHeight());
		}
	
		int getWidth(){
			return _width;
		}
	
		int getHeight(){
			return _height;
		}
	
		cv::Mat & getFrame(){
			return _frame;
		}
	
	private:
		int _width;
		int _height;
	
		#ifdef TARGET_RASPBERRY_PI
            ofxCvPiCam _camera;
        #else
            ofVideoGrabber _camera;
        #endif
	
		cv::Mat _frame;
};

} // namespace danca
} // namespace ofx