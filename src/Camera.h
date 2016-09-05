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
		
		}
    
        void setup(){
			int w = 480;
			int h = 360;

			#ifdef TARGET_RASPBERRY_PI
				_camera.setup(w, h, false);
			#else
				_camera.setDeviceID(0);
				_camera.setDesiredFrameRate(60);
				_camera.initGrabber(w, h);
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
	
	private:
		#ifdef TARGET_RASPBERRY_PI
            ofxCvPiCam _camera;
        #else
            ofVideoGrabber _camera;
        #endif
	
		cv::Mat _frame;
};

} // namespace danca
} // namespace ofx