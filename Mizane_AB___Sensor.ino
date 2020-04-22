#include <SPI.h>
#include <Wire.h>
#include <BlynkApiArduino.h>
#include <Blynk/BlynkProtocol.h>
#include <Adapters/BlynkArduinoClient.h>
#include <ESP8266WiFi.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <BlynkSimpleEsp8266.h>
#include <DHT.h>


#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
#define OLED_RESET -1 // Reset pin # (or -1 if sharing Arduino reset pin)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
#define BLYNE_PRINT serial

const int AirValue = 790;   //you need to replace this value with Value_1
const int WaterValue = 390;  //you need to replace this value with Value_2
const int SensorPin = A0;
const char* ssid = "Mr.atashnejad";
const char* password = "Nimda3721@#";
char auth[] = "lSiL_rEg8DQNZH84UcBGZPhCXMUrGSdi";
int soilMoistureValue = 0;
int soilmoisturepercent = 0;


void setup() {
  Blynk.begin(auth,ssid,password);
  Wificonnection();
  Blynk.virtualWrite(V5, analogRead(A0) );
  display.clearDisplay();
  
}

//void Blynkconnect(){
  //Blynk.begin(auth,ssid,password);
  
//  }

void Wificonnection() {
  {
    Serial.begin(9600); // open serial port, set the baud rate to 9600 bps
    display.begin(SSD1306_SWITCHCAPVCC, 0x3C); //initialize with the I2C addr 0x3C (128x64)
    display.setCursor(20, 0); //oled display
    display.setTextSize(1);
    display.setTextColor(WHITE);
    Serial.println("connecting to wifi ...");
    Serial.println(ssid);
    WiFi.begin(ssid, password);
    Serial.println("");
    display.setCursor(20, 0); //oled display
    display.setTextSize(1);
    display.setTextColor(WHITE);
    Serial.println("wifi is connected");
    while (WiFi.status() != WL_CONNECTED )
    {
      delay(1000);
      Serial.println(".");
    }
  }
  Serial.begin(9600);         // Start the Serial communication to send messages to the computer
  delay(10);
  Serial.println('\n');
  display.setCursor(20, 0); //oled display
  display.setTextSize(1);
  display.setTextColor(WHITE);
  WiFi.begin(ssid, password);             // Connect to the network
  Serial.print("Connecting to ");
  display.setCursor(20, 0); //oled display
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.print("Connecting to");
  delay(1000);
  Serial.print(ssid); Serial.println(" ...");

  display.print("...");

  int i = 0;
  while (WiFi.status() != WL_CONNECTED) { // Wait for the Wi-Fi to connect
    delay(1000);
    Serial.print(++i); Serial.print(' ');
  }

  Serial.println('\n');
  display.println('\n');
  Serial.println("Connection established!");
  display.setCursor(20, 0); //oled display
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.println("Connection established!");
  delay(1000);
  Serial.print("IP address:\t");
  display.setCursor(20, 0); //oled display
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.println("IP address is:\t");
  delay(1000);
  Serial.println(WiFi.localIP());
  display.setCursor(20, 0); //oled display
  display.setTextSize(1);
  display.setTextColor(WHITE);// Send the IP address of the ESP8266 to the computer
  display.println(WiFi.localIP());
  delay(1000);
  display.display();
  display.clearDisplay();
}


void loop()
{
  //Wificonnection();
  //Blynkconnect();

  Blynk.run();
  mizaneAB();
  
}


void mizaneAB() {
  soilMoistureValue = analogRead(SensorPin);  //put Sensor insert into soil
  Serial.println(soilMoistureValue);
  soilmoisturepercent = map(soilMoistureValue, AirValue, WaterValue, 0, 100);
  if (soilmoisturepercent > 100)
  {
    Serial.println("100 %");
    display.setCursor(20, 0); //oled display
    display.setTextSize(1);
    display.setTextColor(WHITE);
    display.println("Mr.Atashnejad");
    display.setCursor(10, 17);
    display.setTextSize(2);
    display.setTextColor(WHITE);
    display.println("Mizane AB");
    display.setCursor(30, 40); //oled display
    display.setTextSize(3);
    display.setTextColor(WHITE);
    display.println("100 %");
    display.display();
    delay(250);
    display.clearDisplay();
  }
  else if (soilmoisturepercent < 0)
  {
    Serial.println("0 %");
    display.setCursor(20, 0); //oled display
    display.setTextSize(1);
    display.setTextColor(WHITE);
    display.println("Mr.atashnejad");
    display.setCursor(10, 17);
    display.setTextSize(2);
    display.setTextColor(WHITE);
    display.println("Mizane AB");
    display.setCursor(30, 40); //oled display
    display.setTextSize(3);
    display.setTextColor(WHITE);
    display.println("0 %");
    display.display();
    delay(250);
    display.clearDisplay();
    Blynk.notify(soilmoisturepercent);
    
  }
  else if (soilmoisturepercent >= 0 && soilmoisturepercent <= 100)
  {
    Serial.print(soilmoisturepercent);
    Serial.println("%");
    display.setCursor(20, 0); //oled display
    display.setTextSize(1);
    display.setTextColor(WHITE);
    display.println("Mr.atashnejad");
    display.setCursor(10, 17);
    display.setTextSize(2);
    display.setTextColor(WHITE);
    display.println("Mizane AB");
    display.setCursor(30, 40); //oled display
    display.setTextSize(3);
    display.setTextColor(WHITE);
    display.println(soilmoisturepercent);
    display.setCursor(70, 40);
    display.setTextSize(3);
    display.println(" %");
    display.display();

    delay(250);
    display.clearDisplay();
  }
}
