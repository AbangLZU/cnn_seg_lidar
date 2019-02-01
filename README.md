## Lidar 深度学习检测模块使用说明

### Dependence
* Ubuntu 16.04
* ROS kinetic
* CUDA 9.0
* Caffe

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