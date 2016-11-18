#ifndef FLINKEEROS_ANALOGIN_HPP_
#define FLINKEEROS_ANALOGIN_HPP_

#include <string>
#include <flinklib.h>
#include <eeros/hal/ScalablePeripheralInput.hpp>
#include <FlinkDevice.hpp>

extern "C"{
	eeros::hal::ScalablePeripheralInput<double> *createAnalgIn(std::string id, std::string device, uint32_t subDeviceNumber, uint32_t channel, double scale, double offset, bool twosComplement);
}

namespace flink{
//	namespace eeros{
		class AnalogIn : public eeros::hal::ScalablePeripheralInput<double> {
		public:
			AnalogIn(std::string id, std::string device, uint32_t subDeviceNumber, uint32_t channel, double scale = 1, double offset = 0, bool twosComplement = false);
			virtual double get();
		private:
			flink_subdev* subdeviceHandle;
			uint32_t channel;
			uint32_t bitMask;
			uint32_t resolution;
			bool twosComplement;
		};
//	};	
};

#endif /* FLINKEEROS_ANALOGIN_HPP_ */