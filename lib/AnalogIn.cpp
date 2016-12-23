#include <AnalogIn.hpp>

using namespace flink;
using namespace eeros::hal;

AnalogIn::AnalogIn(std::string id, void* libHandle, std::string device, uint32_t subDeviceNumber, uint32_t channel, double scale, double offset, double rangeMin, double rangeMax, std::string unit, bool twosComplement) : ScalableInput<double>(id, libHandle, scale, offset, rangeMin, rangeMax, unit), channel(channel), bitMask(0) {
	// TODO untested!!
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
	//TODO untested!!
	uint32_t data;
	flink_analog_in_get_value(subdeviceHandle, channel, &data);
	data &= bitMask;
	if(twosComplement && (data >> (resolution - 1)) >= 1){ //negative number
		int32_t complementsData = -((~data&bitMask) + 1); //invert bitwise and add one
		if(complementsData > maxIn){
			complementsData = maxIn;	//TODO think: saturation bad choice on input?
		}
		if(complementsData < minIn){
			complementsData = minIn;
		}
		return complementsData  / scale / bitMask + offset;	//TODO test Analog in scale, was * scale before
	}else{
		if(data > maxIn){		//TODO think: saturation bad choice on input?
			data = maxIn;
		}
		if(data < minIn){
			data = minIn;
		}
		return data / scale / bitMask + offset;			//TODO test Analog in scale, was * scale before
	}
}

extern "C"{
	eeros::hal::ScalableInput<double> *createAnalgIn(std::string id, void* libHandle, std::string device, uint32_t subDeviceNumber, uint32_t channel, double scale, double offset, double rangeMin, double rangeMax, std::string unit, bool twosComplement){
		return new flink::AnalogIn(id, libHandle, device, subDeviceNumber, channel, scale, offset, rangeMin, rangeMax, unit, twosComplement);
	}
}