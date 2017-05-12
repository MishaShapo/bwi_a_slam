#include <ros/ros.h>
#include <tf/tf.h>
#include <move_base_msgs/MoveBaseAction.h>
#include <actionlib/client/simple_action_client.h>
#include <tf/transform_listener.h>
#include <math.h>

int main(int argc, char** argv){
	ros::init(argc,argv, "explorer");
	ros::NodeHandle n;
	actionlib::SimpleActionClient<move_base_msgs::MoveBaseAction> ac("move_base",true);
	
	/*while(!ac.waitForServer(ros::Duration(5.0))){
		ROS_INFO("Waiting for MoveBaseClient server.\n");	
	}*/

	//ac.waitForServer();
	
	move_base_msgs::MoveBaseGoal goal;
	double yaw = 0.0;

	while(ros::ok()){
		
		std::cout << "enter rotation angle (degrees) :\n ";
		std::cin>>yaw; 	
		
		yaw = yaw * 180 / M_PI;
		
		std::cout << "Yaw (in degrees) : " << yaw << std::endl;
		
		goal.target_pose.header.frame_id = "base_link";
		goal.target_pose.header.stamp = ros::Time::now();

		goal.target_pose.pose.orientation = tf::createQuaternionMsgFromYaw(yaw);

		ac.sendGoal(goal);
		
		std::cout << "state : " << (ac.getState() == actionlib::SimpleClientGoalState::SUCCEEDED) << std::endl;

		bool finished = ac.waitForResult(ros::Duration(5.0));

		std::cout << "finished : " << finished << std::endl;
	}

	return 0;
}
