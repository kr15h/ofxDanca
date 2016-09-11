#pragma once

namespace ofx {
namespace danca {

class SharedData {
	public:
		SharedData(){
			cameraWidth = 480;
			cameraHeight = 360;
		}
	
		int cameraWidth;
		int cameraHeight;
};

} // namespace danca
} // namespace ofx