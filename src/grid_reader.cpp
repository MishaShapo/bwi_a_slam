#include "ros/ros.h"
#include "nav_msgs/OccupancyGrid.h"

using namespace cv;

void costmap_cb(const nav_msgs::OccupancyGrid::ConstPtr& msg){
	std::cout << "costmap_cb got a message: " << msg << std::endl;
    nav_msgs::MapMetaData mmd = msg->info;
    int8[] data = msg->data;
    
    uint32 width = mmd.width;
    uint32 height = mmd.height;
    
    Mat image = Mat(height, width, CV_8UC1, data, AUTO_STEP);
    imshow( "Local Costmap", image );
}


int main(int argc, char** argv){
	ros::init(argc,argv,"grid_reader");
	
	ros::NodeHandle n;
	
	ros::Subscriber costmap_sub = n.subscribe("/move_base/local_costmap/costmap",100,costmap_cb);
	namedWindow( "Local Costmap", WINDOW_AUTOSIZE );
    
    
	ros::spin();
	
	return 0;
}
