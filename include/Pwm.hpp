#ifndef FLINK_EEROS_PWM_HPP_
#define FLINK_EEROS_PWM_HPP_

#include <string>
#include <flinklib.h>
#include <eeros/hal/ScalableOutput.hpp>
#include <FlinkDevice.hpp>
#include <limits>

namespace flink {
	class Pwm : public eeros::hal::ScalableOutput<double> {
	public:
	Pwm(std::string id, void* libHandle, std::string device, uint32_t subDeviceNumber, uint32_t channel, double scale = 1, double offset = 0, double rangeMin = std::numeric_limits<double>::min(), double rangeMax = std::numeric_limits<double>::max(), std::string unit = "");
		virtual double get();
		virtual void set(double dutyCycle);
		virtual void setFrequency(double f);
		virtual void setDutyCycle(double d);
		
	private:
		flink_subdev* subdeviceHandle;
		uint32_t channel;
		double pwmFrequency;
		uint32_t baseFrequency;
	};
};

extern "C"{
	eeros::hal::ScalableOutput<double> *createPwm(std::string id, void *libHandle, std::string device, uint32_t subDeviceNumber, uint32_t channel, double scale, double offset, double rangeMin, double rangeMax, std::string unit);
	void setPwmFrequency(flink::Pwm *obj, double f);
	void setPwmDutyCycle(flink::Pwm *obj, double d);
}

#endif /* FLINK_EEROS_PWM_HPP_ */
