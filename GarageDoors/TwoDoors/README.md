# Garage door - two doors variant

Programm to control two garage doors of your house - Julien Muggli, 2017

You'll need: a NodeMCU board, two relay switches and two reed switches <br/>
And of course: the Blynk app ! <br/>

## Hardware

Links for product purchase: <br/>
NodeMCU: (eBay) http://tiny.cc/7mioly <br/>
Relay switch - pack of 5: (eBay) http://tiny.cc/npioly <br/>
Reed switch - pack of 5: (eBay) http://tiny.cc/pqioly <br/>
400 pins breadboards: (eBay) http://tiny.cc/ntioly <br/>
Jumper wires - 120 Pcs: (eBay) http://tiny.cc/rvioly <br/>

NodeMCU PIN connection: <br/>
D1 => connect to reed switch 1 <br/>
D3 => connect to reed switch 2 <br/>
D5 => connect to relay switch 1 <br/>
D6 => connect to relay switch 2 <br/>

## Software

Blynk app widgets: <br/>
LED: connect to PIN V10 and V12 <br/>
Value display: connect to V11 and V13 <br/>
Button: connect to D5 and D6 <br/>

Configure Arduino IDE this way to communicate with this board: <br/>
Board type: NodeMCU 1.0 (ESP-12E Module) <br/>
Flash size: 4M (3M SPIFFS) <br/>
CPU Frequency: 80 MHz <br/>
Upload speed: 115200 <br/>