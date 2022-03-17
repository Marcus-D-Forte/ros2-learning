#include "helloworld/talker.h"

using namespace std::chrono_literals;

namespace helloworld
{

    MinimalPublisher::MinimalPublisher(const rclcpp::NodeOptions & options)
        : Node("talker",options), count_(0)
    {
        this->declare_parameter<int>("color", 255);
        publisher_ = this->create_publisher<std_msgs::msg::String>("topic", 10);
        publisher_cloud = this->create_publisher<PointCloudT>("cloud", 10);
        timer_ = this->create_wall_timer(
            500ms, std::bind(&MinimalPublisher::timer_callback, this));
    }

    MinimalPublisher::~MinimalPublisher()
    {
    }

    void MinimalPublisher::timer_callback()
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
        this->get_parameter("color", pt.r);
        // pt.r =
        pt.g = 0;
        pt.b = 0;
        cloud_.push_back(pt);

        pcl::toROSMsg(cloud_, cloud);
        cloud.header.frame_id = "map";
        cloud.header.stamp = this->now();
        publisher_cloud->publish(cloud);
    }
} // namespace
#include <rclcpp_components/register_node_macro.hpp>
RCLCPP_COMPONENTS_REGISTER_NODE(helloworld::MinimalPublisher)
