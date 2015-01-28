#include <Barometer.h> // Inclusion de la bibliothèque du BMP180
#include <Wire.h>

Barometer capteur;

void setup()
{
  Serial.begin(9600);
  capteur.init(); // On initialise le capteur.
}

void loop()
{
  float temperatures[10], moyenne;

  for (int i(0) ; i < 10 ; i++) // On relève 10 fois la température.
  {
    temperatures[i] = capteur.bmp085GetTemperature(myBarometer.bmp085ReadUT()); // On la place dans la case i du tableau.
    
    Serial.println(temperatures[i]); // On l'affiche pour vérifier.
    
    delay(90000); // On attend 500 ms. Ainsi, la boucle se termine au bout de 10 × 90 s = 15 min.
  }

  for (int i(0) ; i < 10 ; i++)
    moyenne += temperatures[i]; // On somme les valeurs

  moyenne /= 10; // Et on fait la moyenne.

  Serial.print("Moyenne : ");
  Serial.println(moyenne);
}
