#include <Fqd.hpp>

using namespace flink;
using namespace eeros::hal;

Fqd::Fqd(std::string id, 
					 std::string device,
					 uint32_t subDeviceNumber,
					 uint32_t channel,
					 double scale,
					 double offset,
					 double rangeMin,
					 double rangeMax,
					 std::string unit,
					 bool getDelta) : 
	ScalableInput<double>(id, scale, offset, rangeMin, rangeMax, unit), channel(channel), prevPos(0), getDelta(getDelta)
{
	FlinkDevice *dev = FlinkDevice::getDevice(device);
	this->subdeviceHandle = flink_get_subdevice_by_id(dev->getDeviceHandle(), subDeviceNumber);
	reset();
}

double Fqd::get() {
	uint32_t data = 0;
	flink_counter_get_count(subdeviceHandle, channel, &data);
	int16_t newPos = static_cast<uint16_t>(data);
	int16_t deltaPos = newPos - prevPos;
	prevPos = newPos;
	double delta = deltaPos / scale + offset;
	pos += delta;
	
	if (getDelta)
		return delta;
	else
		return pos;
}

void Fqd::reset() {
	flink_subdevice_reset(subdeviceHandle); // TODO only reset counter, not the subdevice!
	pos = 0;
}

extern "C"{
	eeros::hal::ScalableInput<double> *createFqd(std::string id, std::string device, uint32_t subDeviceNumber, uint32_t channel, double scale, double offset, double rangeMin, double rangeMax, std::string unit, bool getDelta){
		return new flink::Fqd(id, device, subDeviceNumber, channel, scale, offset, rangeMin, rangeMax, unit, getDelta);
	}
	
	void resetFqd(flink::Fqd *obj){
		obj->reset();
	}
}
