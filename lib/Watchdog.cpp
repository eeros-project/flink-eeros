#include "../include/Watchdog.hpp"
#include <eeros/core/Fault.hpp>

using namespace flink;
using namespace eeros::hal;
using namespace eeros::logger;
using namespace eeros;

Watchdog::Watchdog(std::string id, void *libHandle, std::string device, uint32_t subDeviceNumber, double timeout) : 
					Input<bool>(id, libHandle), log(Logger::getLogger()) {
	FlinkDevice *dev = FlinkDevice::getDevice(device);
	subdeviceHandle = flink_get_subdevice_by_id(dev->getDeviceHandle(), subDeviceNumber);
	uint16_t function = flink_subdevice_get_function(subdeviceHandle);
	if (function != WD_INTERFACE_ID) throw Fault("flink invalid subdevice number " + std::to_string(subDeviceNumber) + ", not a WD subdevice");
	flink_wd_get_baseclock(subdeviceHandle, &baseClock);
	setTimeout(timeout);
}

void Watchdog::reset() {
	flink_wd_set_counter(subdeviceHandle, counter);
}

void Watchdog::setTimeout(double t) {
	counter = static_cast<uint32_t>(baseClock * t);
}

bool Watchdog::get() {
	uint8_t status;
	flink_wd_get_status(subdeviceHandle, &status);
	return static_cast<bool>(status);
}

void Watchdog::arm() {
	log.warn() << "arming the watchdog";
	flink_wd_set_counter(subdeviceHandle, counter);
	flink_wd_arm(subdeviceHandle);
}

extern "C"{
	eeros::hal::Input<bool> *createWatchdog(std::string id, void* libHandle, std::string device, uint32_t subDeviceNumber, uint32_t channel, bool inverted, std::string timeout){
		return new flink::Watchdog(id, libHandle, device, subDeviceNumber, std::stod(timeout));
	}
	
	void reset(flink::Watchdog *obj){
		obj->reset();
	}

	void arm(flink::Watchdog *obj){
		obj->arm();
	}
	
	void setTimeout(flink::Watchdog *obj, double t){
		obj->setTimeout(t);
	}
}
