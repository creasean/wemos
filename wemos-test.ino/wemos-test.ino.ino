#include <SparkFun_RHT03.h>

//#include <ESP32_Servo.h>


#define PIN        D6 // On Trinket or Gemma, suggest changing this to 1
#define NUMPIXELS 64 // Popular NeoPixel ring size
#include <NTPClient.h> // change next line to use with another board/shield
#include <ESP8266WiFi.h> //#include <WiFi.h> // for WiFi shield //#include <WiFi101.h> // for WiFi 101 shield or MKR1000
#include <WiFiUdp.h>
#include <Servo.h> //Servo 라이브러리를 추가



Servo myservo;      //Servo 클래스로 servo객체 생성
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
  pinMode(LED_BUILTIN, OUTPUT);  // Initialize the LED_BUILTIN pin as an output
  myservo.attach(2);  // attaches the servo on GIO2 to the servo object
    
  while ( WiFi.status() != WL_CONNECTED ) {
    delay ( 500 );
    Serial.print ( "try to connecting.." );
    Serial.println (""); 
    
  }
}

void loop() {
  digitalWrite(LED_BUILTIN, HIGH);  // Turn the LED on (Note that LOW is the voltage level
  update_cur_time();
  print_time();
  delay(500);
  digitalWrite(LED_BUILTIN, LOW);  // Turn the LED off by making the voltage HIGH
  delay(500);                      // Wait for two seconds (to demonstrate the active low LED)

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

void update_cur_time(){
  timeClient.update();
  time_t cur_time = timeClient.getEpochTime();
  struct tm *ptm = gmtime ((time_t*)&cur_time);
  hour=ptm->tm_hour;
  minute=ptm->tm_min;
  sec=ptm->tm_sec;
}
