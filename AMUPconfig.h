/*
 AirSensor.h - Library for the AMUP Air Sensor.
 Created by Julio Terra, June 2, 2011.
 */

#ifndef config_h
#define AirSensor_h

#include "WProgram.h"

/** \file
  Configuration for AMUP sketches. This file holds constants that define variables that are used across multiple.  
 
 */

// LED Related Constants
#define RGB_COUNT           3   // holds the number of led pins associated to each light (set to three as default)
#define R                   0
#define G                   1
#define B                   2
#define LED_MAX_BRIGHT      1000

// AIR Sensor Message Init and Lock Flags
#define AIR_CONNECT_CHAR     'c'
#define AIR_LOCK_ON_CHAR     '<'
#define AIR_LOCK_OFF_CHAR    '>'

#define OUTPUT_MIN            0
#define OUTPUT_MAX            127


#endif