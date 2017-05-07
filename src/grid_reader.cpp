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

    u_char data[3*msg->data.size()];
    uint32_t width = mmd.width;
    uint32_t height = mmd.height;

    for(int i = 0; i < msg->data.size(); i++){
    	int confidence = msg->data.at(i);
    	if(confidence < 0){
    		data[3*i] = 0;
    		data[3*i+1] = 0;
    		data[3*i+2] = 0;
    	} else if (confidence < 70){
    		data[3*i] = 60;
    		data[3*i+1] = 20;
    		data[3*i+2] = 20;
    	} else if (confidence < 90){
    		data[3*i] = 200;
    		data[3*i+1] = 150;
    		data[3*i+2] = 50;
    	} else{
    		data[3*i] = 0;
    		data[3*i+1] = 0;
    		data[3*i+2] = 255;
    	}
    	
    }

    std::cout << "\nShowing Image" << std::endl;
    Mat temp = Mat(height, width, CV_8UC3, data);
    Mat temp2;
    Mat image;
  	resize(temp, temp2, cv::Size(temp.rows*2, temp.cols*2), cv::INTER_NEAREST);
    flip(temp2,image,1);
    imshow( "Local Costmap", image );

    waitKey(10);
}


int main(int argc, char** argv){
	ros::init(argc,argv,"grid_reader");
	
	ros::NodeHandle n;
	
	ros::Subscriber costmap_sub = n.subscribe("/move_base/local_costmap/costmap",100,costmap_cb);
	namedWindow( "Local Costmap", WINDOW_AUTOSIZE );
    
    
	ros::spin();
	
	return 0;
}
