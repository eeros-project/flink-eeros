#include <AnalogOut.hpp>

using namespace flink;
using namespace eeros::hal;

AnalogOut::AnalogOut(std::string id, std::string device, uint8_t subDeviceNumber, uint32_t channel, double scale, double offset) : ScalablePeripheralOutput<double>(id, scale, offset), channel(channel), bitMask(0) {
	flink_dev *devHandle = FlinkDevice::getDeviceHandle(device);
	this->subdeviceHandle = flink_get_subdevice_by_id(devHandle, subDeviceNumber);

	flink_analog_out_get_resolution(subdeviceHandle, &resolution);
	bitMask = (1 << resolution) - 1;
	
	this->scale = scale;
	this->offset = offset;
}

double AnalogOut::get() {
	// TODO
	return 0;
}

//TODO needed?
/*void AnalogOut::setValue(uint32_t value) {
	value &= bitMask;
	flink_analog_out_set_value(subdeviceHandle, channel, value);
}*/

void AnalogOut::set(double voltage) {
	uint32_t value = static_cast<uint32_t>((voltage - offset)/scale);
	setValue(value);
}

extern "C"{
	eeros::hal::ScalablePeripheralOutput<double> *createAnalgOut(std::string id, std::string device, uint32_t subDeviceNumber, uint32_t channel, double scale, double offset){
		return new flink::AnalogOut(id, device, subDeviceNumber, channel, scale, offset);
	}
}


