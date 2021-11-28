void TaskIRRcv( void *pvParameters __attribute__((unused)) )  // This is a Task to read the keypad
{

  for (;;)
{
    //Serial.print(F("made it to IR task "));
    if (IrReceiver.decode()) {
      //IrReceiver.printIRResultShort(&Serial);
      g.IRKeypress = IrReceiver.decodedIRData.command;
      //IrReceiver.resume(); // Enable receiving of the next value
    }
  else {
    g.IRKeypress = -1;
  }
  //Serial.println(String()+F("keypress =")+g.IRKeypress);
  switch (g.IRKeypress) {
  case 0x74:  //up arrow = forward
  //Serial.println(F("made it to decoded forward button "));
    g.driveState = Forward;
    break;
  case 0x34:  //left arrow = left
    g.turnState = Left;
    break;
  case 0x33:  //right arrow = right
    g.turnState = Right;
    break;
  case 0x75: //down arrow = reverse
    g.driveState = Reverse;
    break;
  case 0x65: //select = stop
    g.driveState = Paused;
    Serial.println(F("made it to decoded pause button "));
    break;
  case 0x2: //"3" = Learn
    stopRobot();
    g.driveState = Paused;
    huskylens.writeForget(); //Reset algorithm
    huskylens.writeLearn(1); //learn new object
    break;
  case 0x5: //"6" = Search
    g.driveState=Search;
    break;
  default: 
    ;
  }
  
  IrReceiver.resume(); // Enable receiving of the next value
    vTaskDelay(1);
 }  
}

  
