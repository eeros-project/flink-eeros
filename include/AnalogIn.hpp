#ifndef FLINK_EEROS_ANALOGIN_HPP_
#define FLINK_EEROS_ANALOGIN_HPP_

#include <string>
#include <flinklib.h>
#include <eeros/hal/ScalableInput.hpp>
#include "FlinkDevice.hpp"
#include <limits>

namespace flink{
	class AnalogIn : public eeros::hal::ScalableInput<double> {
	public:
		AnalogIn(std::string id, void* libHandle, std::string device, uint32_t subDeviceNumber, uint32_t channel, 
					double scale = 1, double offset = 0, 
					double rangeMin = std::numeric_limits<double>::min(), double rangeMax = std::numeric_limits<double>::max(), 
					std::string unit = "", bool twosComplement = false);
		virtual double get();
	private:
		flink_subdev* subdeviceHandle;
		uint32_t channel;
		bool twosComplement;
	};
};

extern "C"{
	eeros::hal::ScalableInput<double> *createAnalogIn(std::string id, void* libHandle, std::string device, uint32_t subDeviceNumber, uint32_t channel, 
							 double scale, double offset, double rangeMin, double rangeMax, std::string unit, bool twosComplement);
}

#endif /* FLINK_EEROS_ANALOGIN_HPP_ */