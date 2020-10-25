//////////////////////////////////////////////////////////
//  Name      : q.rbx subscriber counter 
//////////////////////////////////////////////////////////

// Libraries
#include <ESP8266WiFi.h>

#include <WiFiClientSecure.h>

#include <MD_Parola.h>

#include <MD_MAX72xx.h>

#include <SPI.h>

#include <YoutubeApi.h>  // Library for connecting to the Youtube API

#include <ArduinoJson.h>  // Library used for parsing Json from the API responses

//------- Wifi Network ------
char ssid[] = ; // your network SSID (name)
char password[] = ; // your network key

// Youtube API Info
#define API_KEY "" // your google apps API Token
#define CHANNEL_ID "" // your channel id
//-----------------------------------

// Wifi objects 
WiFiClientSecure client;
YoutubeApi api(API_KEY, client);
unsigned long timeBetweenRequests = 60000;
unsigned long nextRunTime;
long subs = 0;

//------- Max7219 ------
#define HARDWARE_TYPE MD_MAX72XX::FC16_HW // select the correct hardware type
#define MAX_DEVICES 4 // total number of displays
#define CLK_PIN D5
#define CS_PIN D6
#define DATA_PIN D7

// create display object
MD_Parola P = MD_Parola(HARDWARE_TYPE, CS_PIN, MAX_DEVICES);

// led display properties
textPosition_t scrollAlign = PA_RIGHT;
uint8_t scrollSpeed = 15; // default frame delay value
uint16_t scrollPause = 500; // in milliseconds
textEffect_t scrollEffect = PA_SCROLL_LEFT;

// push button
const int buttonPin1 = D2;
const int buttonPin2 = D1;
bool buttonState1 = 0;
bool buttonState2 = 0;

// To store messages 
#define BUF_SIZE 75
char curMessage[BUF_SIZE] = {
  "Youtube Subscriber Counter: "
};
char * cmp = curMessage;
char newMessage[BUF_SIZE] = {
  " "
};
char * nmp = newMessage;

// Keeping track of Modes
int buttonPress;
char currentMode;
char channelMode = 'c';
int cModeCounter = 0;
char subscriberMode = 's';
int sModeCounter = 0;
String channelName = ">QRBX<";
bool firstTime = 1;

bool c1 = 1;
bool s1 = 1;
bool s2 = 1;

long sub_count = 0;
String sub_count_str;
unsigned int string_size = 0;
