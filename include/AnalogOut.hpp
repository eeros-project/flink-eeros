#ifndef FLINKEEROS_ANALOGOUT_HPP_
#define FLINKEEROS_ANALOGOUT_HPP_

#include <string>
#include <flinklib.h>
#include <eeros/hal/ScalablePeripheralOutput.hpp>
#include <FlinkDevice.hpp>

extern "C"{
	eeros::hal::ScalablePeripheralOutput<double> *createAnalgOut(std::string id, std::string device, uint32_t subDeviceNumber, uint32_t channel, double scale, double offset);
}

namespace flink{
//	namespace eeros{
		class AnalogOut : public eeros::hal::ScalablePeripheralOutput<double> {
		public:
			AnalogOut(std::string id, std::string device, uint32_t subDeviceNumber, uint32_t channel, double scale = 1, double offset = 0);
			virtual double get();
			virtual void set(double value);
		private:
			flink_subdev* subdeviceHandle;
			uint32_t channel;
			uint32_t bitMask;
			uint32_t resolution;
		};
//	};	
};

#endif /* FLINKEEROS_ANALOGOUT_HPP_ */