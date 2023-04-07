// Import required libraries
#include <ESP8266WiFi.h>
#include <ESPAsyncWebServer.h>

#define LED D4

// Set your access point network credentials
const char* ssid = "Bugati_Chiron";
const char* password = "vive_l-ecam";

String Str_Valeur_ESC;
String Str_Valeur_Servo;

int Valeur_ESC;
int Valeur_Servo;

const int NUMBER_OF_FIELDS = 2; // how many comma separated fields we expect
int fieldIndex = 0;            // the current field being received
int values[NUMBER_OF_FIELDS];   // array holding values for all the fields
int sign=1;

// Create AsyncWebServer object on port 80
AsyncWebServer server(80);

String readESC() {
  return String(Valeur_ESC);//Serial.read());
}

String readServo() {
  return String(Valeur_Servo);//Serial.read());
}

void setup() {
  // Serial port for debugging purposes
  Serial.begin(115200);

  // Setting the ESP as an access point
  Serial.print("Setting AP (Access Point)…");
  // Remove the password parameter, if you want the AP (Access Point) to be open
  WiFi.softAP(ssid, password);

  IPAddress IP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(IP);

  server.on("/ESC", HTTP_GET, [](AsyncWebServerRequest * request) {
    request->send_P(200, "text/plain", readESC().c_str());
  });
  server.on("/Servo", HTTP_GET, [](AsyncWebServerRequest * request) {
    request->send_P(200, "text/plain", readServo().c_str());
  });
  // Start server
  server.begin();
  pinMode(LED, OUTPUT);
}

void loop() {
    if( Serial.available())
    {
      Str_Valeur_ESC = Serial.readStringUntil(';');
      Valeur_ESC = Str_Valeur_ESC.toInt();
      
      Str_Valeur_Servo = Serial.readStringUntil('\n');
      Valeur_Servo = Str_Valeur_Servo.toInt();
    }
}
