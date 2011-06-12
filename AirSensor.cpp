#include "WProgram.h"
#include "AirSensor.h"

AirSensor::AirSensor(int _pin) {
//AirSensor::AirSensor(int _pin) {
    mainPin = _pin;
    // hand status related variables
    handActive = false;
    handStatusChange = false;
    handIntention = STOPPED;
    handIntentionPrevious = handIntention;
    
    // data input related variables
    newData = false;
    newReading = 0;
    sensorRange = SENSOR_MAX - SENSOR_MIN;
    volumeRange = TOP_VOLUME - VOLUME_MIN;
    
    for (int i = 0; i < READINGS_ARRAY_SIZE; i++) rawReadings[i] = 0;
    for (int i = 0; i < PRE_READING_BUFFER_SIZE; i++) preBuffer[i] = -1;
    
    // gesture capture related variables
    gestOnOff_LastTime = millis(); 
    gestOn = false;
    gestOff = false;
    gestUpDown_Center = 0;
    
    // intialize VOLUME related variables
    masterVolume = 0;
    gestUpDown_Bandwidth = 20;
    gestUpDown_IgnoreRange = 70;
    
//    filteredDataPrevious = 0;
} // *** END CONSTRUCTOR *** //

void AirSensor::reset() {    
    
    for (int i = 0; i < READINGS_ARRAY_SIZE; i++) rawReadings[i] = -1;
    for (int i = 0; i < PRE_READING_BUFFER_SIZE; i++) preBuffer[i] = -1;

} // *** END CONSTRUCTOR *** //


// Set Proximit Pin
void AirSensor::setProximityPin(int _proxPin) {
    mainPin = _proxPin;
}

// *** ADD NEW READING FUNCTION ***
// add new reading into the readings array
void AirSensor::addNewReading() {
    int avgSum = 0;
    int validAvgReadings = 0;
    
    rawReading = analogRead(mainPin);
    
    // ****** PREPARE BUFFER AND READING ARRAYS ****** //   
    // prepare to add new value to arrays - move values back in array by one position, starting at the end of the array and moving to the beginning
    for(int i = READINGS_ARRAY_SIZE-1; i > 0; i--) rawReadings[i] = rawReadings[i-1]; 
    for(int j = PRE_READING_BUFFER_SIZE-1; j > 0; j--) { preBuffer[j] = preBuffer[j-1]; }
    
    // ****** CHECK READING IS WITHIN RANGE AND MAP VALUE ACCORDINGLY ****** //   
    // adjust the value by checking if it is within acceptable range, and adjusting value
    if (rawReading > SENSOR_MIN && rawReading < SENSOR_MAX) { preBuffer[0] = sensorRange - (rawReading - SENSOR_MIN); }
    else if (rawReading < SENSOR_MIN) { preBuffer[0] = -1; }
    else if (rawReading > SENSOR_MAX) { preBuffer[0] = -1; }
    
    // ****** RESORT THE ARRAY WITH THE NEW DATA READING ****** //   
    // array values are resorted from smallest to greatest and then 
    int reorderBuffer[PRE_READING_BUFFER_SIZE];
    for(int j = PRE_READING_BUFFER_SIZE-1; j > 0; j--) { reorderBuffer[j] = -2; }
    
    for(int i = 0; i < PRE_READING_BUFFER_SIZE; i++) {
        int orderCounter = 0;
        int repeatCounter = 0;
        for(int j = 0; j < PRE_READING_BUFFER_SIZE; j++) {
            if(preBuffer[i] < preBuffer[j]) orderCounter++;             
            if(preBuffer[i] == preBuffer[j]) repeatCounter++;             
        }    
        if (repeatCounter == 1) { reorderBuffer[orderCounter] = preBuffer[i]; } 
        else {
            for(int k = 0; k < repeatCounter; k++) {
                if(reorderBuffer[orderCounter + k] == -2) { reorderBuffer[orderCounter + k] = preBuffer[i]; }
            }
        }
    }
    
    int newReading = reorderBuffer[PRE_READING_BUFFER_SIZE/2];
            
    // ****** CHECK HAND ACTIVE STATUS ****** // 
    // check if the hand status has changed
    if (newReading < 0 && handActive == true) {
        handActive = false;
        handStatusChange = true;
    } else if (newReading >= 0  && handActive == false) {
        handActive = true;
        handStatusChange = true;
    }
    
    rawReadings[0] = newReading;
    
} // *** END NEW READING FUNCTION ***


