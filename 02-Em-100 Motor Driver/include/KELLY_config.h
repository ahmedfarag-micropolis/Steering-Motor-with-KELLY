/********************************************************************************/
/*   Author  : Ahmed Farag & Eslam                                              */
/*   Date    : 3/06/2022                                                        */
/*   Version : V01                                                              */
/********************************************************************************/

// File Gurard
#ifndef _KELLY_CONFIG_H
#define _KELLY_CONFIG_H

// RC Min and Max limits
#define THROTTLE_MIN_READINGS 1004
#define THROTTLE_MAX_READINGS 1722
#define THROTTLE_MIN_READINGS_REVERSE 1000
#define THROTTLE_MAX_READINGS_REVERSE 282

// Right steering limits
#define MIN_NUMBER_PULSES_R 0
#define MAX_NUMBER_PULSES_R 128
#define STEERING_MAX_SPEED_RIGHT 80

// Left steering limits
#define MIN_NUMBER_PULSES_L -128
#define MAX_NUMBER_PULSES_L 0
#define STEERING_MAX_SPEED_LEFT 80

// Hall Sensors Input Pins
#define HALL_SENSOR_U 39

// Reverse Switch for steering
#define REVERSE_STEERING_SWITCH 33

// End of file guard
#endif