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

	private:
		flink_dev *it;
	};
};

extern "C"{
	flink::FlinkDevice *createFlinkDevice(std::string deviceNode);
}

#endif /* FLINKEEROS_DEVICE_HPP_ */
