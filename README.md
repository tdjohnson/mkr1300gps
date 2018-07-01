# mkr1300gps
LoRaWAN coverage survey with GPS tracker based on Arduino MKR WAN 1300

Visit us @ 
https://www.thethingsnetwork.org/community/regensburg/
https://twitter.com/TTN_Regensburg

Hardware
* Arduino MKR WAN 1300
* GPS Module comparable to Ublox NEO-6M
* 0.91" OLED Display SSD1306
* In-Circuit 868Mhz Antenna RP-SMA, 5cm, +3dB
* Power Supply: 2 x AA Batteries

Device with all components visible
[[https://github.com/tdjohnson/mkr1300gps/blob/master/misc/mkr1300gps2.jpeg|alt=components]]

Device in enclosure
[[https://github.com/tdjohnson/mkr1300gps/blob/master/misc/mkr1300gps1.jpeg|alt=enclosure]]







Software
* LoRa connectivity by MKRWAN library https://github.com/arduino-libraries/MKRWAN
* GPS handling based on driver an examples from TinyGPSPlus https://github.com/mikalhart/TinyGPSPlus
* Display handling by Adafruit_SSD1306 driver https://github.com/adafruit/Adafruit_SSD1306
* LoRaWAN coverage survey via TTN Mapper Integration on TheThingsNetwork https://www.thethingsnetwork.org/docs/applications/ttnmapper/