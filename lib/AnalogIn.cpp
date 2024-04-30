#include "../include/AnalogIn.hpp"
#include <eeros/core/Fault.hpp>

using namespace flink;
using namespace eeros::hal;
using namespace eeros;

AnalogIn::AnalogIn(std::string id, void* libHandle, std::string device, uint32_t subDeviceNumber, uint32_t channel, 
		   double scale, double offset, double rangeMin, double rangeMax, std::string unit, bool twosComplement) : 
		   ScalableInput<double>(id, libHandle, scale, offset, rangeMin, rangeMax, unit), channel(channel) {

	FlinkDevice *dev = FlinkDevice::getDevice(device);
	this->subdeviceHandle = flink_get_subdevice_by_id(dev->getDeviceHandle(), subDeviceNumber);
	uint16_t function = flink_subdevice_get_function(subdeviceHandle);
	if (function != ANALOG_INPUT_INTERFACE_ID) throw Fault("flink invalid subdevice number " + std::to_string(subDeviceNumber) + ", not a ADC subdevice");
	if (channel < 0 || channel >= flink_subdevice_get_nofchannels(subdeviceHandle)) throw Fault("flink ADC subdevice, invalid channel number " + std::to_string(channel));
	
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
	return (data - offset) / scale;
}

extern "C"{
	eeros::hal::ScalableInput<double> *createAnalogIn(std::string id, void* libHandle, std::string device, uint32_t subDeviceNumber, uint32_t channel, 
							 double scale, double offset, double rangeMin, double rangeMax, std::string unit, bool twosComplement){
		return new flink::AnalogIn(id, libHandle, device, subDeviceNumber, channel, scale, offset, rangeMin, rangeMax, unit, twosComplement);
	}
}