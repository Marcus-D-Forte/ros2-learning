#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"

#include <pcl/point_cloud.h>
#include <pcl_conversions/pcl_conversions.h>
#include <sensor_msgs/msg/point_cloud2.hpp>

namespace helloworld
{
    class MinimalPublisher : public rclcpp::Node
    {
        using PointCloudT = sensor_msgs::msg::PointCloud2; // test
    public:
        MinimalPublisher(const rclcpp::NodeOptions & options);
        virtual ~MinimalPublisher();
        void timer_callback();

    private:
        rclcpp::TimerBase::SharedPtr timer_;
        rclcpp::Publisher<std_msgs::msg::String>::SharedPtr publisher_;
        rclcpp::Publisher<PointCloudT>::SharedPtr publisher_cloud;

        size_t count_;
    };

}
