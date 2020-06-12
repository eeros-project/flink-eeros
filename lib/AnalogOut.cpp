#include "../include/AnalogOut.hpp"
#include <eeros/core/Fault.hpp>

using namespace flink;
using namespace eeros::hal;
using namespace eeros;

AnalogOut::AnalogOut(std::string id, void* libHandle, std::string device, uint32_t subDeviceNumber, uint32_t channel, 
		     double scale, double offset, double rangeMin, double rangeMax, std::string unit) : 
		     ScalableOutput<double>(id, libHandle, scale, offset, rangeMin, rangeMax, unit), channel(channel), bitMask(0) {
  
	FlinkDevice *dev = FlinkDevice::getDevice(device);
	this->subdeviceHandle = flink_get_subdevice_by_id(dev->getDeviceHandle(), subDeviceNumber);
	uint16_t function = flink_subdevice_get_function(subdeviceHandle);
	if (function != ANALOG_OUTPUT_INTERFACE_ID) throw Fault("flink invalid subdevice number " + std::to_string(subDeviceNumber) + ", not a DAC subdevice");
	if (channel < 0 || channel >= flink_subdevice_get_nofchannels(subdeviceHandle)) throw Fault("flink DAC subdevice, invalid channel number " + std::to_string(channel));
	
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


