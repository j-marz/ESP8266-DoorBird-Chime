# ESP8266-DoorBird-Chime
WiFi doorbell chime using a NodeMCU ESP8266 devboard for use with DoorBird smart doorbell.

A low cost (<$15AUD) alternative to the DoorBird IP Door Chime A1061W ~$250AUD

## Parts
* NodeMCU ESP8266 dev board ~$6AUD - https://www.ebay.com.au/itm/162194307584
* Passive buzzer module ~$3AUD - http://www.ebay.com.au/itm/282263010801
* Jumper wires (female-to-female) ~$3AUD - http://www.ebay.com.au/itm/40pcs-10cm-Dupont-Cables-F-F-Jumper-Breadboard-Wire-GPIO-Ribbon-Pi-Arduino-New/122343723749
* Micro USB 5 volt power supply - ~$5AUD - an old phone charger will work or connect directly to USB port of computer

## Instructions
1. Add your SSID and WPA(2) passphrase to the sketch - ssid and password variables
2. Use Arduino IDE to upload sketch to the ESP8266
3. Connect the buzzer module to the GPIO pins using jumper wires - GND to G, VCC to 3V, I/O to D1
4. Configure the DoorBird's notification event API to call the web service on the ESP8266 - you will be promted to enter the DoorBird's username and password
`http://<IP address of your DoorBird>/bha-api/notification.cgi?url=http://<IP address of your ESP8266>/chime=dingDong/?&event=doorbell&subscribe=1`

See DoorBird's API documentation for more info - https://www.doorbird.com/downloads/api_lan.pdf?rev=0.17

Note, you'll need to find the IP address of your DoorBird and the ESP8266 device from your DHCP server or router.

## Testing
You can test the chime directly using your web browser
`http://<IP address of your ESP8266>/`

Click on the chime options
* `dingDong` Ding Dong tone + LED
* `silent` 20 LED flashes over 10 seconds

## Enclosure/case
I've included STL files of a 3D printed case i designed for the specific NodeMCU devboard listed above. The case may not be suitable for all NodeMCU variants (e.g. Amica)
* Speaker hole and mount point on rear lid
* Hole for onboard LED on front
* Holes for Devboard buttons on front

## To Do
* Add authentication to the web service
* Add more chime options