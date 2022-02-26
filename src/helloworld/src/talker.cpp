#include <chrono>
#include <functional>
#include <memory>
#include <string>

#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"
#include "helloworld/method.hpp"

#include <pcl/point_cloud.h>
#include <pcl_conversions/pcl_conversions.h>
#include <sensor_msgs/msg/point_cloud2.hpp>

using PointCloudT = sensor_msgs::msg::PointCloud2; // test

using namespace std::chrono_literals;

/* This example creates a subclass of Node and uses std::bind() to register a
 * member function as a callback from the timer. */

class MinimalPublisher : public rclcpp::Node
{
public:
  MinimalPublisher()
      : Node("talker"), count_(0)
  {
    this->declare_parameter<int>("color", 255);
    publisher_ = this->create_publisher<std_msgs::msg::String>("topic", 10);
    publisher_cloud = this->create_publisher<PointCloudT>("cloud", 10);
    timer_ = this->create_wall_timer(
        500ms, std::bind(&MinimalPublisher::timer_callback, this));
  }

private:
  void timer_callback()
  {
    auto message = std_msgs::msg::String();
    message.data = "Hello, world! " + std::to_string(count_++);
    RCLCPP_INFO(this->get_logger(), "Publishing: '%s'", message.data.c_str());
    publisher_->publish(message);

    PointCloudT cloud;
    pcl::PointCloud<pcl::PointXYZRGB> cloud_;
    pcl::PointXYZRGB pt;
    pt.x = 1;
    pt.y = 2;
    pt.z = 3;
    this->get_parameter("color",pt.r);
    // pt.r = 
    pt.g = 0;
    pt.b = 0;
    cloud_.push_back(pt);

    pcl::toROSMsg(cloud_,cloud);
        cloud.header.frame_id = "map";
    cloud.header.stamp = this->now();
    publisher_cloud->publish(cloud);
  }
  rclcpp::TimerBase::SharedPtr timer_;
  rclcpp::Publisher<std_msgs::msg::String>::SharedPtr publisher_;

  rclcpp::Publisher<PointCloudT>::SharedPtr publisher_cloud;

  size_t count_;
};

int main(int argc, char *argv[])
{
  rclcpp::init(argc, argv);

  rclcpp::spin(std::make_shared<MinimalPublisher>());
  rclcpp::shutdown();
  return 0;
}