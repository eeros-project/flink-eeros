# flinkeeros
Wrapper library for [EEROS Robotics Framework](https://github.com/eeros-project/eeros-framework) to be used with [flink](https://github.com/flink-project).
The flink-eeros wrapper library enables the usage of flink hardware with the [EEROS Robotics Framework](https://github.com/eeros-project/eeros-framework). 

## Documentation
- About flink: http://flink-project.ch/
- About the wrapper library: http://wiki.eeros.org/eeros_architecture/hal/hardware_libraries#flink
- How to install: http://wiki.eeros.org/getting_started/install_wrapper#flink

## Getting Started

The easiest way to get started using EEROS together with flink is described in [Installation and Setup](https://wiki.eeros.org/getting_started/install_and_setup_development_environment) and more specifically in [Use on a cb20 Board](https://wiki.eeros.org/getting_started/install_and_setup_development_environment/use_with_cb20).

The EEROS framework uses various [hardware libraries](http://wiki.eeros.org/eeros_architecture/hal/hardware_libraries) to access the underlying hardware. For the cb20 board [flink](http://flink-project.ch/) is used through this hardware wrapper library. 

The EEROS [Hardware Abstraction Layer](http://wiki.eeros.org/eeros_architecture/hal/start) needs a [configuration file](http://wiki.eeros.org/eeros_architecture/hal/configuration_file) which describes the hardware. A hardware configuration file describing all features in this hardware wrapper library can be found at (https://github.com/ntb-ch/cb20/tree/master/Software/cb20test). It is called *HwConfigCb20.json*.


## Projects using EEROS on the cb20 Board

### Simple Motor Controller
The EEROS tutorial encompasses an application demonstrating the control of a simple motor, see [EEROS Tutorial: Control a Single Motor](https://wiki.eeros.org/getting_started/tutorials/oneaxis).


## How to contribute to flink-eeros

The [EEROS Team](http://eeros.org/eeros-team/) would love to accept your contributions! The development on the EEROS Framework is done with the work flow “**develop with a fork**”. So please fork the repository, develop and test your code changes. For code quality, please follow the guidelines put together [here](http://wiki.eeros.org/for_developers/start). In general, the code should adheres to the existing style in the project. Once the changes are ready, a pull request is submitted. Each logical change should be submitted separately to ensure that the history will be understandable.
