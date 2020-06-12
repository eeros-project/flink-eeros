#include "../include/Watchdog.hpp"
#include <eeros/core/Fault.hpp>

using namespace flink;
using namespace eeros::hal;
using namespace eeros;

Watchdog::Watchdog(std::string id, void *libHandle, std::string device, uint32_t subDeviceNumber, double timeout) : 
					Output<bool>(id, libHandle) {
	FlinkDevice *dev = FlinkDevice::getDevice(device);
	subdeviceHandle = flink_get_subdevice_by_id(dev->getDeviceHandle(), subDeviceNumber);
	uint16_t function = flink_subdevice_get_function(subdeviceHandle);
	if (function != WD_INTERFACE_ID) throw Fault("flink invalid subdevice number " + std::to_string(subDeviceNumber) + ", not a WD subdevice");
	flink_wd_get_baseclock(subdeviceHandle, &baseClock);
	setTimeout(timeout);
}

void Watchdog::set(bool b) {
	if (b)
		flink_wd_set_counter(subdeviceHandle, counter);
	else
		flink_wd_set_counter(subdeviceHandle, 0);
}

void Watchdog::setTimeout(double t) {
	counter = static_cast<uint32_t>(baseClock * t);
}

bool Watchdog::get() {
	uint8_t status;
	flink_wd_get_status(subdeviceHandle, &status);
	return static_cast<bool>(status);
}

void Watchdog::reset() {
	flink_wd_set_counter(subdeviceHandle, counter);
	flink_wd_arm(subdeviceHandle);
}

extern "C"{
	eeros::hal::Output<bool> *createWatchdog(std::string id, void* libHandle, std::string device, uint32_t subDeviceNumber, uint32_t channel, double timeout){
		return new flink::Watchdog(id, libHandle, device, subDeviceNumber, timeout);
	}
	
	void resetWatchdog(flink::Watchdog *obj){
		obj->reset();
	}
	
	void setWatchdogTimeout(flink::Watchdog *obj, double t){
		obj->setTimeout(t);
	}
}