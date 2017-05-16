# Autonomous Localization and Mapping for the BWI robot
The objective is to develop a better navigation and exploration system for
the BWI segbots. We will develop new algorithms for having the robot autonomously
generate a map of an area it has never explored before.

## Usage
1. Install hector_mapping http://wiki.ros.org/hector_mapping
   
   To use hector_mapping, you need a source of sensor_msgs/LaserScan data
   
2. Launch grid_reader by running the command

   `rosrun bwi_a_slam grid_reader`
   
   Grid reader should interpret the occupancy grid created by the robot's sensory input in order to visualize it

3. Launch the gmapping node by running the command 

   `roslaunch segbot_navigation robot_with_gmapping_v2.launch`

4. Launch explorer by running the command

   `rosrun bwi_a_slam explorer`
   
   Explorer publishes to the command velocity topic after a decision has been made


