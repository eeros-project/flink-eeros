#include <DigIn.hpp>
#include <iostream>

//using namespace flink::eeros;
using namespace flink;
using namespace eeros::hal;

DigIn::DigIn(std::string id, std::string device, uint32_t subDeviceNumber, uint32_t channel, bool inverted): PeripheralInput<bool>(id) ,channel(channel), inverted(inverted){
	FlinkDevice *devHandle = FlinkDevice::getDevice(device);
	this->subdeviceHandle = flink_get_subdevice_by_id(devHandle->getDeviceHandle(), subDeviceNumber);
	
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

extern "C" eeros::hal::PeripheralInput<bool> *createDigIn(std::string id, std::string device, uint32_t subDeviceNumber, uint32_t channel, bool inverted){
	printf("create device");
	return new flink::DigIn(id, device, subDeviceNumber, channel, inverted);
}