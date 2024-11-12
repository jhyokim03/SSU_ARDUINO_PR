#define FSR A0 // FSR 압력 센서의 핀 번호를 선언
#define TRIG 11
#define ECHO 13
#define BUZZER 8

int sensor = 0; // 압력 센서로 측정한 값을 저장할 변수
// cnt와 cnt2로 노이즈 현상과 부저의 무한 반복을 방지함
int cnt = 0;
int cnt2 = 1; // cnt2를 0으로 주면 처음부터 부저가 울리게 됨
void setup() {

  pinMode(TRIG, OUTPUT);
  pinMode(ECHO, INPUT);
  pinMode(FSR, INPUT);
  pinMode(BUZZER, OUTPUT);
  Serial.begin(9600);

}

void loop() {
  sensor = analogRead(FSR);
  long duration, distance;

  digitalWrite(TRIG, LOW);
  delayMicroseconds(2);

  digitalWrite(TRIG, HIGH);
  delayMicroseconds(10);

  digitalWrite(TRIG, LOW);

  duration = pulseIn (ECHO, HIGH);

  distance = duration * 17 / 1000;

  if (sensor > 300 && distance > 50) // 기준치는 조정 예정
  {
    // 압력 센서에 힘이 감지되면 cnt는 10으로 계속 초기화됨
    cnt = 10;
    // cnt2는 부저의 무한 반복을 방지하기 위한 변수로, 센서에 힘이 감지되면 0이 됨
    cnt2 = 0;
  }
  
  // 매 루프마다 cnt의 값이 줄어들다가, 센서에 힘이 더이상 감지되지 않을 경우, 끝내는 0이 됨
  if (cnt != 0)
    cnt--;
  
  // 힘이 감지되지 않은지 일정 시간이 지날 경우 부저가 울리게 함
  else if (cnt == 0 && cnt2 == 0)
  {
    tone(8, 392);
    delay(200);
    
    tone(8, 440);
    delay(200);
    
    tone(8, 494);
    delay(200);
    
    noTone(8);
    delay(500);
    
    // 부저가 한 번 울리고 나면 cnt2를 1로 바꿔 무한반복을 방지함
    cnt2 = 1;
  }

  // 잘 작동되는지 확인
  Serial.print("sensor = ");
  Serial.println(sensor);
  Serial.print("cnt = ");
  Serial.println(cnt);

  Serial.print("time = ");
  Serial.println(duration);
  Serial.print("cm = ");
  Serial.println(distance);

  Serial.print("-------------\n");
  
  delay(200); // cnt가 10에서 0이 되려면 2초가 필요함
}
