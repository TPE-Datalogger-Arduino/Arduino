const int capteur = 0;
int valeur = 0;
float temperature = 0.0;

void setup() {
  Serial.begin(9600);
  analogReference(INTERNAL);
}

void loop() {
  valeur = analogRead(capteur);
  temperature = valeur / 9.31;

  Serial.println(temperature);

  delay(500);
}
