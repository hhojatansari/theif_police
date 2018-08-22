# Theif-Police
Chasing a Turtle by Another Turtle using ROS Turtlesim package


### Create Catkin WorkSpace and clone Repo
```
cd ~
mkdir -p catkin_ws/src
cd catkin_ws/src
git clone git@github.com:hhojatansari/theif_police.git
cd ..
catkin_make
```
### run project
if using bash:
```
source ~/catkin_ws/devel/setup.bash 
```
if using zsh:
```
source ~/catkin_ws/devel/setup.zsh 
```
```
roslaunch theif_police theif_police.launch 
```

### to move theif turtle 
```
rosrun turtlesim turtle_teleop_key /turtle1/cmd_vel:=/theif/cmd_vel
```
![Alt Text](https://raw.githubusercontent.com/hhojatansari/Theif-Police/master/outpout.gif)

## nodes and topics graph:
![Alt Text](https://raw.githubusercontent.com/hhojatansari/Theif-Police/master/graph.png)

this package Used from [this tutorial](http://wiki.ros.org/turtlesim/Tutorials/Go%20to%20Goal)
