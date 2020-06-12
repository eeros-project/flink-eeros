#include "../include/Pwm.hpp"
#include <eeros/core/Fault.hpp>

using namespace flink;
using namespace eeros::hal;
using namespace eeros;

Pwm::Pwm(std::string id,
				   void* libHandle,
				   std::string device,
				   uint32_t subDeviceNumber,
				   uint32_t channel,
				   double scale,
				   double offset,
				   double rangeMin,
				   double rangeMax,
				   std::string unit
	) : ScalableOutput<double>(id, libHandle, scale, offset, rangeMin, rangeMax, unit), channel(channel) {
	  
	FlinkDevice *dev = FlinkDevice::getDevice(device);
	subdeviceHandle = flink_get_subdevice_by_id(dev->getDeviceHandle(), subDeviceNumber);
	uint16_t function = flink_subdevice_get_function(subdeviceHandle);
	if (function != PWM_INTERFACE_ID) throw Fault("flink invalid subdevice number " + std::to_string(subDeviceNumber) + ", not a PWM subdevice");
	flink_pwm_get_baseclock(subdeviceHandle, &baseFrequency);
	if (channel < 0 || channel >= flink_subdevice_get_nofchannels(subdeviceHandle)) throw Fault("flink PWM subdevice, invalid channel number " + std::to_string(channel));
}

double Pwm::get() {
	uint32_t period, hightime;
	flink_pwm_get_period(subdeviceHandle, channel, &period);
	flink_pwm_get_hightime(subdeviceHandle, channel, &hightime);
	return (double)hightime / period;
}

void Pwm::set(double dutyCycle) {
	setDutyCycle(dutyCycle);
}

void Pwm::setFrequency(double f) {
	pwmFrequency = f;
	flink_pwm_set_period(subdeviceHandle, channel, (uint32_t)(baseFrequency / pwmFrequency));
}

void Pwm::setDutyCycle(double d) {
	if(d < 0.0) d = 0.0;
	if(d > 1.0) d = 1.0;
	flink_pwm_set_hightime(subdeviceHandle, channel, (uint32_t)(baseFrequency / pwmFrequency * d));
}

extern "C"{
	eeros::hal::ScalableOutput<double> *createPwm(std::string id, void *libHandle, std::string device, uint32_t subDeviceNumber, uint32_t channel, 
						      double scale, double offset, double rangeMin, double rangeMax, std::string unit){
		return new flink::Pwm(id, libHandle, device, subDeviceNumber, channel, scale, offset, rangeMin, rangeMax, unit);
	}
	
	void setPwmFrequency(Pwm *obj, double f){
		obj->setFrequency(f);
	}
	
	void setPwmDutyCycle(Pwm *obj, double d){
		obj->setDutyCycle(d);
	}
}