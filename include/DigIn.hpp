#ifndef FLINKEEROS_DIGIN_HPP_
#define FLINKEEROS_DIGIN_HPP_

#include <string>
#include <flinklib.h>
#include <eeros/hal/Input.hpp>
#include <FlinkDevice.hpp>

extern "C"{
	eeros::hal::Input<bool> *createDigIn(std::string id, void* libHandle, std::string device, uint32_t subDeviceNumber, uint32_t channel, bool inverted);
}

namespace flink{
	class DigIn : public eeros::hal::Input<bool> {
	public:
		DigIn(std::string id, void* libHandle, std::string device, uint32_t subDeviceNumber, uint32_t channel, bool inverted = false);
		virtual bool get();
	private:
		flink_subdev* subdeviceHandle;
		uint32_t channel;
		bool inverted;
	};
};

#endif /* FLINKEEROS_DIGIN_HPP_ */