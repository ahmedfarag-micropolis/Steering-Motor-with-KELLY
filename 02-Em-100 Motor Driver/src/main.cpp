/********************************************************************************/
/*   Author  : Ahmed Farag & Eslam                                              */
/*   Date    : 3/06/2022                                                        */
/*   Version : V01                                                              */
/********************************************************************************/

// Includes Libs
#include <STD_TYPES.h>
#include "SBUS.h"
#include <Arduino.h>

// Include drivers of lower layers
#include <KELLY_interface.h>
#include <KELLY_config.h>

u16 channels[16];
bool failSafe;
bool lostFrame;
u8 c;
u16 RPM;
u16 RC_Steering_Readings;

// a SBUS object, which is on hardware
// serial port 1
SBUS x8r(Serial1);

void setup()
{

  KELLY_voidInit();

  // begin the SBUS communication for the RC
  x8r.begin();
  // Begin the serial communication
  Serial.begin(9600);
}

void loop()
{

  if (x8r.read(&channels[0], &failSafe, &lostFrame))
    ;

  RC_Steering_Readings = channels[X2_RC_CH];
  KELLY_voidSteeringRC(RC_Steering_Readings);
}
