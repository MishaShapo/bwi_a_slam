#include <ros/ros.h>
#include <tf/tf.h>
#include <move_base_msgs/MoveBaseAction.h>
#include <actionlib/client/simple_action_client.h>
#include <tf/transform_listener.h>
#include "geometry_msgs/Twist.h"
#include <actionlib/server/simple_action_server.h>
#include "geometry_msgs/Pose.h"
#include "geometry_msgs/PoseArray.h"
#include <math.h>


int main(int argc, char** argv){
	ros::init(argc,argv, "explorer");
	ros::NodeHandle n;
	
	//ros::Rate rate(100.0);

    actionlib::SimpleActionClient<move_base_msgs::MoveBaseAction> ac("move_base",true);
    
    move_base_msgs::MoveBaseGoal goal;
    
    double yaw = 0.0
    
    /*
     Bheavior: 
     1. Try to move forward 1 meter
     2. If it succeed:
            2.a 1 out of every 5 times, stop and spin
        If it did not succeed:
            2.b spin around in a circle until a valid nav goal appears and move there
     3. Loop
     */
    
    
    for(int i = 0; i < 10; i++){
        //set the header
        goal.target_pose.header.stamp = ros::Time::now();
        goal.target_pose.header.frame_id = "/base_link";
            
            //set relative x, y, and angle
        goal.target_pose.pose.position.x = 1.0;
        goal.target_pose.pose.position.y = 0.0;
        goal.target_pose.pose.position.z = 0.0;
        goal.target_pose.pose.orientation = tf::createQuaternionMsgFromYaw(yaw);
            
        //send the goal
        ac.sendGoal(goal);
            
        //block until the action is completed
        ac.waitForResult();
        
        while(ac.getState() != actionlib::SimpleActionClientGoalState::SUCCEEDED){
            yaw += 2* M_PI / 10;
            yaw %= 2*M_PI;
            goal.target_pose.header.stamp = ros::Time::now();
            goal.target_pose.pose.orientation = tf::createQuaternionMsgFromYaw(yaw);
            ac.sendGoal(goal);
            ac.waitForResult();
            
        }
        if(i % 5 == 0){
            for(int i = 0; i < 4; i++){
                goal.target_pose.header.stamp = ros::Time::now();
                goal.target_pose.pose.orientation = tf.createQuaternionMsgFromYaw(M_PI / 2);
                ac.sendGoal(goal);
                ac.waitForResult();
            }
        }
    }
	
    return 0;
}
