//FirebaseESP8266.h must be included before ESP8266WiFi.h
#include "FirebaseESP8266.h"
#include <ESP8266WiFi.h>

#define FIREBASE_HOST "your project ID here"
#define FIREBASE_AUTH "your data secret"
#define path "you path here"
#define WIFI_SSID "your SSID here"
#define WIFI_PASSWORD "your password here"

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

  //set the streaming path to "/var1/value" and begin stream connection
  if(!Firebase.beginStream(firebaseData, path))  {
  //Could not begin stream connection, then print out the error detail
  Serial.println(firebaseData.errorReason());
  }
  
}

void loop() {

  //start a stream and get the updates in real time database thorugh HTTP connection

  if (!Firebase.readStream(firebaseData))
  {
    //If read stream was failed, print the error detail.
    Serial.println(firebaseData.errorReason());
  }

  if (firebaseData.streamTimeout())
  {
    //If stream timeout, just notify
    Serial.println("Stream timeout, resume streaming...");
    Serial.println();
  }

  if (firebaseData.streamAvailable())
  {
   
   //Print out value
   //Stream data can be many types which can be determined from function dataType

    if (firebaseData.dataType() == "int")
      Serial.println(firebaseData.intData());
    else if (firebaseData.dataType() == "float")
      Serial.println(firebaseData.floatData());
    else if (firebaseData.dataType() == "string")
      Serial.println(firebaseData.stringData());
    else if (firebaseData.dataType() == "json")
      Serial.println(firebaseData.jsonData());
    
  }
  
}
