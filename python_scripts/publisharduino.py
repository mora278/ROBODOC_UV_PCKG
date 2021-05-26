#!/usr/bin/env python

import rospy
from std_msgs.msg import Int32
from std_msgs.msg import String

#### GLOBAL VARIABLES ####
motor_vel = Int32() #Motor velocity Int32 ROS message


def pressed_key_cb(key_msg):
    global motor_vel
    
    if key_msg.data == 'w': 
        motor_vel = 1
        print(motor_vel)
    elif key_msg.data == 'd': 
        motor_vel = 2
        print(motor_vel)
    elif key_msg.data == 'x' or key_msg.data== '0': 
        motor_vel = 5
        print(motor_vel)
    elif key_msg.data == 'a': 
        motor_vel = 4
        print(motor_vel)
    elif key_msg.data == 's': 
        motor_vel = 3
        print(motor_vel)
    elif key_msg.data == 'o': 
        motor_vel = 6
        print(motor_vel)
    elif key_msg.data == 'p': 
        motor_vel = 7
        print(motor_vel)
    else: 
        print("invalid key")

    

def MotorController():
    #########Init the node ################
    rospy.init_node("motor_controller", anonymous=True)
    print("Node initialized")
    ############ CONSTANTS ################
    global motor_vel
    ####    PUBLISHERS    ####
    print("Setting publishers...")
    pub_motor_vel = rospy.Publisher('arduino/motor_vel', Int32, queue_size=1)
    print("Publishers ok")
    print("Starting Node...")

    ####    SUBSCRIBERS    ####
    rospy.Subscriber("pressed_key", String, pressed_key_cb)
    r = rospy.Rate(10) #rate in Hz
    
    while not rospy.is_shutdown():
        pub_motor_vel.publish(motor_vel) #publish the number
        r.sleep()




############################### MAIN PROGRAM ####################################

if __name__ == "__main__":
    try:
        MotorController()
    except:
        rospy.logfatal("motor_controller died")