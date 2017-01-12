#ifndef FLINK_EEROS_DIGOUT_HPP_
#define FLINK_EEROS_DIGOUT_HPP_

#include <string>
#include <flinklib.h>
#include <eeros/hal/Output.hpp>
#include <FlinkDevice.hpp>

namespace flink{
	class DigOut : public eeros::hal::Output<bool> {
	public:
		DigOut(std::string id, void* libHandle, std::string device, uint32_t subDeviceNumber, uint32_t channel, bool inverted = false);
		virtual bool get();
		virtual void set(bool value);
	private:
		flink_subdev* subdeviceHandle;
		uint32_t channel;
		bool inverted;
	};
};

extern "C"{
	eeros::hal::Output<bool> *createDigOut(std::string id, void* libHandle, std::string device, uint32_t subDeviceNumber, uint32_t channel, bool inverted);
}

#endif /* FLINK_EEROS_DIGOUT_HPP_ */