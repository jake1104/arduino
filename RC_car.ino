#include <SoftwareSerial.h>

// motor pin
#define Lmotor_A1A   6
#define Lmotor_A1B   5
#define Rmotor_B1A   11
#define Rmotor_B1B   10

// bluetooth pin
#define BT_TX     7
#define BT_RX     8

SoftwareSerial bts(BT_TX, BT_RX); // 블루투스 시리얼에 필요한 객체
byte car_speed = 255; // motor 속도(0~255)

void setup() {
  Serial.begin(9600); // 시리얼 통신 준비
  bts.begin(9600); // 블루투스 소프트웨어 시리얼 통신 준비
  pinMode(Lmotor_A1A, OUTPUT); // motor 출력모드
  pinMode(Lmotor_A1B, OUTPUT);
  pinMode(Rmotor_B1A, OUTPUT);
  pinMode(Rmotor_B1B, OUTPUT);
}
void loop() {
  if(bts.available() > 1) { // 앱으로 부터 아두이노로 들어온 데이터가 1개보다 크면
    char buf[2];
    bts.readBytes(buf,2); // 값 2개 읽기
    //Serial.print((char)buf[0]); // 들어온 데이터를 시리얼모니터로 확인해보기
    //Serial.println((byte)buf[1]); // 확인해 보기
    if(buf[0] == 'c') { // buf[0]이 c이면
      if(buf[1] == 1) forward(); //  buf[1]이 1이면 전진
      else if(buf[1] == 2) backward(); // 2이면 후진
      else if(buf[1] == 3) left(); // 3이면 좌회전
      else if(buf[1] == 4) right(); // 4이면 우회전
      else stop_car(); // 그외의 값이면 정지
      //Serial.println(data2); // 확인해 보기
    }
    else if(buf[0] == 's') { // buf[0]이 s이면
      car_speed = buf[1]; // 속도값 조절
    }
    delay(5);
  }
}
void stop_car() {  // 정지 함수
  digitalWrite(Lmotor_A1A, LOW); // 모든신호를 LOW로(-전기)
  digitalWrite(Lmotor_A1B, LOW);
  digitalWrite(Rmotor_B1A, LOW);
  digitalWrite(Rmotor_B1B, LOW);
}

void left() { // 좌회전
  analogWrite(Lmotor_A1A, car_speed); //왼쪽모터 A1A +전기
  digitalWrite(Lmotor_A1B, LOW);  //왼쪽모터 A1B -전기
  digitalWrite(Rmotor_B1A, LOW);  //오른쪽모터 B1A -전기
  analogWrite(Rmotor_B1B, car_speed); //오른쪽모터 B1B +전기
}

void right() { // 우회전
  digitalWrite(Lmotor_A1A, LOW); //왼쪽모터 A1A -전기
  analogWrite(Lmotor_A1B, car_speed);//왼쪽모터 A1B +전기
  analogWrite(Rmotor_B1A, car_speed);//오른쪽모터 B1A +전기
  digitalWrite(Rmotor_B1B, LOW); //오른쪽모터 B1B -전기
}

void forward() { // 전진
  digitalWrite(Lmotor_A1A, LOW);  //왼쪽모터 A1A -전기
  analogWrite(Lmotor_A1B, car_speed); //왼쪽모터 A1B +전기
  digitalWrite(Rmotor_B1A, LOW);  //오른쪽모터 B1A -전기
  analogWrite(Rmotor_B1B, car_speed); //오른쪽모터 B1B +전기
}

void backward() { // 후진
  analogWrite(Lmotor_A1A, car_speed);//왼쪽모터 A1A +전기
  digitalWrite(Lmotor_A1B, LOW); //왼쪽모터 A1B -전기
  analogWrite(Rmotor_B1A, car_speed);//오른쪽모터 B1A +전기
  digitalWrite(Rmotor_B1B, LOW); //오른쪽모터B1B -전기
}
