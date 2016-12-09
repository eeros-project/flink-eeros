#include <DigIn.hpp>
#include <iostream>

//using namespace flink::eeros;
using namespace flink;
using namespace eeros::hal;

DigIn::DigIn(std::string id, std::string device, uint32_t subDeviceNumber, uint32_t channel, bool inverted): Input<bool>(id) ,channel(channel), inverted(inverted){
	FlinkDevice *dev = FlinkDevice::getDevice(device);
	this->subdeviceHandle = flink_get_subdevice_by_id(dev->getDeviceHandle(), subDeviceNumber);
	
	flink_dio_set_direction(subdeviceHandle, channel, FLINK_INPUT);
}

bool DigIn::get(){
	uint8_t data = 0;
	bool value;
	flink_dio_get_value(subdeviceHandle, channel, &data);
	value = static_cast<bool>(data);
	if(inverted) value = !value;
	return value;
}

extern "C" eeros::hal::Input<bool> *createDigIn(std::string id, std::string device, uint32_t subDeviceNumber, uint32_t channel, bool inverted){
	return new flink::DigIn(id, device, subDeviceNumber, channel, inverted);
}