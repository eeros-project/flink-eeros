#include <DigOut.hpp>
#include <iostream>

//using namespace flink::eeros;
using namespace flink;
using namespace eeros::hal;

DigOut::DigOut(std::string id, std::string device, uint32_t subDeviceNumber, uint32_t channel, bool inverted): Output<bool>(id) ,channel(channel), inverted(inverted){
	FlinkDevice *dev = FlinkDevice::getDevice(device);
	std::cout << "subdev " << subDeviceNumber << " channel " << channel << std::endl;
	this->subdeviceHandle = flink_get_subdevice_by_id(dev->getDeviceHandle(), subDeviceNumber);
	std::cout << "here2" << std::endl;
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

extern "C" eeros::hal::Output<bool> *createDigOut(std::string id, std::string device, uint32_t subDeviceNumber, uint32_t channel, bool inverted){
	printf("create device");
	return new flink::DigOut(id, device, subDeviceNumber, channel, inverted);
}