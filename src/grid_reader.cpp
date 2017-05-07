#include "ros/ros.h"
#include "nav_msgs/OccupancyGrid.h"
#include "nav_msgs/MapMetaData.h"
#include "std_msgs/Int8.h"
#include "std_msgs/Int8MultiArray.h"
#include "std_msgs/UInt32.h"
#include <opencv2/opencv.hpp>
#include "stdint.h"
#include <tf/transform_datatypes.h>
#include "nav_msgs/Odometry.h"
#include <math.h>


using namespace cv;
using namespace nav_msgs;
using namespace std_msgs;

double yaw = 0.0;

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
    
    arrowedLine(image,Point(image.rows/2,image.cols/2),Point(image.rows/2 + cos(yaw)*50,image.cols/2 + sin(yaw)*50),Scalar(100,100,20),10,8);
    
    imshow( "Local Costmap", image );

    waitKey(10);
}

void odom_cb(const nav_msgs::Odometry::ConstPtr& msg){
    geometry_msgs::Quaternion quat = msg->pose.pose.orientation;
    tf::Quaternion quat2(quat.x, quat.y, quat.z, quat.w);
    tf::Matrix3x3 matrix(quat2);
    double roll, pitch, y;
    matrix.getRPY(roll, pitch, y);
    
    yaw = y;
}


int main(int argc, char** argv){
	ros::init(argc,argv,"grid_reader");
	
	ros::NodeHandle n;
	
	ros::Subscriber costmap_sub = n.subscribe("/move_base/local_costmap/costmap",100,costmap_cb);
    ros::Subscriber odom_sub = n.subscribe("/odom", 100, odom_cb);
	namedWindow( "Local Costmap", WINDOW_AUTOSIZE );
    
    
	ros::spin();
	
	return 0;
}
