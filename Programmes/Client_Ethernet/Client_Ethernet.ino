#include <SPI.h>
#include <Ethernet.h>

byte mac[] = {0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED};
IPAddress ip(10,0,0,20);
IPAddress myDns(1,1,1,1);

EthernetClient client;

char server[] = "192.168.xxx.xxx";

unsigned long lastConnectionTime = 0;
boolean lastConnected = false;
const unsigned long postingInterval = 60*1000;

void setup() {
  Serial.begin(9600);

  delay(1000);
  Ethernet.begin(mac, ip, myDns);
}

void loop() {
  if (client.available()) {
    char c = client.read();
    Serial.print(c);
  }

  if (!client.connected() && lastConnected) {
    Serial.println();
    Serial.println("Déconnecté.");
    client.stop();
  }

  if(!client.connected() && (millis() - lastConnectionTime > postingInterval)) {
    requete();
  }

  lastConnected = client.connected();
}

void requete() {
  if (client.connect(server, 80)) {
    Serial.println("Connexion...");
    client.println("GET /ajouter-temperature.php?t=21.5 HTTP/1.1");
    client.println("Host: 191.168.xxx.xxx");
    client.println("User-Agent: arduino-ethernet");
    client.println("Connection: close");
    client.println();

    lastConnectionTime = millis();
  } else {
    Serial.println("Connexion interrompue.");
    Serial.println("Déconnecté.");
    client.stop();
  }
}
