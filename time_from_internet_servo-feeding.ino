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
}

void loop() {
//==
  if (minute%2==0){
    Serial.print(" =LED ON= ");             
    pixels.setBrightness(100);
    for(int i=0; i<NUMPIXELS; i++) { // For each pixel...
    int a=0;
    a=i*2+1;
    pixels.setPixelColor(a, pixels.Color(100, 100, 100));
    pixels.show();   // Send the updated pixel colors to the hardware.
//  delay(100);
   }

//=servo=
    servo.attach(D7);     //servo 서보모터 7번 핀에 연결
    servo.write(0); //value값의 각도로 회전. ex) value가 90이라면 90도 회전

      for (int a=0;a<5;a++){
      //for1 시작, 10회 반복

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
  else{
  servo.detach();
  Serial.print("=LED OFF=");
  pixels.clear();
  pixels.show();  
  }
  Serial.println (""); 
//  delay(1000);
//==

  
    update_cur_time();
    Serial.print ( hour);
    Serial.print ( ":" );    
    Serial.print (minute);
    Serial.print ( ":" );    
    Serial.print (sec);        
    Serial.print ("  /  ");

/*    
    Serial.print ("다음 공급까지 남은시간(");             
    Serial.print (remain_h);
    Serial.print ( ":" );                    
    Serial.print (remain_m);       
    Serial.print (")");
    Serial.println ("");
             
    value = 0;
    servo.write(value); //value값의 각도로 회전. ex) value가 90이라면 90도 회전
    delay(500);

    for (int i=0;i<180;i++){
    servo.write(i);
    delay(20);
    }
    for (int i=180;i>0;i--){
    servo.write(i);
    delay(20);
    }
    
  delay(1000);
*/
}

void update_cur_time(){
  timeClient.update();
  time_t cur_time = timeClient.getEpochTime();
  struct tm *ptm = gmtime ((time_t*)&cur_time);
  hour=ptm->tm_hour;
  minute=ptm->tm_min;
  sec=ptm->tm_sec;

/*
//아랫 부분은 고칠 필요가있음 시간곱하기 60 더하기 잔여 분수로 해서 분단위로 구한 후
//나머지 시간을 다시 60으로 나누어 몫과 나머지로 표시하기
  remain_m=60-minute;
  if (remain_m==0){
      remain_h=4-hour%6;
  }else{
      remain_h=3-(hour%6);    
  }
*/

  
}
