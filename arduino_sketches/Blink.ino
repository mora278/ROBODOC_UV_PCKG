#include "Blinklib.h"


#include <ros.h>
#include <std_msgs/String.h>
#include <std_msgs/Int32.h>

ros::NodeHandle  nh;

ros::Subscriber<std_msgs::String> sub("toggle_led", &messageCb );
ros::Subscriber<std_msgs::Int32> motor_vel_sub("arduino/motor_vel", motor_vel_cb);

void setup()
{ 
  pinMode(LED_BUILTIN, OUTPUT);
  
  pinMode(MOT1_IN1, OUTPUT);
  pinMode(MOT1_IN2, OUTPUT);
  pinMode(MOT1_EN, OUTPUT);
  pinMode(MOT2_IN1, OUTPUT);
  pinMode(MOT2_IN2, OUTPUT);
  pinMode(MOT2_EN, OUTPUT);
  
  nh.initNode();
  nh.subscribe(sub);
  init_pixel();

  nh.subscribe(motor_vel_sub);
}

void loop()
{  
  nh.spinOnce();
  delay(1);
}
