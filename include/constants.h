#ifndef CONSTANTS
#define CONSTANTS

// Change pins
#define BELT_EN 17      // 17
#define BELT_FORWARD 0  // 0
#define BELT_BACK 16    // 16
#define LED 22
#define PUMP_EN 32
#define PUMP_FORWARD 33
#define PUMP_BACK 25
#define SENSOR_MILK 35      // 34
#define SENSOR_CEREAL_1 34  // 35
#define SENSOR_CEREAL_2 39  // 39
#define SERVO_CEREAL_1 27
#define SERVO_CEREAL_2 26

// PWM channels, resolution and frequency
#define BELT 0
#define PUMP 1
#define FREQ 400
#define RES 8

// Adjust sensor sensitivity, servo defaults and engine speeds (0-100 scale)
#define BELT_SPEED 80
#define SERVO1_DEFAULT 115
#define SERVO2_DEFAULT 100
#define SENSOR_SENSITIVITY 3000

// LEDs
#define LED_COUNT 24
#define LED_START 3
#define LED_MILK 5
#define LED_CEREAL_1 6
#define LED_CEREAL_2 8
#define LED_CEREAL_3 10

// Screen, better to not touch
#define BUTTON_W 135
#define BUTTON_H 110
#define NAV_BUTTON_W 100
#define NAV_BUTTON_H 60
#define OK_BUTTON_W 180
#define OK_BUTTON_H 180

#endif