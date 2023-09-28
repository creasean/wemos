#include <Servo.h>//서보모터 라이브러리 불러와 사용

Servo servo1;  // 서보 모터 객체 생성

void setup() {
 servo1.attach(2);  // 서보 모터를 연결한 핀 번호를 사용하여 초기화
 servo1.writeMicroseconds(500);  // 초기 위치 설정 (90도)
  delay(1000);  // 초기 위치에서 1초 대기
}

void loop() {
  feeding();  // feeding 함수 호출
}

void setAngle(int angle) {
  int pulseWidth = map(angle, -90, 90, 500, 2500);  // 각도를 펄스 너비로 변환
  servo1.writeMicroseconds(pulseWidth);  // 서보 모터 위치 설정
  delay(10);  // 각도 변경 후 일정 시간 대기
}

void feeding() {
  int i = -90;  // 시작 각도 설정 (-90도)
  
  while (i <= 90) {
    setAngle(i);  // 각도 설정 함수 호출
    delay(20);  // 10밀리초 대기
    i++;  // 각도 증가
  }

  delay(1000);  // 최대 위치에서 1초 대기
  
  while (i >= -180) {
    setAngle(i);  // 각도 설정 함수 호출
    delay(20);  // 10밀리초 대기
    i--;  // 각도 감소
  }
}
