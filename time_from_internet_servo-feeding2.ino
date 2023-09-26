//===============
#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
#include <avr/power.h> // Required for 16 MHz Adafruit Trinket
#endif
#define PIN        D6 // On Trinket or Gemma, suggest changing this to 1
#define NUMPIXELS 64 // Popular NeoPixel ring size
Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

#include <NTPClient.h>
// change next line to use with another board/shield
#include <ESP8266WiFi.h>
//#include <WiFi.h> // for WiFi shield
//#include <WiFi101.h> // for WiFi 101 shield or MKR1000
#include <WiFiUdp.h>

#include<Servo.h> //Servo 라이브러리를 추가
Servo servo;      //Servo 클래스로 servo객체 생성
int value = 0;    // 각도를 조절할 변수 value

const char *ssid     = "iptime-home";
const char *password = "js4u2014";
const long utcOffsetInSeconds = 9*3600; //우리나라 표준시 적용하기 위해  GMT+9

WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, utcOffsetInSeconds);

//현재 시간을 저장할 변수
int hour;
int minute;
int sec;
int remain_h;
int remain_m;

void setup(){
  Serial.begin(115200);
    WiFi.begin(ssid, password);
  while ( WiFi.status() != WL_CONNECTED ) {
    delay ( 500 );
    Serial.print ( "." );
  }
//  servo.attach(D7);     //servo 서보모터 7번 핀에 연결
                       // 이때 ~ 표시가 있는 PWM을 지원하는 디지털 핀에 연결

//===
  pixels.begin(); // INITIALIZE NeoPixel strip object (REQUIRED)
//===                       
} //setup() END


void loop() {

  if (hour<=19 && minute%5==0){
    Serial.print(" =LED ON= ");             
    neopixel_on();
    feeding_servo(3);
   }
  else{
  servo.detach();
  neopixel_off();
  }

  Serial.println (""); 
  
    update_cur_time();
    Serial.print ( hour);
    Serial.print ( ":" );    
    Serial.print (minute);
    Serial.print ( ":" );    
    Serial.print (sec);        
    Serial.print ("  /  ");
}

void update_cur_time(){
  timeClient.update();
  time_t cur_time = timeClient.getEpochTime();
  struct tm *ptm = gmtime ((time_t*)&cur_time);
  hour=ptm->tm_hour;
  minute=ptm->tm_min;
  sec=ptm->tm_sec;
}

void feeding_servo(int feeds){
    servo.attach(D7);     //servo 서보모터 7번 핀에 연결
    servo.write(0); //value값의 각도로 회전. ex) value가 90이라면 90도 회전

      for (int a=0;a<feeds;a++){
      //for1 시작, 회 반복

        for (int i=0;i<180;i++){
         servo.write(i);
         delay(10);
        }
        delay(500);
        for (int i=179;i>0;i--){
         servo.write(i);
         delay(10);
        }
        delay(500);

      }
}

void neopixel_on(){
    pixels.setBrightness(100);
    for(int i=0; i<NUMPIXELS; i++) { // For each pixel...
    int a=0;
    a=i*2+1;
    pixels.setPixelColor(a, pixels.Color(100, 100, 100));
    pixels.show();   // Send the updated pixel colors to the hardware.
//  delay(100);
  }
}
  
void neopixel_off(){
  Serial.print("=LED OFF=");
  pixels.clear();
  pixels.show();  
}
