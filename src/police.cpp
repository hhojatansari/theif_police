#include <iostream>
#include <math.h>
#include "ros/ros.h"
#include "turtlesim/Pose.h"
#include "geometry_msgs/Twist.h"

using namespace std;
using namespace geometry_msgs;
using namespace ros;
using namespace turtlesim;

Pose TheifPose;
Pose PolicePose;

float constant = 0.3;
float distance_tolerance = 0.9;

class MyTurtle {
public:
    MyTurtle();
    void trackThief();
    float euclidean_distance();
    float liner_vel();
    float angle_vel();
    float steering_angle();
    
    NodeHandle ListenerTheifNode;
    NodeHandle ListenerPoliceNode;
    Subscriber TheifSub;
    Subscriber PoliceSub;
    NodeHandle CommanderNode;
    Publisher Command;
    Twist msg;
private:
};

MyTurtle::MyTurtle(){
}

void MyTurtle::trackThief(){
    if(euclidean_distance() >= distance_tolerance){
        cout << "Police: Waitttt ..!" << endl;
        msg.linear.x = liner_vel();
        msg.linear.y = 0;
        msg.linear.z = 0;
        msg.angular.x = 0;
        msg.angular.y = 0;
        msg.angular.z = angle_vel();
        Command.publish(msg);
    }
    else{
        cout << "Police: okay, let's go prison :/" << endl;
        msg.linear.x = 0;
        msg.linear.y = 0;
        msg.linear.z = 0;
        msg.angular.x = 0;
        msg.angular.y = 0;
        msg.angular.z = 0;
        Command.publish(msg);
    }
}

float MyTurtle::euclidean_distance(){
    return sqrt(pow(TheifPose.x - PolicePose.x, 2) + pow(TheifPose.y - PolicePose.y, 2));
}

float MyTurtle::liner_vel(){
    return constant * euclidean_distance();
}

float MyTurtle::angle_vel(){
    return constant * (steering_angle() - PolicePose.theta)*1.5;
}

float MyTurtle::steering_angle(){
    return atan2((TheifPose.y - PolicePose.y),(TheifPose.x - PolicePose.x));
}

void thiefPoseUpdate(const turtlesim::Pose::ConstPtr& msg)
{
    TheifPose.x = msg->x;
    TheifPose.y = msg->y;
    TheifPose.linear_velocity = msg->linear_velocity;
    TheifPose.angular_velocity = msg->angular_velocity;
    TheifPose.theta = msg->theta;
}

void policePoseUpdate(const turtlesim::Pose::ConstPtr& msg)
{
    PolicePose.x = msg->x;
    PolicePose.y = msg->y;
    PolicePose.linear_velocity = msg->linear_velocity;
    PolicePose.angular_velocity = msg->angular_velocity;
    PolicePose.theta = msg->theta;
}

int main(int argc, char **argv)
{
    ros::init(argc, argv, "police");
    MyTurtle turtle;
    
    turtle.TheifSub = turtle.ListenerTheifNode.subscribe("/theif/pose", 10, thiefPoseUpdate);
    turtle.PoliceSub = turtle.ListenerPoliceNode.subscribe("/police/pose", 10, policePoseUpdate);
    turtle.Command = turtle.CommanderNode.advertise<geometry_msgs::Twist>("/police/cmd_vel", 10);
    
    ros::Rate loop_rate(1);
    while (ros::ok())
    {
        turtle.trackThief();
        ros::spinOnce();
        loop_rate.sleep();
//        ros::spin();      //It's not working
    }
  return 0;
}