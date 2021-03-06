namespace Freeworld {
class CoreUtils;
}

#ifndef CORE_UTILS_HPP
#define CORE_UTILS_HPP

#include "src/mps-sp/instance.hpp"

namespace Freeworld {

class CoreUtils {
public:
	InstanceMpsSp* instance;
	CoreUtils(InstanceMpsSp* instance);
	~CoreUtils();
	void init();
	void quit();
};

} // end of namespace Freeworld

#endif // CORE_UTILS_HPP
