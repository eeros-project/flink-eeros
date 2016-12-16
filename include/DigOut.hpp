#ifndef FLINKEEROS_DIGOUT_HPP_
#define FLINKEEROS_DIGOUT_HPP_

#include <string>
#include <flinklib.h>
#include <eeros/hal/Output.hpp>
#include <FlinkDevice.hpp>

extern "C"{
	eeros::hal::Output<bool> *createDigOut(std::string id, std::string device, uint32_t subDeviceNumber, uint32_t channel, bool inverted);
}

namespace flink{
	class DigOut : public eeros::hal::Output<bool> {
	public:
		DigOut(std::string id, std::string device, uint32_t subDeviceNumber, uint32_t channel, bool inverted = false);
		virtual bool get();
		virtual void set(bool value);
	private:
		flink_subdev* subdeviceHandle;
		uint32_t channel;
		bool inverted;
	};
};

#endif /* FLINKEEROS_DIGOUT_HPP_ */