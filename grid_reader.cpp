#include "ros/ros.h"
#include "nav_msgs/OccupancyGrid.msg"

void gridCallback(const nav_msgs::OccupancyGrid.msg::ConstPtr& msg)
{
  
}

int main(int argc, char **argv)
{
  
  ros::init(argc, argv, "grid_reader");


  ros::NodeHandle n;

  ros::Subscriber sub = n.subscribe("map", 1000, chatterCallback);



  ros::spin();


  return 0;
}
