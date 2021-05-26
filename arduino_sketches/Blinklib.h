#ifndef BLINKLIB_H
#define BLINKLIB_H

#include <Arduino.h>
#include <ros.h>
#include <std_msgs/String.h>
#include <std_msgs/Int32.h>
#include <Adafruit_NeoPixel.h>

#define MOT1_IN1 8 //IN1 of the L298 should be connected to this arduino pin
#define MOT1_IN2 7 //IN2 of the L298 should be connected to this arduino pin
#define MOT1_EN  9 //enable A right motor
#define MOT2_IN1 4 //IN3 of the L298 should be connected to this arduino pin
#define MOT2_IN2 2 //IN4 of the L298 should be connected to this arduino pin
#define MOT2_EN  3 //enable B left right

void init_pixel();

void messageCb(const std_msgs::String& command);

void motor_vel_cb(const std_msgs::Int32 & msg);

void idle_state();

void sim_scan();

void sim_clean();

void sim_stop();

void turn_off();

uint32_t Wheel(byte WheelPos);

uint32_t PurpleWheel(byte WheelPos);

void motor_stop();

void motor_forward(unsigned int vel);

void motor_backwards(unsigned int vel);

void motor_left(unsigned int vel);

void motor_right(unsigned int vel);

#endif
