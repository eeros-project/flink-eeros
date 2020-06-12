#include "../include/Fqd.hpp"
#include <eeros/core/Fault.hpp>

using namespace flink;
using namespace eeros::hal;
using namespace eeros;

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
	uint16_t function = flink_subdevice_get_function(subdeviceHandle);
	if (function != COUNTER_INTERFACE_ID) throw Fault("flink invalid subdevice number " + std::to_string(subDeviceNumber) + ", not a FQD subdevice");
	flink_subdevice_reset(subdeviceHandle);
	if (channel < 0 || channel >= flink_subdevice_get_nofchannels(subdeviceHandle)) throw Fault("flink FQD subdevice, invalid channel number " + std::to_string(channel));
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
