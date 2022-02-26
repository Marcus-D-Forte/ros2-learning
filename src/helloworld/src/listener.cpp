#include <rclcpp/rclcpp.hpp>
#include <std_msgs/msg/string.hpp>
#include <sensor_msgs/msg/point_cloud2.hpp>
#include <pcl_conversions/pcl_conversions.h>

#include <memory>

using PointCloudT = sensor_msgs::msg::PointCloud2;

class Listener : public rclcpp::Node
{
public:
    Listener() : Node("listener")
    {
        // subscription = this->create_subscription<std_msgs::msg::String>("topic", 10, std::bind(&Listener::callback,this,std::placeholders::_1));
        subscription = this->create_subscription<std_msgs::msg::String>("topic", 10, std::bind(&Listener::callback,this,std::placeholders::_1));
        subscription_cloud = this->create_subscription<PointCloudT>("cloud", 10, std::bind(&Listener::callback_cloud,this,std::placeholders::_1));
    }

private:
    void callback(const std_msgs::msg::String::SharedPtr msg)
    {
        RCLCPP_INFO(this->get_logger(), "msg: %s", msg->data.c_str());
    }

    void callback_cloud(const PointCloudT::SharedPtr msg){
        RCLCPP_INFO(this->get_logger(), "msg: got cloud");
        RCLCPP_INFO(this->get_logger(), "fields size: %d" , msg->fields.size());
        pcl::PointCloud<pcl::PointXYZRGB> cloud;
        pcl::fromROSMsg(*msg,cloud);
        RCLCPP_INFO_STREAM(this->get_logger(), cloud);
        RCLCPP_INFO_STREAM(this->get_logger(), cloud.points[0]);

    }

    rclcpp::Subscription<std_msgs::msg::String>::SharedPtr subscription;
    rclcpp::Subscription<PointCloudT>::SharedPtr subscription_cloud;
};

int main(int argc, char **argv)
{
    rclcpp::init(argc, argv);

    std::shared_ptr<Listener> node = std::make_shared<Listener>();

    rclcpp::spin(node);

    rclcpp::shutdown();
    return 0;
}