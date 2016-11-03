#pragma once

#include "SharedData.h"
#include "ofxCv.h"

#ifdef TARGET_RASPBERRY_PI
	#include "ofxCvPiCam.h"
#else
	#include "ofVideoGrabber.h"
#endif

namespace ofx {
namespace danca {

class Camera {
    public:
        Camera(shared_ptr<SharedData> sd){
			_sharedData = sd;
		}
    
        void setup(){
			#ifdef TARGET_RASPBERRY_PI
				_camera.setup(
					_sharedData.get()->cameraWidth,
					_sharedData.get()->cameraHeight,
					false);
			#else
				_camera.setDeviceID(0);
				_camera.setDesiredFrameRate(60);
				_camera.initGrabber(
					_sharedData.get()->cameraWidth,
					_sharedData.get()->cameraHeight);
			#endif
		}
	
		void update(){
			#ifdef TARGET_RASPBERRY_PI
				if(_sharedData.get()->rotateCamera){
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
	
		cv::Mat & getFrame(){
			return _frame;
		}
	
	private:
		#ifdef TARGET_RASPBERRY_PI
            ofxCvPiCam _camera;
        #else
            ofVideoGrabber _camera;
        #endif
	
		cv::Mat _frame;
		shared_ptr<SharedData> _sharedData;
};

} // namespace danca
} // namespace ofx
