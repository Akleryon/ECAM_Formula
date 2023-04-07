#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>

#include <Servo.h>

#include <ESP8266WiFiMulti.h>
ESP8266WiFiMulti WiFiMulti;

const char* ssid = "Bugati_Chiron";
const char* password = "vive_l-ecam";

//Your IP address or domain name with URL path
const char* serverNameESC = "http://192.168.4.1/ESC";
const char* serverNameServo = "http://192.168.4.1/Servo";

String Str_Valeur_ESC;
String Str_Valeur_Servo;
int Valeur_ESC;
int Valeur_Servo;

#define LED D4

unsigned long previousMillis = 0;
const long interval = 5; 

Servo myServo;
Servo ESC1;
Servo ESC2;

void setup() {
  Serial.begin(115200);
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("Connected to WiFi");
  
  pinMode(LED, OUTPUT);
  
  myServo.attach(D1);
  ESC1.attach(D2);
  ESC2.attach(D3);

}

void loop() {
  unsigned long currentMillis = millis();
  if ((WiFi.status() != WL_CONNECTED) && (currentMillis - previousMillis >=interval)) {
    Serial.println("Reconnecting to WIFI network");
    ESP.restart();
  }
  else if((currentMillis - previousMillis >= interval) && (WiFi.status() == WL_CONNECTED)) {
     // Check WiFi connection status
    Str_Valeur_ESC = httpGETRequest(serverNameESC);
    Str_Valeur_Servo = httpGETRequest(serverNameServo);

    Valeur_ESC = Str_Valeur_ESC.toInt();
    Valeur_Servo = Str_Valeur_Servo.toInt();

    
    myServo.write(Valeur_Servo);
    ESC1.write(Valeur_ESC);
    ESC2.write(Valeur_ESC);

    //Serial.println(Valeur_ESC);
    Serial.println("ESC: " + Str_Valeur_ESC + " - Servo: " + Str_Valeur_Servo);     
    // save the last HTTP GET Request
    previousMillis = currentMillis;
  }
}

String httpGETRequest(const char* serverName) {
  WiFiClient client;
  HTTPClient http;
    
  // Your IP address with path or Domain name with URL path 
  http.begin(client, serverName);
  
  // Send HTTP POST request
  int httpResponseCode = http.GET();
  
  String payload = "--"; 
  
  if (httpResponseCode>0) {
    Serial.print("HTTP Response code: ");
    Serial.println(httpResponseCode);
    payload = http.getString();
  }
  else {
    Serial.print("Error code: ");
    Serial.println(httpResponseCode);
  }
  // Free resources
  http.end();

  return payload;
}
