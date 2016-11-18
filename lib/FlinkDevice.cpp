#include <FlinkDevice.hpp>
#include <eeros/core/EEROSException.hpp>

using namespace flink;

std::map<std::string, flink_dev *> FlinkDevice::devices;

FlinkDevice::FlinkDevice(std::string deviceNode) {
	it = flink_open(deviceNode.c_str());
	if(!it) {
		throw eeros::EEROSException("Can't open device \"" +  deviceNode + "\"!");
	}
	devices[deviceNode] = it;
}

FlinkDevice::~FlinkDevice() {
	flink_close(it);
}

flink_dev* FlinkDevice::getDeviceHandle() {
	return it;
}

flink_dev* FlinkDevice::getDeviceHandle(std::string deviceNode) {
	auto devIt = devices.find(deviceNode);
	if(devIt != devices.end()){
		return devIt->second;
	}
	else{
		FlinkDevice dev = FlinkDevice(deviceNode);
		return dev.getDeviceHandle();
	}
}
