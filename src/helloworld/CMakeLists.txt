cmake_minimum_required(VERSION 3.5)
project(helloworld)

# Default to C++14
if(NOT CMAKE_CXX_STANDARD)
  set(CMAKE_CXX_STANDARD 14)
endif()

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(node_plugins "")
# find dependencies
find_package(ament_cmake REQUIRED)

find_package(rclcpp REQUIRED)
find_package(rclcpp_components REQUIRED)
find_package(rcutils REQUIRED)
find_package(std_msgs REQUIRED)
find_package(rclcpp_components REQUIRED)
find_package(pcl_conversions REQUIRED)
find_package(sensor_msgs REQUIRED)
find_package(PCL 1.12 REQUIRED)
find_package(class_loader REQUIRED)

add_library(talker_class SHARED lib/talker_class.cpp)
ament_target_dependencies(talker_class rclcpp std_msgs pcl_conversions sensor_msgs PCL class_loader)
rclcpp_components_register_nodes(talker_class "helloworld::MinimalPublisher")
target_include_directories(talker_class PUBLIC include)

add_executable(talker src/talker.cpp)
target_link_libraries(talker talker_class)
ament_target_dependencies(talker rclcpp)
target_include_directories(talker PUBLIC include)

add_executable(listener src/listener.cpp)
ament_target_dependencies(listener rclcpp std_msgs PCL pcl_conversions sensor_msgs)




  install(TARGETS 
    talker
    listener
    DESTINATION lib/${PROJECT_NAME})

# IMPORTANT!!
  install(TARGETS
    talker_class
    LIBRARY DESTINATION lib)  

  install(DIRECTORY launch
  DESTINATION share/${PROJECT_NAME})



if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  # the following line skips the linter which checks for copyrights
  # uncomment the line when a copyright and license is not present in all source files
  #set(ament_cmake_copyright_FOUND TRUE)
  # the following line skips cpplint (only works in a git repo)
  # uncomment the line when this package is not in a git repo
  #set(ament_cmake_cpplint_FOUND TRUE)
  ament_lint_auto_find_test_dependencies()
endif()

ament_package()
