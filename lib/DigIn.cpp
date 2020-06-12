#include "../include/DigIn.hpp"
#include <eeros/core/Fault.hpp>

using namespace flink;
using namespace eeros::hal;
using namespace eeros;

DigIn::DigIn(std::string id, void* libHandle, std::string device, uint32_t subDeviceNumber, uint32_t channel, bool inverted): 
				Input<bool>(id, libHandle) ,channel(channel), inverted(inverted){
	FlinkDevice *dev = FlinkDevice::getDevice(device);
	this->subdeviceHandle = flink_get_subdevice_by_id(dev->getDeviceHandle(), subDeviceNumber);
	uint16_t function = flink_subdevice_get_function(subdeviceHandle);
	if (function != GPIO_INTERFACE_ID) throw Fault("flink invalid subdevice number " + std::to_string(subDeviceNumber) + ", not a GPIO subdevice");
	if (channel < 0 || channel >= flink_subdevice_get_nofchannels(subdeviceHandle)) throw Fault("flink GPIO subdevice, invalid channel number " + std::to_string(channel));
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

extern "C" eeros::hal::Input<bool> *createDigIn(std::string id, void* libHandle, std::string device, uint32_t subDeviceNumber, uint32_t channel, bool inverted){
	return new flink::DigIn(id, libHandle, device, subDeviceNumber, channel, inverted);
}