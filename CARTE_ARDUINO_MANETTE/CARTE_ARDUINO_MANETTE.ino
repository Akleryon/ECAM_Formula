int Valeur_Servo;
int Valeur_ESC;



void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
}

void loop() {
  // put your main code here, to run repeatedly:
    Valeur_Servo = analogRead(A0);
    Valeur_Servo = map(Valeur_Servo, 0, 1023, 0, 140);
    Valeur_ESC = analogRead(A1);
    Valeur_ESC = map(Valeur_ESC, 0, 1023, -50, 45);
    
    Serial.print(Valeur_ESC);Serial.print(';');Serial.println(Valeur_Servo);
    delay(10);
}
