void TaskHuskyLens( void *pvParameters __attribute__((unused)) )  // This is a Task to read Husky Lens
{
  for (;;) // A Task shall never return or exit.
  {
    if (!huskylens.request(ID1)) {Serial.println(F("Fail to request data from HUSKYLENS, recheck the connection!"));g.driveState=Paused;}
    else if(!huskylens.isLearned()) {Serial.println(F("Nothing learned, press learn button on HUSKYLENS to learn one!"));g.driveState=Paused;}
    else if(!huskylens.available()){ 
        Serial.println(F("No block or arrow appears on the screen!"));
        g.inTrack = false;
      }
    else{  //now we are in track
        g.inTrack = true;
        HUSKYLENSResult result = huskylens.read();
        printResult(result);
        if (g.driveState == SearchRight || g.driveState == SearchLeft)
          g.driveState = ForwardTracking;
        // Calculate the error:
        if (g.visionModeCurrent == lineFollowing)
         g.error = (int32_t)result.xTarget - (int32_t)160;
        else { //assume object tracking otherwise
         g.error = (int32_t)result.xCenter - (int32_t)160;
        }
        //Serial.println(String()+g.error);
        
    }
  vTaskDelay(1); //task delay
  }
}
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
void printResult(HUSKYLENSResult result){
    if (result.command == COMMAND_RETURN_BLOCK){
        Serial.println(String()+F("Block:xCenter=")+result.xCenter+F(",yCenter=")+result.yCenter+F(",width=")+result.width+F(",height=")+result.height+F(",ID=")+result.ID);
    }
    else if (result.command == COMMAND_RETURN_ARROW){
        Serial.println(String()+F("Arrow:xOrigin=")+result.xOrigin+F(",yOrigin=")+result.yOrigin+F(",xTarget=")+result.xTarget+F(",yTarget=")+result.yTarget+F(",ID=")+result.ID);
    }
    else{
        Serial.println("Object unknown!");
    }
}
