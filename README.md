# Autonomous Localization and Mapping for the BWI robot
The objective is to develop a better navigation and exploration system for
the BWI segbots. We will develop new algorithms for having the robot autonomously
generate a map of an area it has never explored before.

## Usage
1. Install hector_mapping http://wiki.ros.org/hector_mapping
   
   To use hector_mapping, you need a source of sensor_msgs/LaserScan data
2. Launch grid_reader
   -rosrun bwi_a_slam grid_reader
   
   Grid reader should interpret the occupancy grid created by the robot's sensory input in order to determine movement

3. Launch conquistador
   -rosrun bwi_a_slam conquistador
   

## Grid reader
Our grid_reader node subscribes to the bwi's local_costmap rostopic and interprets the occupancy grid created by the robot's sensory input in order to determine movement.


## TODO
~~1. Utilize the gmapping package to develop a live map~~

~~2. Establish a certain frequency for the map to be updated and published to another node~~

~~3. Develop a node that will interpret the new map and make decisions accordingly~~

~~4. Allow the robot to move but avoid all obstacles based off of interpretation of environment~~

~~5. Set navigation goals along walls and rotate at arbitrary frequency~~

~~6. Keep track of current position relative to the initial starting point in order to localize~~

