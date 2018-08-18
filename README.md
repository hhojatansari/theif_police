# Theif-Police
Chasing a Turtle by Another Turtle using ROS Turtlesim package

### run project
```
soruce <path_to_catkin_WorkSpace>/devel/setup.bash
roslaunch thief_police thief_police.launch 
```
### to move thief turtle 
```
rosrun turtlesim turtle_teleop_key /turtle1/cmd_vel:=/thief/cmd_vel
```
![Alt Text](https://raw.githubusercontent.com/hhojatansari/Theif-Police/master/outpout.gif)

## nodes and topics graph:
![Alt Text](https://raw.githubusercontent.com/hhojatansari/Theif-Police/master/graph.png)

this package Used from [this tutorial](http://wiki.ros.org/turtlesim/Tutorials/Go%20to%20Goal)
