#ifndef FLINK_EEROS_WATCHDOG_HPP_
#define FLINK_EEROS_WATCHDOG_HPP_

#include <string>
#include <flinklib.h>
#include <eeros/hal/Output.hpp>
#include <FlinkDevice.hpp>

namespace flink {
	class Watchdog : public eeros::hal::Output<bool> {
	public:
		Watchdog(std::string id, void *libHandle, std::string device, uint32_t subDeviceNumber, uint32_t channel, double timeout = 0.05);
		
		virtual bool get();
		virtual void set(bool b);
		virtual void setTimeout(double t);
		virtual void reset();
		
	private:
		flink_subdev* subdeviceHandle;
		uint32_t channel;
		uint32_t baseClock;
		uint32_t counter;
	};
};

extern "C"{
	eeros::hal::Output<bool> *createWatchdog(std::string id, void* libHandle, std::string device, uint32_t subDeviceNumber, uint32_t channel, double timeout);
	void resetWatchdog(flink::Watchdog *obj);
	void setWatchdogTimeout(flink::Watchdog *obj, double t);
}

#endif /* FLINK_EEROS_WATCHDOG_HPP_ */
