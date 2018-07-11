#include "../include/AnalogOut.hpp"
#include <iostream>

using namespace flink;

AnalogOut::AnalogOut(std::string id, void* libHandle, std::string device, uint32_t subDeviceNumber, uint32_t channel, 
		     double scale, double offset, double rangeMin, double rangeMax, std::string unit) : 
		     ScalableOutput<double>(id, libHandle, scale, offset, rangeMin, rangeMax, unit), channel(channel), bitMask(0) {
  
	FlinkDevice *dev = FlinkDevice::getDevice(device);
	this->subdeviceHandle = flink_get_subdevice_by_id(dev->getDeviceHandle(), subDeviceNumber);
	
	flink_analog_out_get_resolution(subdeviceHandle, &resolution);
	bitMask = (1 << resolution) - 1;
	
	this->scale = scale;
	this->offset = offset;
	this->minOut = rangeMin;
	this->maxOut = rangeMax;
	this->unit = unit;
}

double AnalogOut::get() {
	return value;
}

void AnalogOut::set(double outValue) {
	this->value = outValue;
	uint32_t val = static_cast<uint32_t>((outValue - offset)/scale);
	val &= bitMask;
	// check range
	if( val > maxOut ) val = maxOut;
	if( val < minOut ) val = minOut;
	flink_analog_out_set_value(subdeviceHandle, channel, val);
}

extern "C"{
	eeros::hal::ScalableOutput<double> *createAnalogOut(std::string id, void *libHandle, std::string device, uint32_t subDeviceNumber, 
							    uint32_t channel, double scale, double offset, double rangeMin, double rangeMax, std::string unit){
		return new flink::AnalogOut(id, libHandle, device, subDeviceNumber, channel, scale, offset, rangeMin, rangeMax, unit);
	}
}


