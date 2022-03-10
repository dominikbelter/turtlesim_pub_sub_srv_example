#!/usr/bin/env python3
import rospy
import math
from std_msgs.msg import String
from geometry_msgs.msg import Twist
from turtlesim.msg import Color
from turtlesim.srv import *

def callback(data):
    rospy.loginfo(rospy.get_caller_id() + "I heard %d %d %d", data.r, data.g, data.b)

def set_pencil():
    rospy.wait_for_service('/turtle1/set_pen')
    try:
        set_pen = rospy.ServiceProxy('/turtle1/set_pen', SetPen)
        req = SetPenRequest()
        req.g = 120
        req.r = 80
        req.b = 209
        resp1 = set_pen(req)
    except rospy.ServiceException as e:
        print("Service call failed: %s"%e)

def talker():
    pub = rospy.Publisher('/turtle1/cmd_vel', Twist, queue_size=10)
    rospy.Subscriber("/turtle1/color_sensor", Color, callback)

    rospy.init_node('talker', anonymous=True)
    rate = rospy.Rate(10) # 10hz
    count = 0
    while not rospy.is_shutdown():
        cmd_vel = Twist()
        cmd_vel.linear.x = math.sin(0.1*count)
        cmd_vel.angular.z = math.cos(0.2*count)
        if (count == 50):
            set_pencil()

        pub.publish(cmd_vel)
        rate.sleep()
        count = count + 1

if __name__ == '__main__':
    try:
        talker()
    except rospy.ROSInterruptException:
        pass