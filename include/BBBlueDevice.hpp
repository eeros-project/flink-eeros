#ifndef BBBLUE_EEROS_DEVICE_HPP_
#define BBBLUE_EEROS_DEVICE_HPP_

#include <string>
#include <map>
#include <flinklib.h>

namespace bbblue {
	class BBBlueDevice {
	public:
		BBBlueDevice(std::string deviceNode);
		virtual ~BBBlueDevice();
		
		flink_dev* getDeviceHandle();
		static BBBlueDevice* getDevice(std::string deviceNode);
// 		static flink_dev* getDeviceHandle(std::string deviceNode);

	private:
// 		flink_dev *it;
		static std::map<std::string, bbblue::BBBlueDevice *> devices;
	};
};

#endif /* BBBLUE_EEROS_DEVICE_HPP_ */
