/* Source : http://skyduino.wordpress.com/2012/04/26/arduino-capteur-de-temperature-ds18b20/ */

#include <OneWire.h>

#define DS18B20 0x28
#define BROCHE_ONEWIRE 5

OneWire ds(BROCHE_ONEWIRE);

boolean getTemperature(float *temp){
  byte data[9], addr[8];
  // data : Données lues depuis le scratchpad
  // addr : adresse du module 1-Wire détecté

  if (!ds.search(addr)) { // Recherche un module 1-Wire
    ds.reset_search();    // Réinitialise la recherche de module
    return false;         // Retourne une erreur
  }

  if (OneWire::crc8(addr, 7) != addr[7]) // Vérifie que l'adresse a été correctement reçue
    return false;                        // Si le message est corrompu on retourne une erreur

  if (addr[0] != DS18B20) // Vérifie qu'il s'agit bien d'un DS18B20
    return false;         // Si ce n'est pas le cas on retourne une erreur

  ds.reset();             // On reset le bus 1-Wire
  ds.select(addr);        // On sélectionne le DS18B20

  ds.write(0x44, 1);      // On lance une prise de mesure de température
  delay(5000);             // Et on attend la fin de la mesure

  ds.reset();             // On reset le bus 1-Wire
  ds.select(addr);        // On sélectionne le DS18B20
  ds.write(0xBE);         // On envoie une demande de lecture du scratchpad

  for (byte j = 0 ; j < 9 ; j++) // On lit le scratchpad
    data[j] = ds.read();       // Et on stock les octets reçus

  // Calcul de la température en degré Celsius
  *temp = ((data[1] << 8) | data[0]) * 0.0625;

  // Pas d'erreur
  return true;
}

void setup() {
  Serial.begin(9600);
}

void loop() {
  float temperatures[13], moyenne;

  for (int i(1) ; i <= 13 ; i++) {
    float temp;

    if(getTemperature(&temp)) {
      temperatures[i] = temp;
      Serial.print("Température ");
      Serial.print(i);
      Serial.print(" : ");
      Serial.println(temp);
    }
  }

  for (int i(1) ; i <= 13 ; i++)
    moyenne += temperatures[i];

  moyenne /= 12;
  Serial.print("Moyenne : ");
  Serial.println(moyenne);
}
