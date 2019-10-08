#include "../include/Fqd.hpp"
#include <iostream>

using namespace flink;
using namespace eeros::hal;

Fqd::Fqd(std::string id, 
					 void* libHandle, 
					 std::string device,
					 uint32_t subDeviceNumber,
					 uint32_t channel,
					 double scale,
					 double offset,
					 double rangeMin,
					 double rangeMax,
					 std::string unit,
					 bool getDelta) : 
	ScalableInput<double>(id, libHandle, scale, offset, rangeMin, rangeMax, unit), channel(channel), prevPos(0), getDelta(getDelta) {
	FlinkDevice *dev = FlinkDevice::getDevice(device);
	this->subdeviceHandle = flink_get_subdevice_by_id(dev->getDeviceHandle(), subDeviceNumber);
	flink_subdevice_reset(subdeviceHandle);
	reset();
}

double Fqd::get() {
	uint32_t data = 0;
	flink_counter_get_count(subdeviceHandle, channel, &data);	// returns 16 bit value
	int16_t actPos = static_cast<uint16_t>(data);
	int16_t deltaPos = actPos - prevPos;
	prevPos = actPos;
	pos += deltaPos / scale + offset;
	return pos + zeroPos;
}

void Fqd::reset() {
	setPos(0);
}

void Fqd::setPos(double position) {
	pos = position;
	zeroPos = position - get(); 
}

extern "C"{
	eeros::hal::ScalableInput<double> *createFqd(std::string id, void* libHandle, std::string device, uint32_t subDeviceNumber, uint32_t channel, 
						     double scale, double offset, double rangeMin, double rangeMax, std::string unit) {
		return new flink::Fqd(id, libHandle, device, subDeviceNumber, channel, scale, offset, rangeMin, rangeMax, unit);
	}
	
	void resetFqd(flink::Fqd *obj) {
		obj->reset();
	}
	
	void setFqdPos(flink::Fqd *obj, double position) {
		obj->setPos(position);
	}
}
