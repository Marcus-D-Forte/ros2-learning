# useful commands
remapping 
´´ros2 run helloworld listener --ros-args -r cloud:=claaud -r __node:=listener2´´

composition
- Create a class. Inherit `rclcpp::Node` and implement constructor `<class>(const rclcpp::NodeOptions & options)`
- Call ` #include <rclcpp_components/register_node_macro.hpp>
RCLCPP_COMPONENTS_REGISTER_NODE(<namespace>::<class>)` at the end of implementation
- in `package.xml`, make sure you have `<depend>rclcpp_components</depend>`
- in `CMakeLists.txt` call `rclcpp_components_register_nodes(<target> <namespace>::<class>)
- You can still link this class in compile time with `target_link_libraries(<client target> <class>)`