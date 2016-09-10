#pragma once

namespace ofx {
namespace danca {

class SharedData {
	public:
		static SharedData * instance();
	
		int cameraWidth;
		int cameraHeight;
	
	private:
		static SharedData * _instance;
	
		SharedData(){
			cameraWidth = 480;
			cameraHeight = 360;
		}
};

} // namespace danca
} // namespace ofx