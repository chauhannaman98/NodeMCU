//FirebaseESP8266.h must be included before ESP8266WiFi.h
#include "FirebaseESP8266.h"
#include <ESP8266WiFi.h>

#define FIREBASE_HOST "your project ID"
#define FIREBASE_AUTH "your data secret"
#define WIFI_SSID "your SSID"
#define WIFI_PASSWORD "your wifi password"

//Define FirebaseESP8266 data object
FirebaseData firebaseData;

void setup()  {

  Serial.begin(115200);

  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting to Wi-Fi");
  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    delay(300);
  }
  Serial.println();
  Serial.print("Connected with IP: ");
  Serial.println(WiFi.localIP());
  Serial.println();

  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  Firebase.reconnectWiFi(true);
  
}

void loop() {

  //Read integer value from database at "/test/int" 

  int val = 0;

  if(Firebase.getInt(firebaseData, "/var1/value")) {

    //Success, then read the payload value
    //Make sure payload value returned from server is integer
    //This prevent you to get garbage data
    if (firebaseData.dataType() == "int") {
      val = firebaseData.intData();
      Serial.println(val);
    }
  } 
  else {
    //Failed, then print out the error detail
    Serial.println(firebaseData.errorReason());
  }
  
}
