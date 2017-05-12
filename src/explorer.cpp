#include <ros/ros.h>
#include <tf/tf.h>
#include <move_base_msgs/MoveBaseAction.h>
#include <actionlib/client/simple_action_client.h>
#include <tf/transform_listener.h>
#include "geometry_msgs/Twist.h"

#include <stdio.h>
#include <termios.h>            //termios, TCSANOW, ECHO, ICANON
#include <unistd.h> 
#include <math.h>

/*
int getch()
{
  static struct termios oldt, newt;
  tcgetattr( STDIN_FILENO, &oldt);           // save old settings
  newt = oldt;
  newt.c_lflag &= ~(ICANON);                 // disable buffering      
  tcsetattr( STDIN_FILENO, TCSANOW, &newt);  // apply new settings

  int c = getchar();  // read character (non-blocking)

  tcsetattr( STDIN_FILENO, TCSANOW, &oldt);  // restore old settings
  return c;
}*/

int getc(){
  system ("/bin/stty raw");
  int c = getchar();
  /* use system call to set terminal behaviour to more normal behaviour */
  system ("/bin/stty cooked");
  return c;

}

int main(int argc, char** argv){
	ros::init(argc,argv, "explorer");
	ros::NodeHandle n;
	
	ros::Rate rate(100.0);

	float x,y,z,th;
	bool pause = false;
	int counter = 0;

	ros::Publisher vel_pub = n.advertise<geometry_msgs::Twist>("cmd_vel", 10);
	
	while(ros::ok()){
		geometry_msgs::Twist goal;
		int c = getc();   // call your non-blocking input function
	  		
		if(c == ' '){
			pause = true;
			goal.linear.x = 0;
			goal.linear.x = 0;
			goal.linear.x = 0;
			goal.angular.z = 0;
			vel_pub.publish(goal);
		} else if(c == '\x0D'){
			pause = false;
			counter = 0;
		} 
		//backspace is 127
		std::cout << "Key = " << c << std::endl;

		if(pause){
			continue;
		}

		goal.angular.z = -1;
		vel_pub.publish(goal);			
	
		ros::spinOnce();
		rate.sleep();
	}

	return 0;
}
