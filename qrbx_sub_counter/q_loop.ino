//----------------------------------SETUP-----------------------------------------
void setup() {
  Serial.begin(9600); // open serial port 
  Serial.println("Connected to Serial Port");

  initPins(); // set push buttons as input
  connectWifi(); // connect to wifi

  setMode(channelMode);
  P.begin(); // initialize display object
  P.setIntensity(1); // sets brightness (0-15)
  P.displayText(curMessage, scrollAlign, scrollSpeed, scrollPause, scrollEffect, scrollEffect); // curMessage = const char *pText
}

//-----------------------------------LOOP--------------------------------------------
void loop() {
  if (animationDone()) {
    firstTime = 0;
  }

  if (!firstTime) {
    mainLoop();
  }
}

void mainLoop() {
  sPrint("inside main loop"); //prints to serial monitor

  //CHANNEL MODE//////////////////////////////////////////////////
  if (currentMode == channelMode) {
    if (c1) {
      animateCustom("c-mode");
      c1 = 0;
    }

    // Waits for above animation to be done 
    if (animationDone()) {

      P.print(channelName);

      buttonPress = readButtons(); // 0 - button A , 1 - button B

      if (buttonPress == 0) {
        cModeCounter++;
      } else if (buttonPress == 1) {
        switchMode();
        c1 = 1;
      }

      delay(100);
      sPrint("100");

    }

  } // end channel mode

  // SUBSCRIBER MODE //////////////////////////////////////////////
  else if (currentMode == subscriberMode) {

    // first time in subscriber mode
    if (s1) {
      animateCustom("s-mode");
      s1 = 0;
    }

    // Waits for above animation to be done 
    if (animationDone()) {

      if (s2) {
        P.print("...");
        sub_count = getSubCount();
        animateCustom(String(sub_count));
        s2 = 0;
      }

      // Wait for animation to be done 
      if (animationDone()) {
        P.print(sub_count);

        buttonPress = readButtons(); // 0 - button A , 1 - button B

        if (buttonPress == 1) {
          sModeCounter++;
          s2 = 1;
          sPrint("Manual Update Please");
          sPrint(String(sModeCounter));
        } else if (buttonPress == 0) {
          switchMode();
          s1 = 1;
          s2 = 1;
        }

        delay(100);
        sPrint("100");
      }

    }
  }
}
