void initPins() {
  // set buttons as inputs
  pinMode(buttonPin1, INPUT);
  pinMode(buttonPin2, INPUT);
}

void connectWifi() {
  // Set WiFi to station mode and disconnect from an AP if it was Previously
  // connected
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  delay(100);

  // Attempt to connect to Wifi network:
  Serial.print("Connecting Wifi: ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");

  IPAddress ip = WiFi.localIP();
  Serial.println(ip);

  // Required if you are using ESP8266 V2.5 or above
  client.setInsecure();

}

void testButton() {

  buttonState1 = digitalRead(buttonPin1);
  buttonState2 = digitalRead(buttonPin2);

  // check if the pushbutton is pressed. If it is, the buttonState is HIGH:
  if ((buttonState1 == HIGH) || (buttonState2 == HIGH)) {
    // turn LED on:
    Serial.println("HIGH");
  } else {
    // turn LED off:
    Serial.println("LOW");
  }

  //delay(250);
}

int readButtons() {
  // check button 1
  buttonState1 = digitalRead(buttonPin1);
  buttonState2 = digitalRead(buttonPin2);
  // check button 2 

  if ((buttonState1 == HIGH) && (buttonState2 == LOW)) {
    Serial.println("Button 1 is pressed");
    return 0;

  } else if ((buttonState1 == LOW) && (buttonState2 == HIGH)) {
    Serial.println("Button 2 is pressed");
    return 1;
  } else {
    return -1;
  } // no button press

}

void setMode(char m) {
  currentMode = m;
}

void switchMode() {
  if (currentMode == channelMode) {
    setMode(subscriberMode);
    sModeCounter = 0;
  } else if (currentMode == subscriberMode) {
    setMode(channelMode);
    cModeCounter = 0;
  }
}

/********************************************** Animation Functions ***************************************************/
bool animationDone() {
  return P.displayAnimate(); // returns 0 - animation in progress , 1 - completed animation cycle
}

void animateCustom(String a) {
  P.displayClear();

  for (int i = 0; i < a.length(); i++) {
    nmp[i] = a[i];
  }

  nmp[a.length()] = '\0';
  //cmp[a.length() ] = '\0';

  strcpy(curMessage, newMessage);

  P.displayReset(); // * Reset the current animation to restart for all zones.
  P.displayText(curMessage, scrollAlign, scrollSpeed, scrollPause, scrollEffect, scrollEffect);
}

void serialPrintSubCount() {
  Serial.print("Subscriber Count: ");
  Serial.println(api.channelStats.subscriberCount);
}

void sPrint(String a) {
  Serial.println(a);
}

long getSubCount() {
  if (api.getChannelStatistics(CHANNEL_ID)) {
    return api.channelStats.subscriberCount;
  } else {
    return -1;
  }
}
