#pragma once

namespace ofx {
namespace danca {

class SharedData {
	public:
		SharedData(){
			cameraWidth = 480;
			cameraHeight = 360;
			rotateCamera = false;
		}
	
		int cameraWidth;
		int cameraHeight;
		bool rotateCamera;
};

} // namespace danca
} // namespace ofx
