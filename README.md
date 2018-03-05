# CxxZookeeper
## C++ version of Zookeeper



chinese version: [简体中文](README.zh_cn.md)



### Table of Contents
- [Characteristics](#characteristics)
- [Compare](#Compare)
- [Dependency](#dependency)
- [Support](#support)

#### Characteristics
* Compatibility: Fully compatible with java version zookeeper;
* Cross platform: support Linux32/64, OSX64, Win64 platforms;

#### Compare
* Performance: At no further optimization, the performance of the released c++ version of ZK is close to the Java version, and the data obtained by the zk-latencies.py test are basically the same.
* Memory use: The c++ version of ZK has an obvious advantage, with a less than one order of magnitude than the Java version, and no GC.
* See more testing report in the future.

#### Dependency
1. [CxxJDK](https://github.com/cxxjava/CxxJDK)
2. [CxxLog4j](https://github.com/cxxjava/CxxLog4j)

#### Support
Email: [cxxjava@163.com](mailto:cxxjava@163.com)