/*

  Programm to control one garage door of your house - Julien Muggli, 2018
  Github link: https://github.com/Liozon/Blynk/tree/master/GarageDoors/OneDoor

  You'll need: a NodeMCU board, one relay switch and one reed switch
  And of course: the Blynk app !

  Links for product purchase:
  NodeMCU: (eBay) http://tiny.cc/7mioly
  Relay switch - pack of 5: (eBay) http://tiny.cc/npioly
  Reed switch - pack of 5: (eBay) http://tiny.cc/pqioly
  400 pins breadboards: (eBay) http://tiny.cc/ntioly
  Jumper wires - 120 Pcs: (eBay) http://tiny.cc/rvioly

  NodeMCU PIN connection:
  D3 => connect to reed switch 1
  D5 => connect to relay switch 1

  Blynk app widgets:
  LED: connect to PIN V1
  Value display: connect to V0
  Button: connect to D5

  Configure Arduino IDE this way to communicate with this board:
  Board type: NodeMCU 1.0 (ESP-12E Module)
  Flash size: 4M (3M SPIFFS)
  CPU Frequency: 80 MHz
  Upload speed: 115200

*/

// Uncomment "#define BLYNK_PRINT Serial" for debug
//#define BLYNK_PRINT Serial
#define BLYNK_MAX_SENDBYTES 256 // Default notification characters limit is 128
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <SimpleTimer.h>

// Blynk Auth token
char auth[] = "AUTH_TOKEN";

// WiFi connection information
// Set password to "" for open networks
char ssid[] = "SSID";
char pass[] = "Password";

// Some useful declarations
int power = LED_BUILTIN;
int wifi = 2;
bool isFirstConnect = true;
WidgetLED led(V1);
#define BLYNK_GREEN   "#23C48E"
#define BLYNK_RED     "#D3435C"
#define BLYNK_YELLOW  "#DDAD3B"
SimpleTimer timer;

// Variables will change:
unsigned long lastPress1 = 0;
unsigned long stateTime1 = 500; //runs until two seconds elapse

// The NodeMCU onboard LED will blink in sequence when it's successfully connected to the Blynk server
// (Useful when you install your project in your garage and you don't have access to the Arduino IDE serial monitor)
// For the built-in LED on th NodeMCU, LOW = On and HIGH = Off
BLYNK_CONNECTED() {
  if (isFirstConnect) {
    digitalWrite(wifi, LOW);
    isFirstConnect = false;
    Blynk.virtualWrite(V0, "Checking status...");
    led.setColor(BLYNK_YELLOW);
    // Not needed, but it will send you a push notification when it's connected. Useful if you reset the board or the Wi-Fi goes down when you're not at home.
    // Uncomment if you want push notifications
    //Blynk.notify("Garage doors connected to Wi-Fi !");
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
    digitalWrite(power, LOW);
    digitalWrite(wifi, LOW);
    delay(100);
  }
}

void relayGarageLexus() {
  if (digitalRead(D5)) lastPress1 = millis();
  if (millis() - lastPress1 < stateTime1) {
    digitalWrite(D7, LOW);
  } else {
    digitalWrite(D7, HIGH);
  }
}

void garageDoor() {
  if (digitalRead(D3)) {
    led.setColor(BLYNK_RED);  // Reed switch is open, D3 is HIGH
    Serial.println("Garage car X is open");
    Blynk.virtualWrite(V0, "Garage car X is open");

  } else {

    led.setColor(BLYNK_GREEN);  // Reed switch is closed, D3 is LOW
    Serial.println("Garage car X is closed");
    Blynk.virtualWrite(V0, "Garage car X is closed");
  }
}

void setup()
{
  Serial.begin(9600);
  pinMode(power, OUTPUT); // Build-in LED for power indication
  pinMode(wifi, OUTPUT);  // Built-in LED for Wi-Fi indication
  pinMode(D1, OUTPUT);
  digitalWrite(D1, LOW);
  digitalWrite(power, LOW); // Declaring power LED is On
  digitalWrite(wifi, HIGH); // Declaring Wi-Fi LED is Off
  digitalWrite(D7, HIGH); // Declaring the Relay is Off (to avoid the door to open when a reboot/power cut occurs)
  pinMode(D7, OUTPUT);  // PIN connection for relay switch for garage door
  pinMode(D3, INPUT_PULLUP);  // PIN connection to reed switch for garage
  Blynk.begin(auth, ssid, pass);  // Connection to Wi-Fi
  // You can also specify server:
  //Blynk.begin(auth, ssid, pass, "blynk-cloud.com", 8442);
  //Blynk.begin(auth, ssid, pass, IPAddress(192,168,1,100), 8080);

  // Turning LED in the Blynk app on
  led.on();
  timer.setInterval(1500, garageDoor);
}

void loop()
{
  Blynk.run();
  timer.run();
  if (WiFi.status() == 6) // This will check the Wi-Fi connection. If disconnected, it will reset the board (reboot it) until it's successfully connected to Wi-Fi
  {
    ESP.reset();
  }
}
