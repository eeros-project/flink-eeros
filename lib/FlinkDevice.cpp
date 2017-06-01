#include "../include/FlinkDevice.hpp"
#include <eeros/core/Fault.hpp>
#include <iostream>

using namespace flink;

std::map<std::string, FlinkDevice *> FlinkDevice::devices;

FlinkDevice::FlinkDevice(std::string deviceNode) {
	auto devIt = devices.find(deviceNode);
	if(devIt != devices.end()){
		throw new eeros::Fault("device already open, claim already opened device via getDevice()");
	}
	it = flink_open(deviceNode.c_str());
	if(!it) {
		throw eeros::Fault("Can't open device \"" +  deviceNode + "\"!");
	}
	devices[deviceNode] = this;
}

FlinkDevice::~FlinkDevice() {
	flink_close(it);
	devices.clear();
}

flink_dev* FlinkDevice::getDeviceHandle() {
	return it;
}

FlinkDevice* FlinkDevice::getDevice(std::string deviceNode) {
	auto devIt = devices.find(deviceNode);
	if(devIt != devices.end()){
		return devIt->second;
	}
	else{
		return new FlinkDevice(deviceNode);
	}
}
