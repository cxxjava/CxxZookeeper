
# zookeeper的新选择--CxxZookeeper


### 概览
为了压榨性能极限，并使zk有更好的可预测性，且没有GC的打扰，我们在2个多月时间里将java版zk使用c++语言进行了完整翻译，并最终推出CxxZookeeper这个开源产品。

### 开源
网址：[https://github.com/cxxjava/CxxZookeeper](https://github.com/cxxjava/CxxZookeeper)

### 特点 
兼容性：c++开发，完全兼容java版zookeeper；
跨平台：同时支持Linux32/64、OSX64和WIN64三大平台，支持C++11及以上；

### 对比 
性能：未深入优化，目前release版本性能接近java版，使用zk-latencies.py测试得出的数据基本一致；
内存：c++版有明显优势，跟java版同环境下对比内存少用一个数量级，且无GC困扰；

### 支持
Email: [cxxjava@163.com](mailto:cxxjava@163.com)
