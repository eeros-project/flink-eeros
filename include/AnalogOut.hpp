#ifndef FLINKEEROS_ANALOGOUT_HPP_
#define FLINKEEROS_ANALOGOUT_HPP_

#include <string>
#include <flinklib.h>
#include <eeros/hal/ScalableOutput.hpp>
#include <FlinkDevice.hpp>
#include <limits>

extern "C"{
	eeros::hal::ScalableOutput<double> *createAnalogOut(std::string id, std::string device, uint32_t subDeviceNumber, uint32_t channel, double scale, double offset, double rangeMin, double rangeMax, std::string unit);
}

namespace flink{
//	namespace eeros{
		class AnalogOut : public eeros::hal::ScalableOutput<double> {
		public:
			AnalogOut(std::string id, std::string device, uint32_t subDeviceNumber, uint32_t channel, double scale = 1, double offset = 0, double rangeMin = std::numeric_limits<double>::min() , double rangeMax = std::numeric_limits<double>::max(), std::string unit = "");
			virtual double get();
			virtual void set(double value);
			virtual void setValue(uint32_t value);
		private:
			flink_subdev* subdeviceHandle;
			uint32_t channel;
			uint32_t bitMask;
			uint32_t resolution;
		};
//	};	
};

#endif /* FLINKEEROS_ANALOGOUT_HPP_ */