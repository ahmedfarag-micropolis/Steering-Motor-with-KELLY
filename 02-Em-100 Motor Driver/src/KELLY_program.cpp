/********************************************************************************/
/*   Author  : Ahmed Farag & Eslam                                              */
/*   Date    : 3/06/2022                                                        */
/*   Version : V01                                                              */
/********************************************************************************/

// Includes
#include <Arduino.h>
#include <STD_TYPES.h>

#include <KELLY_interface.h>
#include <KELLY_config.h>

// Global variables
bool PulseValCurrentU = digitalRead(HALL_SENSOR_U); // Set the U sensor value as boolean and read initial state
bool PulseValPrevU;                                 // Variable to save the state of the previous pulse
int pulseCount;                                     // Variable to store the count of the pulses
u8 PrevMappedCount;                                 // Variable to store the value of the previous mapped value from the RC to get the direction
s16 MappedPulseCount;                               // Variable to store the value of the mapping from the RC values to 0 -> 128 which represents one complete revolution of the output shaft

// initialization function
void KELLY_voidInit()
{
  // Set the Throotle pin of the Right direction to output
  pinMode(STEERING_RIGHT_PIN, OUTPUT);
  // Set the Throotle pin of the Left direction to output
  pinMode(STEERING_LEFT_PIN, OUTPUT);
  // Set the Reverse Switch  to output
  pinMode(REVERSE_STEERING_SWITCH, OUTPUT);
  // Set the pin that will read the values from the input U hall sensor to Input
  pinMode(HALL_SENSOR_U, INPUT);
  // Set Reverse pin to low in initialization
  digitalWrite(REVERSE_STEERING_SWITCH, LOW);
}

// Function for the RC control for the steering driver
void KELLY_voidSteeringRC(u16 copy_u8RCReadings)
{

  if ((copy_u8RCReadings > 1002) && (copy_u8RCReadings <= 1722))
  {
    // Call the KELLY Right function to move the steering motor to the right position
    KELLY_voidRight(copy_u8RCReadings, STEERING_RIGHT_PIN, THROTTLE_MIN_READINGS, THROTTLE_MAX_READINGS, MIN_NUMBER_PULSES_R, MAX_NUMBER_PULSES_R);
  }

  else if (copy_u8RCReadings == 1002)
  {
    // call the function to reset the position of the shaft to zero
    KELLY_voidResetToZero();
    Serial.printf("pulseCount Zero %d  \n", pulseCount);
  }

  else if ((copy_u8RCReadings >= 282) && (copy_u8RCReadings < 1002))
  {
    // Call the KELLY Left function to move the steering motor to the Left position
    KELLY_voidLeft(copy_u8RCReadings, STEERING_LEFT_PIN, THROTTLE_MIN_READINGS_REVERSE, THROTTLE_MAX_READINGS_REVERSE, MAX_NUMBER_PULSES_L, MIN_NUMBER_PULSES_L);
  }
}

// KELLY right function that will move the shaft to the right direction
void KELLY_voidRight(u16 RC_Readings, u8 Throttle_Pin, u16 RC_Min_Readings, u16 RC_Max_Readings, u8 Min_Pulse_Count, u16 Max_Pulse_Count)
{
  MappedPulseCount = map(RC_Readings, RC_Min_Readings, RC_Max_Readings, Min_Pulse_Count, Max_Pulse_Count);
  Serial.printf("MappedPulseCount Right  %d  \n", MappedPulseCount);
  Serial.printf("pulseCount  %d  \n", pulseCount);

  if (pulseCount < MappedPulseCount)
  {

    KELLY_voidSetPosition(LOW, HIGH);
  }
  else if (pulseCount > MappedPulseCount)
  {
    KELLY_voidSetPosition(HIGH, LOW);
  }

  else if (pulseCount == MappedPulseCount)
  {
    analogWrite(STEERING_RIGHT_PIN, 1);
  }
}

// KELLY left function that will move the shaft to the left direction
void KELLY_voidLeft(s16 RC_Readings, u8 Throttle_Pin, u16 RC_Min_Readings, u16 RC_Max_Readings, u8 Min_Pulse_Count, s16 Max_Pulse_Count)
{
  MappedPulseCount = map(RC_Readings, RC_Min_Readings, RC_Max_Readings, Min_Pulse_Count, Max_Pulse_Count);
  Serial.printf("MappedPulseCount Left %d  \n", MappedPulseCount);
  Serial.printf("pulseCount  %d  \n", pulseCount);

  if (pulseCount > MappedPulseCount)
  {
    KELLY_voidSetPosition(HIGH, LOW);
  }
  else if (pulseCount == MappedPulseCount)
  {
    analogWrite(STEERING_RIGHT_PIN, 1);
  }

  else if (pulseCount < MappedPulseCount)
  {
    KELLY_voidSetPosition(LOW, HIGH);
  }
  PrevMappedCount = MappedPulseCount;
}

// KELLY function that will make the shaft get back to the same position after calling the right or the left functions
void KELLY_voidSetPosition(bool Copy_BoolDirection, bool Copy_BoolState)
{

  digitalWrite(REVERSE_STEERING_SWITCH, Copy_BoolDirection ? HIGH : LOW);
  analogWrite(STEERING_RIGHT_PIN, STEERING_MAX_SPEED_RIGHT);
  PulseValCurrentU = digitalRead(HALL_SENSOR_U);

  if (PulseValCurrentU != PulseValPrevU)
  {
    pulseCount = Copy_BoolState ? pulseCount + 1 : pulseCount - 1;
    PulseValPrevU = PulseValCurrentU;
  }
}

// KELLY reset to zero function that will reset the shaft to it's zero position if the throttle is left suddenly
void KELLY_voidResetToZero()
{
  if (pulseCount > 0)
  {

    KELLY_voidSetPosition(HIGH, LOW);
  }

  else if (pulseCount < 0)
  {

    KELLY_voidSetPosition(LOW, HIGH);
  }

  else if (pulseCount == 0)
  {
    analogWrite(STEERING_RIGHT_PIN, 1);
    Serial.printf("pulseCount Zero %d  \n", pulseCount);
  }
}