#ifndef FLINKEEROS_DEVICE_HPP_
#define FLINKEEROS_DEVICE_HPP_

#include <string>
#include <map>
#include <flinklib.h>

namespace flink {
	class FlinkDevice {
	public:
		FlinkDevice(std::string deviceNode);
		virtual ~FlinkDevice();
		
		flink_dev* getDeviceHandle();
		static flink_dev* getDeviceHandle(std::string deviceNode);

	private:
		flink_dev *it;
		static std::map<std::string, flink_dev *> devices;
	};
};

#endif /* FLINKEEROS_DEVICE_HPP_ */
