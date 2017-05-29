#include "../include/BBBlueDevice.hpp"
#include <eeros/core/Fault.hpp>

using namespace bbblue;

std::map<std::string, BBBlueDevice *> BBBlueDevice::devices;

BBBlueDevice::BBBlueDevice(std::string deviceNode) {
// 	auto devIt = devices.find(deviceNode);
// 	if(devIt != devices.end()){
// 		throw new eeros::Fault("device already open, claim already opened device via getDevice()");
// 	}
// 	it = flink_open(deviceNode.c_str());
// 	if(!it) {
// 		throw eeros::Fault("Can't open device \"" +  deviceNode + "\"!");
// 	}
	devices[deviceNode] = this;
}

BBBlueDevice::~BBBlueDevice() {
// 	flink_close(it);
	devices.clear();
}

// flink_dev* BBBlueDevice::getDeviceHandle() {
// 	return it;
// }

BBBlueDevice* BBBlueDevice::getDevice(std::string deviceNode) {
	auto devIt = devices.find(deviceNode);
	if(devIt != devices.end()){
		return devIt->second;
	}
	else{
		return new BBBlueDevice(deviceNode);
	}
}
