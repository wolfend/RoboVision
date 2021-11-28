const int numReadings = 6;
int SonarReadings[numReadings];      // the readings from the analog input
int readIndex = 0;              // the index of the current reading
int SonarTotal = 0;                  // the running total

void TaskSonar( void *pvParameters __attribute__((unused)) )  // Reads the sonar, computes running average into global variable
{
  for (;;) // A Task shall never return or exit.
  {
    
    // subtract the last reading:
    SonarTotal = SonarTotal - SonarReadings[readIndex];
    // read from the sensor:
    SonarReadings[readIndex] = analogRead(PIN_Sonar);
    // add the reading to the total:
    SonarTotal = SonarTotal + SonarReadings[readIndex];
    // advance to the next position in the array:
    readIndex++;
    // if we're at the end of the array...
    if (readIndex >= numReadings) {
    // ...wrap around to the beginning:
    readIndex = 0;
    }

  // calculate the average:
  g.sonarDistance = SonarTotal / numReadings;
  //Serial.println(String()+g.sonarDistance);
  if (g.sonarDistance > SAFE_DIST)
    LEDoff();
  else {
    if (g.sonarDistance > WARNDIST1)
     LEDgreen();
    else {
      if (g.sonarDistance > WARNDIST2)
        LEDblue();
      else {
        LEDred();
        if (g.driveState == Forward){
          g.driveState = Paused;
        }
      }
    }
  }
    vTaskDelay(5); 
  }
}
   

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++   
 // initialize all the readings to 0:
 void initSonarAvg () {
  for (int thisReading = 0; thisReading < numReadings; thisReading++) {
    SonarReadings[thisReading] = 0;
  }
 }
