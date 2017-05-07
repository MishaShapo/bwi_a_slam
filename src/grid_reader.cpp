#include "ros/ros.h"
#include "nav_msgs/OccupancyGrid.h"
#include "nav_msgs/MapMetaData.h"
#include "std_msgs/Int8.h"
#include "std_msgs/Int8MultiArray.h"
#include "std_msgs/UInt32.h"
#include <opencv2/opencv.hpp>
#include "stdint.h"


using namespace cv;
using namespace nav_msgs;
using namespace std_msgs;

void costmap_cb(const nav_msgs::OccupancyGrid::ConstPtr& msg){
	std::cout << "costmap_cb got a message: " << msg << std::endl;
    nav_msgs::MapMetaData mmd = msg->info;

    
    uint32_t width = mmd.width;
    uint32_t height = mmd.height;
    
    Mat image = Mat(height, width, CV_8UC1, msg->data);
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
