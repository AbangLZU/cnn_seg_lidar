#ifndef CNN_SEGMENTATION_H
#define CNN_SEGMENTATION_H

#include <chrono>

#include <ros/ros.h>

#include "caffe/caffe.hpp"

// #include <pcl_conversions/pcl_conversions.h>
#include <pcl/point_types.h>
#include <pcl_ros/point_cloud.h>
#include <pcl/filters/extract_indices.h>

#include <rockauto_msgs/DetectedObjectArray.h>
#include <visualization_msgs/MarkerArray.h>
#include <jsk_recognition_msgs/BoundingBoxArray.h>

#include <std_msgs/Header.h>

#include "cluster2d.h"
#include "feature_generator.h"
// #include "pcl_types.h"
// #include "modules/perception/obstacle/lidar/segmentation/cnnseg/cnn_segmentation.h"

#define __APP_NAME__ "lidar_cnn_seg_detect"

struct CellStat
{
  CellStat() : point_num(0), valid_point_num(0)
  {
  }

  int point_num;
  int valid_point_num;
};

class CNNSegmentation
{
public:
  CNNSegmentation();

  void run();

  void test_run();

private:
  double range_, score_threshold_;
  double max_distance_, min_distance_, clip_height_;
  int width_;
  int height_;
  bool use_constant_feature_;
  std_msgs::Header message_header_;
  std::string topic_src_;

  int gpu_device_id_;
  bool use_gpu_;

  // nodehandle
  ros::NodeHandle nh_;

  // publisher
  ros::Publisher points_pub_;

  ros::Publisher mapping_points_pub_;
  ros::Publisher original_points_pub_;

  ros::Publisher objects_pub_;

  // subscriber
  ros::Subscriber points_sub_;

  std::shared_ptr<caffe::Net<float>> caffe_net_;

  // center offset prediction
  boost::shared_ptr<caffe::Blob<float>> instance_pt_blob_;
  // objectness prediction
  boost::shared_ptr<caffe::Blob<float>> category_pt_blob_;
  // fg probability prediction
  boost::shared_ptr<caffe::Blob<float>> confidence_pt_blob_;
  // object height prediction
  boost::shared_ptr<caffe::Blob<float>> height_pt_blob_;
  // raw features to be input into network
  boost::shared_ptr<caffe::Blob<float>> feature_blob_;
  // class prediction
  boost::shared_ptr<caffe::Blob<float>> class_pt_blob_;

  // clustering model for post-processing
  std::shared_ptr<Cluster2D> cluster2d_;

  // bird-view raw feature generator
  std::shared_ptr<FeatureGenerator> feature_generator_;

  bool init();

  bool segment(const pcl::PointCloud<pcl::PointXYZI>::Ptr &pc_ptr,
               const pcl::PointIndices &valid_idx,
               rockauto_msgs::DetectedObjectArray &objects);

  void pointsCallback(const sensor_msgs::PointCloud2 &msg);

  void pubColoredPoints(const rockauto_msgs::DetectedObjectArray &objects);

  void segDetected(const rockauto_msgs::DetectedObjectArray &objects,
                   const pcl::PointCloud<pcl::PointXYZI>::Ptr &in_pc_ptr);
  void remove_close_far_above_pt(const pcl::PointCloud<pcl::PointXYZI>::Ptr in,
                                            const pcl::PointCloud<pcl::PointXYZI>::Ptr out);
};

#endif //CNN_SEGMENTATION_H
