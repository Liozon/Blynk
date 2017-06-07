// Programme de domotique pour les garages de la maison - Julien Muggli, 2017
// Décommenter "#define BLYNK_PRINT Serial" pour debug
#define BLYNK_PRINT Serial
#define BLYNK_MAX_SENDBYTES 256 // Augmentation du nombre de caractères pour les notifications
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <SimpleTimer.h>

// Blynk Auth token (GarageAnnexe)
char auth[] = "fa5af8e8c48940d08f15567e3ea9c9ef";

// Informations de connexion au WiFi
char ssid[] = "Modem 56K";
char pass[] = "enfinduwifi";

// Diverses déclarations
int power = LED_BUILTIN;
int wifi = 2;
bool isFirstConnect = true;
WidgetLED led(V1);
#define BLYNK_GREEN   "#23C48E"
#define BLYNK_RED     "#D3435C"
SimpleTimer timer;

// Indique dès que le NodeMCU est connecté au WiFi et au serveur
// (Utile une fois que l'on utilise pas le moniteur série de l'Arduino IDE)
// Pour les LED sur le NodeMCU, LOW = On et HIGH = Off
BLYNK_CONNECTED() {
  if (isFirstConnect) {
    digitalWrite(wifi, LOW);
     isFirstConnect = false;
     Blynk.notify("Le garage de la Lexus est connecté !");
     digitalWrite(power, HIGH);
     delay(500);
     digitalWrite(wifi, HIGH);
     digitalWrite(power, LOW);
     delay(500);
     digitalWrite(wifi, LOW);
     digitalWrite(power, HIGH);
     delay(500);
     digitalWrite(wifi, HIGH);
     digitalWrite(power, LOW);
     delay(500);
     digitalWrite(wifi, LOW);
     digitalWrite(power, HIGH);
     delay(500);
     digitalWrite(wifi, HIGH);
     digitalWrite(power, LOW);
     delay(500);
     digitalWrite(wifi, LOW);
     delay(1000);
     digitalWrite(power, HIGH);
     digitalWrite(wifi, HIGH);
     delay(100);
     digitalWrite(power, LOW);
     digitalWrite(wifi, LOW);
     delay(100);
     digitalWrite(power, HIGH);
     digitalWrite(wifi, HIGH);
     delay(100);
     digitalWrite(power, LOW);
     digitalWrite(wifi, LOW);
     delay(100);
     digitalWrite(power, HIGH);
     digitalWrite(wifi, HIGH);
     delay(100);
     digitalWrite(power, LOW);
     digitalWrite(wifi, LOW);
     delay(100);
     digitalWrite(power, HIGH);
     digitalWrite(wifi, HIGH);
     delay(100);
     digitalWrite(power, LOW);
     digitalWrite(wifi, LOW);
     delay(100);
     digitalWrite(power, HIGH);
     digitalWrite(wifi, HIGH);
     delay(100); 
     }
 }

void garageLexus() {
 if (digitalRead(D3)) {
    led.setColor(BLYNK_RED);  // Le reed switch est ouvert, D3 est HIGH
    Serial.println("Lexus ouvert");
    Blynk.virtualWrite(V0, "Garage Lexus ouvert");

  } else {

    led.setColor(BLYNK_GREEN);  // Le reed switch est fermé, D3 est LOW
    Serial.println("Lexus fermé");
    Blynk.virtualWrite(V0, "Garage Lexus fermé");
    }
}

void setup()
{
  // Décommenter "Serial.begin(9600)" pour debug
  Serial.begin(9600);
  pinMode(power, OUTPUT); // Déclaration LED alimentation
  pinMode(wifi, OUTPUT); // Déclaration LED WiFi 
  digitalWrite(power, LOW); // Déclaration LED alimentation est allumé
  digitalWrite(wifi, HIGH); // Déclaration LES WiFi est éteinte
  pinMode(D5, OUTPUT);   // Connection au relai du garage de la Lexus
  pinMode(D3, INPUT_PULLUP);    // Connection au reed switch du garage de la Lexus
  Blynk.begin(auth, ssid, pass, IPAddress(192,168,0,196), 8442); // Connection au WiFi
  
  // Allumage des LED, pour les voir dans l'app Blynk
  led.on();
  timer.setInterval(1500, garageLexus);
}

void loop()
{
  Blynk.run();
  timer.run();
  if (WiFi.status() == 6)      // Check la connexion. Si deconnecté, alors il se reset jusqu'à ce que la connexion soit à nouveau établie
  {
    ESP.reset();
  }
}
