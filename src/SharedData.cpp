#include "SharedData.h"

namespace ofx {
namespace danca {

SharedData * SharedData::_instance = 0;

SharedData * SharedData::instance(){
	if(_instance == 0){
		_instance = new SharedData();
	}
	return _instance;
}

} // namespace danca
} // namespace ofx