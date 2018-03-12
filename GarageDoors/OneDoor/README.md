# Garage door - one door variant

Programm to control one garage door of your house - Julien Muggli, 2017

You'll need: a NodeMCU board, one relay switch and one reed switch <br/>
And of course: the Blynk app !

## Hardware

Links for product purchase: <br/>
NodeMCU: (eBay) http://tiny.cc/7mioly <br/>
Relay switch - pack of 5: (eBay) http://tiny.cc/npioly <br/>
Reed switch - pack of 5: (eBay) http://tiny.cc/pqioly <br/>
400 pins breadboards: (eBay) http://tiny.cc/ntioly <br/>
Jumper wires - 120 Pcs: (eBay) http://tiny.cc/rvioly <br/>

NodeMCU PIN connection: <br/>
D3 => connect to reed switch 1 <br/>
D5 => connect to relay switch 1 <br/>

## Software

Blynk app widgets: <br/>
LED: connect to PIN V1 <br/>
Value display: connect to V0 <br/>
Button: connect to D6 <br/>

Configure Arduino IDE this way to communicate with this board: <br/>
Board type: NodeMCU 1.0 (ESP-12E Module) <br/>
Flash size: 4M (3M SPIFFS) <br/>
CPU Frequency: 80 MHz <br/>
Upload speed: 115200 <br/>
