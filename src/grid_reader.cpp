#include "ros/ros.h"
#include "nav_msgs/OccupancyGrid.h"
#include "nav_msgs/MapMetaData.h"
#include "std_msgs/Int8.h"
#include "std_msgs/Int8MultiArray.h"
#include "std_msgs/UInt32.h"
#include <opencv2/opencv.hpp>
#include "stdint.h"
#include <tf/transform_datatypes.h>
#include <tf/transform_listener.h>
#include "nav_msgs/Odometry.h"
#include "geometry_msgs/Twist.h"

#include <math.h>


using namespace cv;
using namespace nav_msgs;
using namespace std_msgs;

double yaw = 0.0;

void costmap_cb(const nav_msgs::OccupancyGrid::ConstPtr& msg){

    nav_msgs::MapMetaData mmd = msg->info;

    uint32_t width = mmd.width;

    uint32_t height = mmd.height;

    Mat data(width, height, CV_8UC3, Scalar(0,0,0));

	std::cout << "Message data size : " << msg->data.size() << std::endl;
    std::cout << "Width and height : " << width << "," << height << std::endl;	

    for(int i = 0; i < height * width; i++){
    	int confidence = msg->data.at(i);
	int x = i % width;
	int y = height - 1 - i / height;
	if (confidence>0){
	//std::cout<< "non neg = " << confidence << "x,y = " << x << "," << y <<std::endl;
	}


    	if(confidence < 0){
    		data.at<Vec3b>(x,y)[0] = 0;
		data.at<Vec3b>(x,y)[1] = 0;
		data.at<Vec3b>(x,y)[2] = 0;
    	} else if (confidence < 70){
    		data.at<Vec3b>(x,y)[0] = 60;
		data.at<Vec3b>(x,y)[1] = 20;
		data.at<Vec3b>(x,y)[2] = 20;
    	} else if (confidence < 90){
    		data.at<Vec3b>(x,y)[0] = 200;
		data.at<Vec3b>(x,y)[1] = 150;
		data.at<Vec3b>(x,y)[2] = 50;
    	} else{
    		data.at<Vec3b>(x,y)[0] = 0;
		data.at<Vec3b>(x,y)[1] = 0;
		data.at<Vec3b>(x,y)[2] = 255;
    	}
    	
    }
    std::cout << "costmap_cb got a message: " << msg << std::endl;

    std::cout << "\nShowing Image" << std::endl;
    //Mat temp = Mat(height, width, CV_8UC3, data);
    Mat temp2;
    Mat image;
    resize(data, temp2, cv::Size(data.rows/8, data.cols/8), cv::INTER_NEAREST);
    flip(temp2,image,0);
    
    line(image,Point(image.rows/2,image.cols/2),Point(image.rows/2 + cos(yaw)*50,image.cols/2 + sin(yaw)*50),Scalar(100,100,20),10,8);
    
    imshow( "Local Costmap", image );

    waitKey(3);
}

void odom_cb(const nav_msgs::Odometry::ConstPtr& msg){
    geometry_msgs::Quaternion quat = msg->pose.pose.orientation;
    tf::Quaternion quat2(quat.x, quat.y, quat.z, quat.w);
    tf::Matrix3x3 matrix(quat2);
    double roll, pitch, y;
    matrix.getRPY(roll, pitch, y);
    std::cout << "RPY: " << roll << " , " << pitch << " , " << yaw << std::endl;
    yaw = y;
}


int main(int argc, char** argv){
	ros::init(argc,argv,"grid_reader");
	
	ros::NodeHandle n;
	
	ros::Subscriber costmap_sub = n.subscribe("/map",100,costmap_cb);
    	//ros::Subscriber odom_sub = n.subscribe("/odom", 100, odom_cb);

	
	namedWindow( "Local Costmap", WINDOW_AUTOSIZE );

	while(ros::ok()){
		ros::spin();
	}
    	
	return 0;
}
