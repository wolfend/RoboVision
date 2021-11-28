void TaskControlMotor( void *pvParameters __attribute__((unused)) )  // This is a Task to control motor.
{
  for (;;)
  {
      switch (g.driveState){
            case Forward:
              forward();
              break;
            case Reverse:
              reverse();
              break;
            case Paused:
              stopRobot();
              break;
            case Search:
              search();
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
      // Perform PID algorithm.
      headingLoop.update(g.error);
  
      // separate heading into left and right wheel velocities.
      g.leftSpeed = headingLoop.m_command;
      g.rightSpeed =-headingLoop.m_command;
  
      g.leftSpeed += MOVE_SPEED;                      //Calculate the total left side speed
      g.rightSpeed += MOVE_SPEED;                     //Calculate the total right side speed
      //Serial.println(String()+g.leftSpeed+","+g.rightSpeed);
      analogWrite (PIN_PWM1, g.leftSpeed);
      analogWrite (PIN_PWM2, g.rightSpeed);
    }
}

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
void reverse() {
  digitalWrite (PIN_Direction1, 1);
  digitalWrite (PIN_Direction2, 1);
  g.leftSpeed = MOVE_SPEED;
  g.rightSpeed = MOVE_SPEED;
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
        analogWrite (PIN_PWM1, MOVE_SPEED-TURN_SPEED_DELTA);
        analogWrite (PIN_PWM2, MOVE_SPEED+TURN_SPEED_DELTA);
      } 
      else{
        analogWrite (PIN_PWM1, MOVE_SPEED+TURN_SPEED_DELTA);
        analogWrite (PIN_PWM2, MOVE_SPEED-TURN_SPEED_DELTA);
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
        analogWrite (PIN_PWM1, MOVE_SPEED+TURN_SPEED_DELTA);
        analogWrite (PIN_PWM2, MOVE_SPEED-TURN_SPEED_DELTA);
      } 
      else{
        analogWrite (PIN_PWM1, MOVE_SPEED-TURN_SPEED_DELTA);
        analogWrite (PIN_PWM2, MOVE_SPEED+TURN_SPEED_DELTA);
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
void search() {
  digitalWrite (PIN_Direction1, 1);
  digitalWrite (PIN_Direction2, 0);
  g.leftSpeed = SEARCH_SPEED;
  g.rightSpeed = SEARCH_SPEED;
  analogWrite (PIN_PWM1, g.leftSpeed);
  analogWrite (PIN_PWM2, g.rightSpeed);
 }
