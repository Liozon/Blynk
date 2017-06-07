/*

Programm to control two garage doors of your house - Julien Muggli, 2017
Github link: https://github.com/Liozon/Blynk/tree/master/Garages/2%20doors

You'll need: a NodeMCU board, two relay switches and two reed switches
And of course: the Blynk app !
Links for product purchase:
NodeMCU: (eBay) http://tiny.cc/7mioly
Relay switch - pack of 5: (eBay) http://tiny.cc/npioly
Reed switch - pack of 5: (eBay) http://tiny.cc/pqioly
400 pins breadboards: (eBay) http://tiny.cc/ntioly
Jumper wires - 120 Pcs: (eBay) http://tiny.cc/rvioly

NodeMCU PIN connection:
D1 => connect to reed switch 1
D3 => connect to reed switch 2
D5 => connect to relay switch 1
D6 => connect to relay switch 2

Blynk app widgets:
LED: connect to PIN V10 and V12
Value display: connect to V11 and V13
Button: connect to D5 and D6

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
WidgetLED led1(V10);
WidgetLED led2(V12);
#define BLYNK_GREEN   "#23C48E"
#define BLYNK_RED     "#D3435C"
SimpleTimer timer;

// The NodeMCU onboard LED will blink in sequence when it's successfully connected to the Blynk server
// (Useful when you install your project in your garage and you don't have access to the Arduino IDE serial monitor) 
// For the built-in LED on th NodeMCU, LOW = On and HIGH = Off
BLYNK_CONNECTED() {
  if (isFirstConnect) {
    digitalWrite(wifi, LOW);
     isFirstConnect = false;
     // Not needed, but it will send you a push notification when it's connected. Useful if you reset the board of the Wi-Fi goaes down when you're not at home.
     // Uncomment if you want push notifications
//     Blynk.notify("Garage doors connected to Wi-Fi !");
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

void garageX() {
  if (digitalRead(D1)) {
    led1.setColor(BLYNK_RED);  // Reed switch is open, D1 is HIGH
    Serial.println("Garage car X is open");
    Blynk.virtualWrite(V13, "Garage car X is open");

  } else {

    led1.setColor(BLYNK_GREEN);  // Reed switch is closed, D1 is LOW
    Serial.println("Garage car X is closed");
    Blynk.virtualWrite(V13, "Garage car X is closed");
    } 
 }

 void garageY() {
  if (digitalRead(D3)) {
    led2.setColor(BLYNK_RED);  // Reed switch is open, D3 is HIGH
    Serial.println("Garage car Y is open");
    Blynk.virtualWrite(V11, "Garage car Y is open");

  } else {

    led2.setColor(BLYNK_GREEN);  // Reed switch is closed, D3 is LOW
    Serial.println("Garage car Y is closed");
    Blynk.virtualWrite(V11, "Garage car Y is closed");
    }  
}

void setup()
{
  Serial.begin(9600);
  pinMode(power, OUTPUT); // Build-in LED for power indication
  pinMode(wifi, OUTPUT);  // Built-in LED for Wi-Fi indication 
  digitalWrite(power, LOW); // Declaring power LED is On
  digitalWrite(wifi, HIGH); // Declaring Wi-Fi LED is Off
  pinMode(D5, OUTPUT);  // PIN connection for relay switch for garage door 1
  pinMode(D6, OUTPUT);  // PIN connection for relay switch for garage door 2
  pinMode(D1, INPUT_PULLUP);  // PIN connection to reed switch for garage 1
  pinMode(D3, INPUT_PULLUP);  // PIN connection to reed switch for garage 1
  Blynk.begin(auth, ssid, pass); // Connection to Wi-Fi
  // You can also specify server:
  //Blynk.begin(auth, ssid, pass, "blynk-cloud.com", 8442);
  //Blynk.begin(auth, ssid, pass, IPAddress(192,168,1,100), 8442);

  // Turning LED in the Blynk app on
  led1.on();
  led2.on();
  timer.setInterval(1500, garageX);
  timer.setInterval(1500, garageY);
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
