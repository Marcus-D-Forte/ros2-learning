# turtlesim/launch/multisim.launch.py

from launch import LaunchDescription
import launch_ros.actions


def generate_launch_description():
    return LaunchDescription([
        launch_ros.actions.Node(
            package='helloworld', executable='listener', output='screen'),
        launch_ros.actions.Node(
            package='helloworld', executable='talker', output='screen'),
        
    ])