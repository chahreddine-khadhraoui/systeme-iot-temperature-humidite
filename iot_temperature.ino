#include <WiFi.h>
#include <DHT.h>

// Configuration du réseau Wi-Fi
const char* ssid = "TON_SSID_WIFI";
const char* password = "TON_MOT_DE_PASSE_WIFI";

// Définition du capteur DHT (ex: DHT11 ou DHT22)
#define DHTPIN 4     // Broche de données connectée au DHT
#define DHTTYPE DHT11 

DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(115200);
  delay(1000);

  // Initialisation du capteur
  dht.begin();

  // Connexion au Wi-Fi
  Serial.println();
  Serial.print("Connexion au reseau : ");
  Serial.println(ssid);
  
  WiFi.begin(ssid, password);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("Connexion Wi-Fi etablie !");
  Serial.print("Adresse IP : ");
  Serial.println(WiFi.localIP());
}

void loop() {
  // Attente de 2 secondes entre chaque mesure
  delay(2000);

  // Lecture de l'humidité
  float humidite = dht.readHumidity();
  // Lecture de la température en Celsius
  float temperature = dht.readTemperature();

  // Vérification si les lectures ont échoué
  if (isnan(humidite) || isnan(temperature)) {
    Serial.println("Erreur de lecture du capteur DHT !");
    return;
  }

  // Affichage des données sur le moniteur série
  Serial.print("Temperature : ");
  Serial.print(temperature);
  Serial.print(" °C  |  ");
  Serial.print("Humidite : ");
  Serial.print(humidite);
  Serial.println(" %");
}
