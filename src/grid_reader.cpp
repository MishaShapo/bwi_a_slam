#include "ros/ros.h"
#include "nav_msgs/OccupancyGrid.h"


void costmap_cb(const nav_msgs::OccupancyGrid::ConstPtr& msg){
	std::cout << "costmap_cb got a message: " << msg << std::endl;
}

int main(int argc, char** argv){
	ros::init(argc,argv,"grid_reader");
	
	ros::NodeHandle n;
	
	ros::Subscriber costmap_sub = n.subscribe("/move_base/local_costmap/costmap",100,costmap_cb);
	
	ros::spin();
	
	return 0;
}
