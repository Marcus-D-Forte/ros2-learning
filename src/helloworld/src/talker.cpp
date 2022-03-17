#include <chrono>
#include <functional>
#include <memory>
#include <string>

#include "helloworld/talker.h"

using namespace helloworld;


/* This example creates a subclass of Node and uses std::bind() to register a
 * member function as a callback from the timer. */



int main(int argc, char *argv[])
{
  rclcpp::init(argc, argv);
  rclcpp::NodeOptions options;
  
  auto node_ = std::make_shared<MinimalPublisher>(options);
  // rclcpp::spin(node_);
  rclcpp::executors::MultiThreadedExecutor executor;
  executor.add_node(node_);

  int count = 0;
  while (rclcpp::ok())
  {



    
    executor.spin_some();
  }
  rclcpp::shutdown();
  return 0;
}