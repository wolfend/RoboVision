#include <Arduino_FreeRTOS.h>
//#include <semphr.h>  // add the FreeRTOS functions for Semaphores (or Flags).

#include "PIDLoop.h"
#include "HUSKYLENS.h"
#include "roboVision.h"
#include "SoftwareSerial.h"
#include <IRremote.hpp>




/* define Tasks */
void TaskSonar( void *pvParameters );
void TaskControlMotor( void *pvParameters );
void TaskIRRcv( void *pvParameters );
void TaskHuskyLens( void *pvParameters );
void TaskLED( void *pvParameters );


/*Here is where the executable program starts*/
// the setup function runs once when you press reset or power the board
void setup() {

  pinMode(PIN_PWM1, OUTPUT);
  pinMode(PIN_PWM2, OUTPUT);
  pinMode(PIN_Direction1, OUTPUT);
  pinMode(PIN_Direction2, OUTPUT);
  pinMode(PIN_LEDred, OUTPUT);
  pinMode(PIN_LEDgreen, OUTPUT);
  pinMode(PIN_LEDblue, OUTPUT);
  pinMode(PIN_Sonar, INPUT);
  pinMode(PIN_SYSMODE, INPUT_PULLUP);
  
  
  initSonarAvg ();
  stopRobot();
  g.driveState = Paused;
  g.turnState = Straight;
  g.inTrack = false;
  g.IRKeypress = 0;
  Serial.begin(115200);
  Wire.begin();
  IrReceiver.begin(PIN_IRrcvr, ENABLE_LED_FEEDBACK); // Start the receiver
  Serial.print(F("Ready to receive IR signals of protocols: "));
  printActiveIRProtocols(&Serial);
  Serial.print(F("at pin "));
  Serial.println(PIN_IRrcvr);
  
  while (!huskylens.begin(Wire))
    {
        Serial.println(F("Begin failed!"));
        Serial.println(F("1.Please recheck the \"Protocol Type\" in HUSKYLENS (General Settings>>Protol Type>>I2C)"));
        Serial.println(F("2.Please recheck the connection."));
        delay(100);
    }
  int mode = digitalRead(PIN_SYSMODE);
  if ( mode == 1){
  Serial.println(F("linefollowingmode"));
  g.visionModeCurrent = lineFollowing;
  g.visionModeNew = lineFollowing;
  huskylens.writeAlgorithm(ALGORITHM_LINE_TRACKING); //Switch the algorithm to line tracking.
} else {
 Serial.println(F("object tracking mode"));
 g.visionModeCurrent = objectTracking;
 g.visionModeNew = objectTracking;
 huskylens.writeAlgorithm(ALGORITHM_OBJECT_TRACKING); //Switch the algorithm to object tracking.
 } 
  // Now set up the Tasks to run independently.
  
  xTaskCreate(
    TaskSonar
    ,  "ReadSonarSensor"  // A name just for humans
    ,  128  // This stack size can be checked & adjusted by reading the Stack Highwater
    ,  NULL
    ,  0  // Priority, with 3 (configMAX_PRIORITIES - 1) being the highest, and 0 being the lowest.
    ,  NULL );

  xTaskCreate(
    TaskControlMotor
    ,  "controlMotor"
    ,  128  // Stack size
    ,  NULL
    ,  2  // Priority
    ,  NULL );

  xTaskCreate(
    TaskHuskyLens
    ,  "AI Vision"
    ,  128  // Stack size
    ,  NULL
    ,  3  // Priority
    ,  NULL );

   
    xTaskCreate(
    TaskLED
    ,  "RGB LED"
    ,  128  // Stack size
    ,  NULL
    ,  0  // Priority
    ,  NULL );

    xTaskCreate(
    TaskIRRcv
    ,  "process IR receiver"
    ,  128  // Stack size
    ,  NULL
    ,  1  // Priority
    ,  NULL );
      
  // Now the Task scheduler, which takes over control of scheduling individual Tasks, is automatically started.
}

void loop()
{
 ; //nothing to do here, work done in tasks
}
