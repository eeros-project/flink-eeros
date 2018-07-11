#include "../include/AnalogIn.hpp"

using namespace flink;

AnalogIn::AnalogIn(std::string id, void* libHandle, std::string device, uint32_t subDeviceNumber, uint32_t channel, 
		   double scale, double offset, double rangeMin, double rangeMax, std::string unit, bool twosComplement) : 
		   ScalableInput<double>(id, libHandle, scale, offset, rangeMin, rangeMax, unit), channel(channel), bitMask(0) {

	FlinkDevice *dev = FlinkDevice::getDevice(device);
	this->subdeviceHandle = flink_get_subdevice_by_id(dev->getDeviceHandle(), subDeviceNumber);

	flink_analog_in_get_resolution(subdeviceHandle, &resolution);
	bitMask = (1 << resolution) - 1;
	
	this->scale = scale;
	this->offset = offset;
	this->minIn = rangeMin;
	this->maxIn = rangeMax;
	this->unit = unit;
	this->twosComplement = twosComplement;
}

double AnalogIn::get() {
	uint32_t data;
	flink_analog_in_get_value(subdeviceHandle, channel, &data);
	data &= bitMask;
	return (data - offset) / scale;
}

extern "C"{
	eeros::hal::ScalableInput<double> *createAnalogIn(std::string id, void* libHandle, std::string device, uint32_t subDeviceNumber, uint32_t channel, 
							 double scale, double offset, double rangeMin, double rangeMax, std::string unit, bool twosComplement){
		return new flink::AnalogIn(id, libHandle, device, subDeviceNumber, channel, scale, offset, rangeMin, rangeMax, unit, twosComplement);
	}
}