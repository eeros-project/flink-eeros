#ifndef FLINKEEROS_DIGIN_HPP_
#define FLINKEEROS_DIGIN_HPP_

#include <string>
#include <flinklib.h>
#include <eeros/hal/PeripheralInput.hpp>
#include <FlinkDevice.hpp>

extern "C"{
	eeros::hal::PeripheralInput<bool> *createDigIn(std::string id, std::string device, uint32_t subDeviceNumber, uint32_t channel, bool inverted);
}

namespace flink{
//	namespace eeros{
		class DigIn : public eeros::hal::PeripheralInput<bool> {
		public:
			DigIn(std::string id, std::string device, uint32_t subDeviceNumber, uint32_t channel, bool inverted = false);
			virtual bool get();
		private:
			flink_subdev* subdeviceHandle;
			uint32_t channel;
			bool inverted;
		};
//	};	
};

#endif /* FLINKEEROS_DIGIN_HPP_ */