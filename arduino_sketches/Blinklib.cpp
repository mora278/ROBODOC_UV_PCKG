#include "Blinklib.h"
#include <ros.h>
#include <std_msgs/String.h>
#include <std_msgs/Int32.h>
#include <Adafruit_NeoPixel.h>


int PIN=12; //Pin donde está conectada la tira de leds
int NUMPIXELS=148; //Número de leds conectados

Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

String cmds[5] = {"idle","scan", "clean", "stop", "end"};

volatile int motor_vel = 40; //The motor velocity between -255->full speed backwards and 255-> Full speed forward

int motor_opt;
int motor_max = 150;
int motor_min = 10;
void init_pixel(){
  pixels.begin(); // Inicialización
  pixels.show(); // Inicialitza tots els pixels apagats
}

void messageCb(const std_msgs::String& command){
  String cmd = command.data;
  if (cmd.equals(cmds[0]))
    idle_state();
  else if (cmd.equals(cmds[1]))
    sim_scan();
  else if (cmd.equals(cmds[2]))
    sim_clean();
  else if (cmd.equals(cmds[3]))
    sim_stop();
  else if (cmd.equals(cmds[4]))
    turn_off();
}

void motor_vel_cb(const std_msgs::Int32 & msg) {
  motor_opt = msg.data;
  if (motor_opt == 1)
    motor_forward((unsigned int) motor_vel);
  else if (motor_opt == 3) 
    motor_backwards((unsigned int) -1*motor_vel);
  else if(motor_opt == 4)
    motor_left((unsigned int) motor_vel);
  else if(motor_opt == 2)
    motor_right((unsigned int) motor_vel);
  else if(motor_opt == 7)
        if(motor_vel < motor_max)
        motor_vel = motor_vel + 10;
    else
        motor_vel = motor_max;
    
  else if(motor_opt == 6)
    if(motor_vel > motor_min)
        motor_vel = motor_vel - 10;
    else
        motor_vel = motor_min;
  else if(motor_opt == 5)
    motor_stop();
  else 
    motor_stop();
}

//------------------------------------------------------------------
// Function for idle state
//------------------------------------------------------------------
void idle_state() {
  uint8_t wait = 50;
  uint16_t i, j;

  for(j=0; j<256; j++) {
    for(i=0; i<pixels.numPixels(); i++) {
      pixels.setPixelColor(i, Wheel((i+j) & 255));
    }
    pixels.show();
    delay(wait);
  }
}
//------------------------------------------------------------------

//------------------------------------------------------------------
// Function for simulate room scanning
//------------------------------------------------------------------
void sim_scan() {
  uint8_t wait = 120;
  uint16_t i, j;
    
  for(i=0; i<pixels.numPixels(); i++) {
    pixels.setPixelColor(i, pixels.Color(0,255,0));
  }
  pixels.show();
  delay(wait);
  
  for(i=0; i<pixels.numPixels(); i++) {
    pixels.setPixelColor(i, pixels.Color(0,0,0));
  }
  pixels.show();
  delay(wait);
}
//------------------------------------------------------------------

//------------------------------------------------------------------
// Function for simulating UV application
//------------------------------------------------------------------
void sim_clean() {
  uint8_t wait = 10;
  uint16_t i, j;
  
  for(j=0; j<256; j++) {
    for(i=0; i<pixels.numPixels(); i++) {
      pixels.setPixelColor(i, PurpleWheel((i+j) & 255));
    }
    pixels.show();
    delay(wait);
  }
}
//------------------------------------------------------------------

//------------------------------------------------------------------
// Function for simulate emergency stop
//------------------------------------------------------------------
void sim_stop() {
  uint8_t wait = 30;
  uint16_t i, j;
    
  for(i=0; i<pixels.numPixels(); i++) {
    pixels.setPixelColor(i, pixels.Color(255,0,0));
  }
  pixels.show();
  delay(wait);
  
  for(i=0; i<pixels.numPixels(); i++) {
    pixels.setPixelColor(i, pixels.Color(0,0,0));
  }
  pixels.show();
  delay(wait);
}
//------------------------------------------------------------------

//------------------------------------------------------------------
// Function for turning off leds
//------------------------------------------------------------------
void turn_off() {
  uint16_t i, j;
  
  for(j=0; j<256; j++) {
    for(i=0; i<pixels.numPixels(); i++) {
      pixels.setPixelColor(i, 0);
    }
    pixels.show();
  }  
}
//------------------------------------------------------------------

//------------------------------------------------------------------
// Function for color generation
//------------------------------------------------------------------
// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t Wheel(byte WheelPos) {
  WheelPos = 255 - WheelPos;
  if(WheelPos < 85) {
    return pixels.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  }
  if(WheelPos < 170) {
    WheelPos -= 85;
    return pixels.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
  WheelPos -= 170;
  return pixels.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
}

uint32_t PurpleWheel(byte WheelPos) {
  // Blue
  if(WheelPos < 128) {
    WheelPos = WheelPos / 1;
    return pixels.Color(128 + WheelPos, 0, 255);
  }
  //Red   
  WheelPos = (WheelPos  - 128)/ 1;
  return pixels.Color(255, 0, 255 - WheelPos);
}
//------------------------------------------------------------------

/* 
 * Stop the motor
 */
void motor_stop() {
  //Stop if received an wrong direction
    digitalWrite(MOT1_IN1, 0);
    digitalWrite(MOT1_IN2, 0);
    analogWrite(MOT1_EN, 0);
    digitalWrite(MOT2_IN1, 0);
    digitalWrite(MOT2_IN2, 0);
    analogWrite(MOT2_EN, 0);
}

/* Moves the motor in positive sens
    vel: [0-255] the desired pwm value 255 means full speed
 */
void motor_forward(unsigned int vel) {
    digitalWrite(MOT1_IN1, 1);
    digitalWrite(MOT1_IN2, 0);
    analogWrite(MOT1_EN, vel);
    digitalWrite(MOT2_IN1, 1);
    digitalWrite(MOT2_IN2, 0);
    analogWrite(MOT2_EN, vel);
}

/* Moves the motor backwards
    vel: [0-255] the desired pwm value 255 means full speed
 */
void motor_backwards(unsigned int vel) {
    digitalWrite(MOT1_IN1, 0);
    digitalWrite(MOT1_IN2, 1);
    analogWrite(MOT1_EN, vel);
    digitalWrite(MOT2_IN1, 0);
    digitalWrite(MOT2_IN2, 1);
    analogWrite(MOT2_EN, vel);
}

void motor_left(unsigned int vel) {
    digitalWrite(MOT1_IN1, 0);
    digitalWrite(MOT1_IN2, 0);
    analogWrite(MOT1_EN, vel);
    digitalWrite(MOT2_IN1, 1);
    digitalWrite(MOT2_IN2, 0);
    analogWrite(MOT2_EN, vel);
}

void motor_right(unsigned int vel) {
    digitalWrite(MOT1_IN1, 1);
    digitalWrite(MOT1_IN2, 0);
    analogWrite(MOT1_EN, vel);
    digitalWrite(MOT2_IN1, 0);
    digitalWrite(MOT2_IN2, 0);
    analogWrite(MOT2_EN, vel);
}







