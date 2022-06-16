/********************************************************************************/
/*   Author  : Ahmed Farag & Eslam                                              */
/*   Date    : 3/06/2022                                                        */
/*   Version : V01                                                              */
/********************************************************************************/

#ifndef _KELLY_INTERFACE_H
#define _KELLY_INTERFACE_H

// Channel zero for the x2 switch in the RC remote
#define X2_RC_CH 0

// Throttle pin for steering
#define STEERING_RIGHT_PIN 13
#define STEERING_LEFT_PIN 13

/* Function prototypes */
void KELLY_voidInit();
void KELLY_voidSteeringRC(u16 copy_u8RCReadings);
void KELLY_voidRight(u16 RC_Readings, u8 Throttle_Pin, u16 RC_Min_Readings, u16 RC_Max_Readings, u8 Min_Pulse_Count, u16 Max_Pulse_Count);
void KELLY_voidLeft(s16 RC_Readings, u8 Throttle_Pin, u16 RC_Min_Readings, u16 RC_Max_Readings, u8 Min_Pulse_Count, s16 Max_Pulse_Count);
void KELLY_voidSetPosition(bool Copy_BoolDirection, bool Copy_BoolState);
void KELLY_voidResetToZero();

#endif