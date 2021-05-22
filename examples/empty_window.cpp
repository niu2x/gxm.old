#include <iostream>

#include <gxm/gxm.h>

namespace {

using base_app = gxm::main::app;
class my_app: public gxm::main::app {
public:
	virtual void setup() override {
		base_app::setup();
		std::cout << "my_app setup" << std::endl;
	}
};

};

GXM_MAIN(my_app);