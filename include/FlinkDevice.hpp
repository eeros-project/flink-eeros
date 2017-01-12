#ifndef FLINK_EEROS_DEVICE_HPP_
#define FLINK_EEROS_DEVICE_HPP_

#include <string>
#include <map>
#include <flinklib.h>

namespace flink {
	class FlinkDevice {
	public:
		FlinkDevice(std::string deviceNode);
		virtual ~FlinkDevice();
		
		flink_dev* getDeviceHandle();
		static FlinkDevice* getDevice(std::string deviceNode);
// 		static flink_dev* getDeviceHandle(std::string deviceNode);

	private:
		flink_dev *it;
		static std::map<std::string, flink::FlinkDevice *> devices;
	};
};

#endif /* FLINK_EEROS_DEVICE_HPP_ */
