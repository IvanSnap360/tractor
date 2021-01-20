#! /usr/bin/env python3
import rospy
import sys
from ros2can.msg import ros2can_message
from ros2can.srv import get_data
rospy.init_node("ros2can_converter")

message_pub = rospy.Publisher("/tractor/ros2can/write_message_buffer", ros2can_message, queue_size=10)

rate = rospy.Rate(0.5)

def msg_read(msg):
    print("id:",msg.id,"[",msg.data_1,msg.data_2,msg.data_3,msg.data_4,msg.data_5,msg.data_6,msg.data_7,msg.data_8,"]")

rospy.Subscriber("/tractor/ros2can/read_message_buffer",ros2can_message,msg_read)

rospy.spin()        
                
