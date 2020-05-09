## 深度学习Lidar障碍物检测模块使用说明(ROS)
## Deep learning based obstacle detection module(ROS)

This project use the CNN-Seg model from Baidu Apollo Project. And make it running in ROS.

### Dependence
* Ubuntu 16.04
* ROS kinetic
* CUDA 9.0
* Caffe

### Update 
This project have been test with Ubuntu 18.04 and CUDA 10.0. For  Ubuntu 18.04 and CUDA 10.0, you only neet to update the CMake version to > 3.12.2, here I use CMake 3.17.2:

```bash
tar -xvf cmake-3.17.2.tar.gz
cd cmake-3.17.2
cmake .
make -j8
sudo make install
sudo update-alternatives --install /usr/bin/cmake cmake /usr/local/bin/cmake 1 --force
```

then you will see:

```bash
cmake version 3.12.2

CMake suite maintained and supported by Kitware (kitware.com/cmake).
```

### Caffe Config
clone the caffe project in your home folder. like this:

```sh
cd
git clone https://github.com/BVLC/caffe.git
``` 

before install , install the dependencies:

```sh
sudo apt-get install libprotobuf-dev libleveldb-dev libsnappy-dev libopencv-dev libhdf5-serial-dev protobuf-compiler
sudo apt-get install --no-install-recommends libboost-all-dev

sudo apt-get install libopenblas-dev

sudo apt-get install libgflags-dev libgoogle-glog-dev liblmdb-dev

```

Then copy our Makefile.config to the caffe folder (replace the older one)

#### make & make distribute

```
sudo make -j8
sudo make distribute
```

if the there is error with opencv, try uncomment this line in Makefile.config:

```
# OPENCV_VERSION := 3
```

### Build the project
install the catkin build tool:

```
sudo apt-get install python-catkin-tools
```

build this project:

```
catkin build
```


### Run this project
```
source devel/setup.bash
./run_cnn_seg.sh
```