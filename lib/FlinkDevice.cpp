#include <FlinkDevice.hpp>
#include <eeros/core/EEROSException.hpp>

using namespace flink;

FlinkDevice::FlinkDevice(std::string deviceNode) {
	it = flink_open(deviceNode.c_str());
	if(!it) {
		throw eeros::EEROSException("Can't open device \"" +  deviceNode + "\"!");
	}
}

FlinkDevice::~FlinkDevice() {
	flink_close(it);
}

flink_dev* FlinkDevice::getDeviceHandle() {
	return it;
}

extern "C" FlinkDevice *createFlinkDevice(std::string deviceNode){
	return new flink::FlinkDevice(deviceNode);
}