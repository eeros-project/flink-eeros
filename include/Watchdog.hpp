#ifndef FLINK_EEROS_WATCHDOG_HPP_
#define FLINK_EEROS_WATCHDOG_HPP_

#include <string>
#include <flinklib.h>
#include <eeros/hal/Input.hpp>
#include <eeros/logger/Logger.hpp>
#include "FlinkDevice.hpp"

namespace flink {
	class Watchdog : public eeros::hal::Input<bool> {
	public:
		Watchdog(std::string id, void *libHandle, std::string device, uint32_t subDeviceNumber, double timeout = 0.05);
		
		virtual bool get();
		virtual void setTimeout(double t);
		virtual void reset();
		virtual void arm();

	private:
		flink_subdev* subdeviceHandle;
		uint32_t baseClock;
		uint32_t counter;
		eeros::logger::Logger log;
	};
};

extern "C"{
	eeros::hal::Input<bool> *createWatchdog(std::string id, void* libHandle, std::string device, uint32_t subDeviceNumber, uint32_t channel, bool inverted, std::string timeout);
	void reset(flink::Watchdog *obj);
	void arm(flink::Watchdog *obj);
	void setTimeout(flink::Watchdog *obj, double t);
}

#endif /* FLINK_EEROS_WATCHDOG_HPP_ */
