void TaskControlMotor( void *pvParameters __attribute__((unused)) )  // This is a Task to control motor.
{
  for (;;)
  {
      switch (g.driveState){
            case Forward:
              forward();
              break;
            case ForwardTracking:
              forwardTracking();
              break;
            case Reverse:
              reverse();
              break;
            case Paused:
              stopRobot();
              break;
            case SearchRight:
              searchRight();
              break;
            case SearchLeft:
              searchLeft();
              break;
            default:
              ;
          }
      switch (g.turnState){
        case Left:
          left(TURN_TIME);
          break;
        case Right:
          right(TURN_TIME);
          break;
        default:
          ;
      } 
     vTaskDelay(1); 
  }
}

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
void forward() {
    digitalWrite (PIN_Direction1, 0);
    digitalWrite (PIN_Direction2, 0);
    if (g.sonarDistance > WARNDIST2){     
      g.leftSpeed = g.currentSpeed;       
      g.rightSpeed = g.currentSpeed;
      
      analogWrite (PIN_PWM1, g.leftSpeed);
      analogWrite (PIN_PWM2, g.rightSpeed);
    }
}

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
void forwardTracking() {
    digitalWrite (PIN_Direction1, 0);
    digitalWrite (PIN_Direction2, 0);
    if (g.sonarDistance > WARNDIST2){  // Perform PID algorithm.   
      if (g.currentSpeed == FAST_SPEED){
        headingLoopFast.update(g.error);
        g.leftSpeed = headingLoopFast.m_command;
        g.rightSpeed =-headingLoopFast.m_command;
      }
      else{
        if (g.currentSpeed == MOVE_SPEED){
         headingLoopMove.update(g.error);
         g.leftSpeed = headingLoopMove.m_command;
         g.rightSpeed =-headingLoopMove.m_command;
        }
         else{
         headingLoopSlow.update(g.error);
         // separate heading into left and right delta wheel velocities
         g.leftSpeed = headingLoopSlow.m_command;
         g.rightSpeed =-headingLoopSlow.m_command;
         }
      }
      
  
      g.leftSpeed += g.currentSpeed;                      //Calculate the total left side speed
      g.rightSpeed += g.currentSpeed;                     //Calculate the total right side speed
      
     
    //Serial.println(String()+g.leftSpeed+","+g.rightSpeed);
      analogWrite (PIN_PWM1, g.leftSpeed);
      analogWrite (PIN_PWM2, g.rightSpeed);
    }
}
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
void reverse() {
  digitalWrite (PIN_Direction1, 1);
  digitalWrite (PIN_Direction2, 1);
  g.leftSpeed = g.currentSpeed;
  g.rightSpeed = g.currentSpeed;
  analogWrite (PIN_PWM1, g.leftSpeed);
  analogWrite (PIN_PWM2, g.rightSpeed);
 }

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
void stopRobot() {
  digitalWrite (PIN_PWM1, 0);
  digitalWrite (PIN_PWM2, 0);
  g.leftSpeed = 0;
  g.rightSpeed = 0;
}

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
void left(int8_t turnTime) {
  g.turnState = Straight;
  if (g.driveState != Paused){
      if (g.driveState != Reverse){
        analogWrite (PIN_PWM1, g.currentSpeed-(g.currentSpeed/TURN_SPEED_DELTA));
        analogWrite (PIN_PWM2, g.currentSpeed+(g.currentSpeed/TURN_SPEED_DELTA));
      } 
      else{
        analogWrite (PIN_PWM1, g.currentSpeed+(g.currentSpeed/TURN_SPEED_DELTA));
        analogWrite (PIN_PWM2, g.currentSpeed-(g.currentSpeed/TURN_SPEED_DELTA));
      }
    }
      else {
      digitalWrite (PIN_Direction1, 1);
      digitalWrite (PIN_Direction2, 0);
      analogWrite (PIN_PWM1, MOVE_SPEED);
      analogWrite (PIN_PWM2, MOVE_SPEED);
      }
    vTaskDelay( pdMS_TO_TICKS(turnTime) );
}
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
void right(int8_t turnTime) {
  g.turnState = Straight;
  if (g.driveState != Paused){
      if (g.driveState != Reverse){
        analogWrite (PIN_PWM1, g.currentSpeed+(g.currentSpeed/TURN_SPEED_DELTA));
        analogWrite (PIN_PWM2, g.currentSpeed-(g.currentSpeed/TURN_SPEED_DELTA));
      } 
      else{
        analogWrite (PIN_PWM1, g.currentSpeed-(g.currentSpeed/TURN_SPEED_DELTA));
        analogWrite (PIN_PWM2, g.currentSpeed+(g.currentSpeed/TURN_SPEED_DELTA));
      }
    }
    else {
      digitalWrite (PIN_Direction1, 0);
      digitalWrite (PIN_Direction2, 1);
      analogWrite (PIN_PWM1, MOVE_SPEED);
      analogWrite (PIN_PWM2, MOVE_SPEED);
    }
    vTaskDelay( pdMS_TO_TICKS(turnTime) );
}

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
void searchLeft() {
  digitalWrite (PIN_Direction1, 1);
  digitalWrite (PIN_Direction2, 0);
  g.leftSpeed = SEARCH_SPEED;
  g.rightSpeed = SEARCH_SPEED;
  analogWrite (PIN_PWM1, g.leftSpeed);
  analogWrite (PIN_PWM2, g.rightSpeed);
 }

 //++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
void searchRight() {
  digitalWrite (PIN_Direction1, 0);
  digitalWrite (PIN_Direction2, 1);
  g.leftSpeed = SEARCH_SPEED;
  g.rightSpeed = SEARCH_SPEED;
  analogWrite (PIN_PWM1, g.leftSpeed);
  analogWrite (PIN_PWM2, g.rightSpeed);
 }
