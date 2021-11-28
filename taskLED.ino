void TaskLED( void *pvParameters __attribute__((unused)) )  // Manages the LED
{
  for (;;) // A Task shall never return or exit.
  {
    digitalWrite (PIN_LEDred, g.LEDred);
    digitalWrite (PIN_LEDgreen, g.LEDgreen);
    digitalWrite (PIN_LEDblue, g.LEDblue);
  
    vTaskDelay(1); 
  }
}
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
void LEDoff() {
  g.LEDred=0;
  g.LEDgreen=0;
  g.LEDblue=0;  
}
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
void LEDred() {
  g.LEDred=1;
  g.LEDgreen=0;
  g.LEDblue=0;  
}

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
void LEDgreen() {
  g.LEDred=0;
  g.LEDgreen=1;
  g.LEDblue=0;  
}

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
void LEDblue() {
  g.LEDred=0;
  g.LEDgreen=0;
  g.LEDblue=1;  
}
