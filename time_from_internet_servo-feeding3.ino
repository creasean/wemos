#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
#include <avr/power.h> // Required for 16 MHz Adafruit Trinket
#endif
#define PIN        D6 // On Trinket or Gemma, suggest changing this to 1
#define NUMPIXELS 64 // Popular NeoPixel ring size
Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);
#include <NTPClient.h> // change next line to use with another board/shield
#include <ESP8266WiFi.h> //#include <WiFi.h> // for WiFi shield //#include <WiFi101.h> // for WiFi 101 shield or MKR1000
#include <WiFiUdp.h>
#include<Servo.h> //Servo 라이브러리를 추가

Servo servo;      //Servo 클래스로 servo객체 생성
int value = 0;    //각도를 조절할 변수 value
int swch = 1;    //5분단위로 끄고 켜기 위해서 변수 생성 테스트용

const char *ssid     = "iptime-home"; //우리집 와이파이 이름
const char *password = "js4u2014";    //우리집 와이파이 비번
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
  pixels.begin(); // INITIALIZE NeoPixel strip object (REQUIRED)
  while ( WiFi.status() != WL_CONNECTED ) {
    delay ( 500 );
    Serial.print ( "." );
    for(int a=1;a<65;a++){pixels.setPixelColor(a, pixels.Color(0, 250, 0));}
    pixels.show();   // Send the updated pixel colors to the hardware.    
  }
}

void loop() {
//  if ( minute%2==0 && sec==0){swch=swch*-1; }
//  if (swch>0){feeding_servo(1);}  

  if(hour>=18){neopixel_on();}
  else{neopixel_off();}

/* 서보모터 테스트용 무한 반복
  servo.attach(D5);     //servo 서보모터 5번 핀에 연결
  servo.write(0); //value값의 각도로 회전. ex) value가 90이라면 90도 회전
    for (int i=0;i<180;i++){
      servo.write(i);
      delay(30);
    }

    for (int i=179;i>0;i--){
      servo.write(i);
      delay(30);
    }
  delay(200);
서보모터 테스트용 무한 반복 */
 
  if (hour==18 && minute==01){feeding_servo();}
  else{servo.detach();}
  update_cur_time();
  print_time();
  delay(1000);

}

void update_cur_time(){
  timeClient.update();
  time_t cur_time = timeClient.getEpochTime();
  struct tm *ptm = gmtime ((time_t*)&cur_time);
  hour=ptm->tm_hour;
  minute=ptm->tm_min;
  sec=ptm->tm_sec;
}

void feeding_servo(){
  servo.attach(D5);     //servo 서보모터 5번 핀에 연결
  servo.write(0); //value값의 각도로 회전. ex) value가 90이라면 90도 회전
    Serial.print("");
    Serial.print("먹이타임");

    for (int i=0;i<180;i++){
      servo.write(i);
      delay(15);
    }
    delay(200);
    for (int i=179;i>0;i--){
      servo.write(i);
      delay(15);
    }
    
  servo.detach();
  delay(60000);
}

void neopixel_on(){
  Serial.print(" =LED ON= ");
  pixels.setBrightness(100);
  for(int i=0; i<NUMPIXELS; i++) { // For each pixel...
    int a=0;
    a=i*2+1;
    pixels.setPixelColor(a, pixels.Color(100, 100, 100));
    pixels.show();   // Send the updated pixel colors to the hardware.
  }
}
  
void neopixel_off(){
  Serial.print("=LED OFF=");
  pixels.clear();
  pixels.show();  
}

void print_time(){
    Serial.println (""); 
    Serial.print ( hour);
    Serial.print ( ":" );    
    Serial.print (minute);
    Serial.print ( ":" );    
    Serial.print (sec);        
    Serial.print ("  /  ");
  }