// ***** GESTURE ON AND OFF ***** // 
// Function that identifies gestures that turn on and off the sound of channel
// returns false it has captured an on or off gesture within the pause interval
int AirSensor::gestOnOff() {
    int timeCounter = 0;    // counter that identifies how many readings fit within the gesture interval time
    int onCounter = 0;      // counter that identifies how many readings support an on gesture
    int offCounter = 0;     // counter that identifies how many readings support an off gesture
    gestOn = false;         // boolean variable set to true if ON gesture detected
    gestOff = false;        // boolean variable set to false if OFF gesture detected
    
    // check that an on and off gesture has not been recorded recently 
    if (millis() - gestOnOff_LastTime > gestOnOff_PauseInterval) {
        int counterMin = 4;                        // set minimum number of requirements that need to be met to identify a gesture
        int lookback = READINGS_ARRAY_SIZE - 1;    // set how many readings will be read from the array to identify gesture
        
        // check that the most current and last readings are valid (they do not equal -1)
        if (rawReadings[0] > 0 && rawReadings[lookback] > 0) {
            int fullDelta = rawReadings[0] - rawReadings[lookback];
            if(fullDelta > gestOnOff_FullDelta || fullDelta < (gestOnOff_FullDelta * -1)) {
                
                int noiseThreshold = 2;      // the maximum number of out of order readings for the on/off gesture
                int noiseCount = 0;          // the current count of out of order readings for the on/off gesture
                
                // loop through each element in rawReadings array to see which ones meet requirements
                for (int j = 0; j < lookback; j++) { 
                    int gradientDelta = 0;
                    int offsetCheck = j + 1;
                    
                    if(rawReadings[j] > 0) { 
                        
                        // if rawReadings value at offsetCheck equals less than 0, then loop through array to until you find the next value that is greater than 0 
                        if (rawReadings[offsetCheck] < 0) {
                            for(offsetCheck; offsetCheck <= lookback; offsetCheck++) {
                                if (offsetCheck == lookback) return false;
                                else if (rawReadings[offsetCheck] >= 0) break;
                            }
                        }
                        
                        // if a rawReadings value has been found that is more than or equal to 0 then check if the delta meets requirements 
                        if(rawReadings[offsetCheck] > 0) { 
                            gradientDelta = rawReadings[j] - rawReadings[offsetCheck];
                            if(fullDelta > 0) {
                                if (gradientDelta >= 0 && gradientDelta < gestOnOff_GradientDelta) { onCounter++; } 
                                else if (gradientDelta >= gestOnOff_GradientDelta) { break; }
                                else { noiseCount++; }
                                
                            } else if(fullDelta < 0) {
                                if (gradientDelta <= 0 && gradientDelta > (gestOnOff_GradientDelta * -1)) { offCounter++; } 
                                else if (gradientDelta <= (gestOnOff_GradientDelta * -1)) { break; }
                                else { noiseCount++; }
                            }
                            if (noiseCount >= TREND_NOISE_THRESHOLD) break;  
                        }
                    }
                }
            } 
        }
        
        if (onCounter > TREND_RECOGNITION_MIN) { 
            gestOn = true; 
            masterVolume = TOP_VOLUME;
            gestOnOff_LastTime = millis();
            handIntention = UP;
            return GEST_ON;
        }
        
        if (offCounter > TREND_RECOGNITION_MIN) { 
            gestOff = true; 
            masterVolume = 0;
            gestOnOff_LastTime = millis();
            handIntention = DOWN;
            return GEST_OFF;
        }
        return STOPPED;
    } 
    return STOPPED; 
} // ****** END - GESTURE ON AND OFF ****** //

// ***** GESTURE VOLUME UP AND DOWN ***** // 
int AirSensor::gestUpDown() {
    int gestUpDown_Shift = 0;

    if (rawReadings[0] > 0) {
        if (gestUpDown_Center == -1) { 
            gestUpDown_Center = rawReadings[0];   
            gestUpDown_Shift = 0;
            handIntention = STOPPED;                  
        } else if (rawReadings[0] > (gestUpDown_Center + gestUpDown_Bandwidth)) {
            gestUpDown_Shift = rawReadings[0] - (gestUpDown_Center + gestUpDown_Bandwidth);
            gestUpDown_Center += gestUpDown_Shift; 
            handIntention = UP;
        } else if (rawReadings[0] < (gestUpDown_Center - gestUpDown_Bandwidth)) {
            gestUpDown_Shift = rawReadings[0] - (gestUpDown_Center - gestUpDown_Bandwidth);
            gestUpDown_Center += gestUpDown_Shift; 
            handIntention = DOWN;
        } else {
            gestUpDown_Shift = 0;
            handIntention = STOPPED;                  
        }
    } else {
        gestUpDown_Center = -1;   
        gestUpDown_Shift = 0;
        handIntention = STOPPED;                  
    }  
    return gestUpDown_Shift;
}

// ***** MIDI VOLUME FUNCTIONS ***** // 

// Function calls other two functions that actually handle two main types of gestures - on/off gesture, and smooth up/down gesture
void AirSensor::updateVolumeMIDI() {
    if (!volumeOnOffMIDI()) volumeUpDownMIDI(); 
}


// function that converts up and down gesture values into a MIDI volume between 0 and 127 
void AirSensor::volumeUpDownMIDI() {
    float gestureUpDown = gestUpDown();
    int lastMasterVolume = masterVolume;
    masterVolume += (gestureUpDown / sensorRange) * volumeRange;
//    masterVolume += (gestureUpDown / (TOP_VOLUME)) * TOP_VOLUME;
    if (masterVolume > TOP_VOLUME) masterVolume = TOP_VOLUME;
    else if (masterVolume < 0) masterVolume = 0;
    if(lastMasterVolume != int(masterVolume)) {
        newData = true;
    }
}

// function that converts that converts on and off shift values into a MIDI value between 0 and 127 
boolean AirSensor::volumeOnOffMIDI(){
    int gestureOnOff = gestOnOff();
    if(gestureOnOff == GEST_ON) {
        masterVolume = TOP_VOLUME;
        newData = true;
        return true;
    } else if(gestureOnOff == GEST_OFF) {
        masterVolume = 0;
        newData = true;
        return true;
    }
    return false; 
}

//void AirSensor::printMIDIVolume() {
//    Serial.println(int(masterVolume));
//}

void AirSensor::printRawReadings() {
    Serial.print("raw: ");
    Serial.println(rawReading);
}

// *** ADD NEW TIMED READING ***
// add new reading with a timestamp
int AirSensor::play() {
    if (millis() - lastReading >  timer_interval) {
        addNewReading();
        updateVolumeMIDI();
        if (newData) {
            newData = false;
            Serial.println(int(masterVolume));
            return int(masterVolume);
        }
    }
    return -1;
}





