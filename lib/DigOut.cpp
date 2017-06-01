#include "../include/DigOut.hpp"
#include <iostream>

//using namespace flink::eeros;
using namespace flink;
using namespace eeros::hal;

DigOut::DigOut(std::string id, void *libHandle, std::string device, uint32_t subDeviceNumber, uint32_t channel, bool inverted): 
				Output<bool>(id, libHandle) ,channel(channel), inverted(inverted){
	FlinkDevice *dev = FlinkDevice::getDevice(device);
	this->subdeviceHandle = flink_get_subdevice_by_id(dev->getDeviceHandle(), subDeviceNumber);
	flink_dio_set_direction(subdeviceHandle, channel, FLINK_OUTPUT);
}

bool DigOut::get(){
	uint8_t data = 0;
	bool value;
	flink_dio_get_value(subdeviceHandle, channel, &data);
	value = static_cast<bool>(data);
	if(inverted) value = !value;
	return value;
}

void DigOut::set(bool value){
	if(inverted) value = !value;
	flink_dio_set_value(subdeviceHandle, channel, value);
}

extern "C" eeros::hal::Output<bool> *createDigOut(std::string id, void* libHandle, std::string device, uint32_t subDeviceNumber, uint32_t channel, bool inverted){
	return new flink::DigOut(id, libHandle, device, subDeviceNumber, channel, inverted);
}