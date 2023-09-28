#include <SparkFun_RHT03.h>
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
// The pins for I2C are defined by the Wire-library. 
// On an arduino WEMOS D1 mini lite:       D1(SCL), D2(SDA)
#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3C ///< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
const int RHT03_DATA_PIN = 12; // RHT03 data pin

RHT03 rht;

void setup() {
  Serial.begin(115200); // Serial is used to print sensor readings.
  rht.begin(RHT03_DATA_PIN);// Call rht.begin() to initialize the sensor and our data pin
  if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
      Serial.println(F("SSD1306 allocation failed"));}

  display.display();
  delay(2000);
  display.clearDisplay();  // Clear the buffer
  display.drawPixel(10, 10, SSD1306_WHITE);  // Draw a single pixel in white
  // Show the display buffer on the screen. You MUST call display() after
  // drawing commands to make them visible on screen!
  display.display();
  delay(2000);

  testdrawstyles();    // Draw 'stylized' characters
  display.clearDisplay();
  display.display();
}

void loop()
{

  // Call rht.update() to get new humidity and temperature values from the sensor.
  int updateRet = rht.update();
  float latestHumidity = rht.humidity();
  float latestTempC = rht.tempC();
  // If successful, the update() function will return 1.
  // If update fails, it will return a value <0
  if (updateRet == 1)
  {
    // The humidity(), tempC(), and tempF() functions can be called -- after 
    // a successful update() -- to get the last humidity and temperature
    // value 
    //float latestHumidity = rht.humidity();
    //float latestTempC = rht.tempC();
    // Now print the values:
    Serial.println("Humidity: " + String(latestHumidity, 1) + " %");
    Serial.println("Temp (C): " + String(latestTempC, 1) + " deg C");
  }
  else
  {
    // If the update failed, try delaying for RHT_READ_INTERVAL_MS ms before
    // trying again.
    delay(RHT_READ_INTERVAL_MS);
  }
//====

  display.clearDisplay();
  display.setTextSize(1);             // Normal 1:1 pixel scale
  display.setTextColor(SSD1306_WHITE);        // Draw white text
  display.setCursor(0,0);             // Start at top-left corner
  display.println("Humidity: " + String(latestHumidity, 1) + " %");
  display.println("AIR Temp: " + String(latestTempC, 1) + " C");
  display.display();
  delay(500);
}

void testdrawstyles(void) {
  display.clearDisplay();

  display.setTextSize(1);             // Normal 1:1 pixel scale
  display.setTextColor(SSD1306_WHITE);        // Draw white text
  display.setCursor(0,30);             // Start at top-left corner
  display.println(F("Smart Fish Bowl"));
  display.println(F("System initializing!"));
/*
  display.setTextColor(SSD1306_BLACK, SSD1306_WHITE); // Draw 'inverse' text
  display.println(3.141592);

  display.setTextSize(2);             // Draw 2X-scale text
  display.setTextColor(SSD1306_WHITE);
  display.print(F("0x")); display.println(0xDEADBEEF, HEX);
*/
  display.display();
  delay(2000);
}
