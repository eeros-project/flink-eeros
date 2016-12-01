#include <AnalogOut.hpp>

using namespace flink;
using namespace eeros::hal;

AnalogOut::AnalogOut(std::string id, std::string device, uint32_t subDeviceNumber, uint32_t channel, double scale, double offset, std::string unit) : ScalableOutput<double>(id, scale, offset, unit), channel(channel), bitMask(0) {
  
	FlinkDevice *dev = FlinkDevice::getDevice(device);
	this->subdeviceHandle = flink_get_subdevice_by_id(dev->getDeviceHandle(), subDeviceNumber);
	
	flink_analog_out_get_resolution(subdeviceHandle, &resolution);
	bitMask = (1 << resolution) - 1;
	
	this->scale = scale;
	this->offset = offset;
	this->unit = unit;
}

double AnalogOut::get() {
	// TODO
	return 0;
}

void AnalogOut::setValue(uint32_t value) {
	value &= bitMask;
	flink_analog_out_set_value(subdeviceHandle, channel, value);
}

void AnalogOut::set(double voltage) {
	uint32_t value = static_cast<uint32_t>((voltage - offset)/scale);
	setValue(value);
}

extern "C"{
	eeros::hal::ScalableOutput<double> *createAnalogOut(std::string id, std::string device, uint32_t subDeviceNumber, uint32_t channel, double scale, double offset, std::string unit){
		return new flink::AnalogOut(id, device, subDeviceNumber, channel, scale, offset, unit);
	}
}


