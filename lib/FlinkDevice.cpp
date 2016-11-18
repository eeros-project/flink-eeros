#include <FlinkDevice.hpp>
#include <eeros/core/EEROSException.hpp>
#include <iostream>

using namespace flink;

std::map<std::string, FlinkDevice *> FlinkDevice::devices;

FlinkDevice::FlinkDevice(std::string deviceNode) {
	std::cout << "open device: " << deviceNode << std::endl;
	auto devIt = devices.find(deviceNode);
	if(devIt != devices.end()){
		throw new eeros::EEROSException("claim already opened device via getDevice()");
	}
	it = flink_open(deviceNode.c_str());
	if(!it) {
		throw eeros::EEROSException("Can't open device \"" +  deviceNode + "\"!");
	}
	std::cout << "open successful" << std::endl;
	devices[deviceNode] = this;
}

FlinkDevice::~FlinkDevice() {
	flink_close(it);
}

flink_dev* FlinkDevice::getDeviceHandle() {
	return it;
}

FlinkDevice* FlinkDevice::getDevice(std::string deviceNode) {
	auto devIt = devices.find(deviceNode);
	if(devIt != devices.end()){
		std::cout << "device found" << std::endl;
		return devIt->second;
	}
	else{
		std::cout << "create device" << std::endl;
		return new FlinkDevice(deviceNode);
// 		 getDeviceHandle(deviceNode);
	}
}
