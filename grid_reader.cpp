#include "ros/ros.h"
#include "nav_msgs/OccupancyGrid.msg"
#include <tf/transform_listener.h>
#include <costmap_2d/costmap_2d_ros.h>

void gridCallback(const nav_msgs::OccupancyGrid.msg::ConstPtr& msg)
{
  
}

int main(int argc, char **argv)
{
  
  ros::init(argc, argv, "grid_reader");


  ros::NodeHandle n;

  ros::Subscriber sub = n.subscribe("map", 1000, gridCallback);



  ros::spin();


  return 0;
}
