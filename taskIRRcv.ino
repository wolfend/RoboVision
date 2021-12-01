void TaskIRRcv( void *pvParameters __attribute__((unused)) )  // This is a Task to read the keypad
{

  for (;;)
{
    if (IrReceiver.decode()) {
      //IrReceiver.printIRResultShort(&Serial);
      if (IrReceiver.decodedIRData.protocol == SONY)
        g.IRKeypress = IrReceiver.decodedIRData.command;
      else
        g.IRKeypress = -1;  
      //IrReceiver.resume(); // Enable receiving of the next value
    } 
  else {
    g.IRKeypress = -1;
  }
  //Serial.println(String()+F("keypress =")+g.IRKeypress);
  switch (g.IRKeypress) {
  case 0x74:  //up arrow = forward
    g.driveState = Forward;
    break;
  case 0x15:  //Power = forwardTracking
    g.driveState = ForwardTracking;
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
    //Serial.println(F("made it to decoded pause button "));
    break;
  case 0x10: //"Channel +" = Search Right
    g.driveState=SearchRight;
    break;
  case 0x12: //"Volume +" = Search Left
    g.driveState=SearchLeft;
    break; 
  case 0x06: //"7" = Slow speed
    g.currentSpeed=SLOW_SPEED;
    break; 
  case 0x07: //"8" = Normal speed
    g.currentSpeed=MOVE_SPEED;
    break;
  case 0x08: //"9" = High speed
    g.currentSpeed=FAST_SPEED;
    break;
  default: 
    ;
  }
  
  IrReceiver.resume(); // Enable receiving of the next value
    vTaskDelay(1);
 }  
}

  
