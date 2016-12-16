#include <Pwm.hpp>

using namespace flink;
using namespace eeros::hal;

Pwm::Pwm(std::string id,
				   std::string device,
				   uint32_t subDeviceNumber,
				   uint32_t channel,
				   double scale,
				   double offset,
				   double rangeMin,
				   double rangeMax,
				   std::string unit
	) : ScalableOutput<double>(id, scale, offset, rangeMin, rangeMax, unit), channel(channel) {
	  
	FlinkDevice *dev = FlinkDevice::getDevice(device);
	this -> subdeviceHandle = flink_get_subdevice_by_id(dev->getDeviceHandle(), subDeviceNumber);
	flink_pwm_get_baseclock(subdeviceHandle, &baseFrequency);
}

double Pwm::get() {
	// TODO
	return 0;
}

void Pwm::set(double dutyCycle) {
	setDutyCycle(dutyCycle);
}

void Pwm::setFrequency(double f) {
	pwmFrequency = f;
	flink_pwm_set_period(subdeviceHandle, channel, (uint32_t)(baseFrequency / pwmFrequency));
}

void Pwm::setDutyCycle(double d) {
	if(d >= 0 && d <= 1) {
		flink_pwm_set_hightime(subdeviceHandle, channel, (uint32_t)(baseFrequency / pwmFrequency * d));
	}
}

extern "C"{
	eeros::hal::ScalableOutput<double> *createPwm(std::string id, std::string device, uint32_t subDeviceNumber, uint32_t channel, double scale, double offset, double rangeMin, double rangeMax, std::string unit){
		return new flink::Pwm(id, device, subDeviceNumber, channel, scale, offset, rangeMin, rangeMax, unit);
	}
}