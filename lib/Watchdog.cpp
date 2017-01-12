#include <Watchdog.hpp>
using namespace flink;
using namespace eeros::hal;

Watchdog::Watchdog(std::string id, void *libHandle, std::string device, uint32_t subDeviceNumber, uint32_t channel, double timeout) : 
					Output<bool>(id, libHandle), channel(channel) {
	FlinkDevice *dev = FlinkDevice::getDevice(device);
	subdeviceHandle = flink_get_subdevice_by_id(dev->getDeviceHandle(), subDeviceNumber);
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
		return new flink::Watchdog(id, libHandle, device, subDeviceNumber, channel, timeout);
	}
	
	void resetWatchdog(flink::Watchdog *obj){
		obj->reset();
	}
	
	void setWatchdogTimeout(flink::Watchdog *obj, double t){
		obj->setTimeout(t);
	}
}