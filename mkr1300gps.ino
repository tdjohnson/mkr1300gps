#include <MKRWAN.h>
#include <TinyGPS++.h>
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>


#define OLED_RESET 4
Adafruit_SSD1306 display(OLED_RESET);
#define NUMFLAKES 10
#define XPOS 0
#define YPOS 1
#define DELTAY 2
#define LOGO16_GLCD_HEIGHT 16
#define LOGO16_GLCD_WIDTH  16

static const int RXPin = 4, TXPin = 3;
static const uint32_t SerialBaud = 9600;
static const uint32_t GPSBaud = 9600;
static String appEui = "";
static String appKey = "";
TinyGPSPlus gps;
LoRaModem modem;
int lifetime = 0;
int connected = 0;
int lastcon = 0;
double last_lat = 0;
double last_lng = 0;
unsigned long distanceToLast;

void connectr() {
  Serial.println("conn: connecting...");
  connected = 0;
 
  if (!modem.begin(EU868)) {
    while (1) {}
  };

  connected = modem.joinOTAA(appEui, appKey);
  if (!connected) {
    Serial.println("conn: FAIL");
  }else
  {
      Serial.println("conn: OK");
  }
  
}


void sendPayload(String msg) {

  int err;

  if(!connected){
      connectr();
  }
  
      display.clearDisplay();
      displayinfo("SENDING DATA...",0);
 
      modem.beginPacket();
      modem.print(msg);
      err = modem.endPacket();

      if (err) {
        Serial.println("data: OK");
        lastcon = gps.time.value();
      } else {
        Serial.println("data: ERROR");
      }
      

}

void setup()
{
  delay(1000);
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);   pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(SerialBaud);
  Serial1.begin(GPSBaud);
  delay(1000);
  Serial.println("MKR GPS Tracker");
  display.clearDisplay();
  displayinfo("TTN Regensburg",0);
  displayinfo("GPS Tracker",1);
  delay(1000);
}

void displayinfo(String text, int line) {
  //display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0,line*10);
  display.display();
  display.println(text);
  display.display();
  delay(1);
}

static void smartDelay(unsigned long ms)
{
  unsigned long start = millis();
  do
  {
    while (Serial1.available())
      gps.encode(Serial1.read());
  } while (millis() - start < ms);
}

void loop()
{

 
  if (gps.location.isValid() == 1 && gps.hdop.hdop() < 10)
  {
    double cur_lat = gps.location.lat();
    double cur_lng = gps.location.lng();
    String vlat = String(cur_lat, 6);
    String vlng = String(cur_lng, 6);
    String msg = vlat + vlng + String(gps.altitude.meters()) + String(gps.hdop.hdop());
 
     distanceToLast = (unsigned long)TinyGPSPlus::distanceBetween(cur_lat, cur_lng, last_lat, last_lng);
    Serial.println("loc: " + msg + " dist:" + String(distanceToLast) + " hdop:" +String(gps.hdop.hdop()));

    if(distanceToLast > 1)
     {
    sendPayload(msg);
     }

    last_lat = cur_lat;
    last_lng = cur_lng;

    smartDelay(10 * 1000);
  } else {
    Serial.print(F("No GPS data!"));
    Serial.println("Sats: " + String(gps.satellites.value())  + " hdop:" +String(gps.hdop.hdop()));

    smartDelay(1000);
  }
   display.clearDisplay();
   displayinfo("L:" + String(lifetime++),0);
   displayinfo("S:" + String(gps.satellites.value())  + " H:" +String(gps.hdop.hdop()),1);
   displayinfo("W:" + String(connected) + " D:" + String(distanceToLast) + " C:" + String(lastcon),2);
}
