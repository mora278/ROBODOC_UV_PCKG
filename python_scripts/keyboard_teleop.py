#!/usr/bin/env python 

""" This programs reads the PC keyboard and publishes the value of the pressed key to a ROS topic 

    Published topic 

        /pressed_key 

""" 

import rospy 

from std_msgs.msg import String 

from copy import deepcopy 

import sys, select, termios, tty 

  

msg = """ 

Reading from the keyboard  and Publishing to pressed_key! 

Press any key to publish it as a ROS String message. 

It is designed to use only leters and numbers without special characters 

  

Press CTRL-C or Escape to quit 

""" 

def getKey(): 

    tty.setraw(sys.stdin.fileno()) 

    select.select([sys.stdin], [], [], 0) 

    key = sys.stdin.read(1) 

    termios.tcsetattr(sys.stdin, termios.TCSADRAIN, settings) 

    return key 

  

if __name__ == "__main__": 

    settings = termios.tcgetattr(sys.stdin) 

    rospy.init_node('keyboard_teleop') 

    """ ROS Parameters 

    """ 

    pressed_key_pub = rospy.Publisher('pressed_key', String, queue_size=10) 

    pressed_key_msg=String() 

    try: 

        print msg 

        while(1): 

            key = getKey() 

            print ("hola",key) 

            if (key == '\x03' or key == '\x1B'): #If the user pressed Ctrl+C or Scape finish the program 

                break 

            pressed_key_msg.data=key 

            pressed_key_pub.publish(pressed_key_msg) 

  

    except:

        rospy.logerror("keyboard_teleop.py: exception") 

  

    finally: 

        termios.tcsetattr(sys.stdin, termios.TCSADRAIN, settings) 
