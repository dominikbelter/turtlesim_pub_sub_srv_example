#include "ros/ros.h"
#include "geometry_msgs/Twist.h"
#include "turtlesim/Color.h"
#include "turtlesim/SetPen.h"

#include <sstream>

void chatterCallback(const turtlesim::Color::ConstPtr& msg)
{
    std::cout << (int)msg->b << ", "<< (int)msg->g << ", " << (int)msg->r << "\n";
}

int main(int argc, char **argv)
{
    ros::init(argc, argv, "talker");

    ros::NodeHandle n;

    ros::Publisher chatter_pub = n.advertise<geometry_msgs::Twist>("/turtle1/cmd_vel", 1000);

    ros::Subscriber sub = n.subscribe("/turtle1/color_sensor", 1000, chatterCallback);

    ros::ServiceClient client = n.serviceClient<turtlesim::SetPen>("/turtle1/set_pen");

    ros::Rate loop_rate(10);

    int count = 0;
    while (ros::ok())
    {
        geometry_msgs::Twist msg;

        msg.linear.x = sin(double(count)*0.1);
        msg.angular.z = cos(double(count)*0.2);

        chatter_pub.publish(msg);

        if (count == 50){
            turtlesim::SetPen srv;
            srv.request.r = 255;
            srv.request.g = 0;
            srv.request.b = 0;
            srv.request.width = 3;
            srv.request.off = 0;
            if (client.call(srv)) {
                ROS_INFO("Success!");
            }
            else {
                ROS_ERROR("Failed to call service");
                return 1;
            }
        }

        if (count == 60){
            turtlesim::SetPen srv;
            srv.request.off = 1;
            if (client.call(srv)) {
                ROS_INFO("Success!");
            }
            else {
                ROS_ERROR("Failed to call service");
                return 1;
            }
        }

        ros::spinOnce();

        loop_rate.sleep();
        ++count;
    }


    return 0;
}
