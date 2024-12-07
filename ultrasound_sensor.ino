const int trig_pin = 11;
const int echo_pin = 13;

void setup() {
  pinMode(trig_pin, OUTPUT);
  pinMode(echo_pin, INPUT);
    
  Serial.begin(115200);
}

void loop() {
  digitalWrite(trig_pin, LOW);
  delayMicroseconds(2);
  digitalWrite(trig_pin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig_pin, LOW);
  
  long duration = pulseIn(echo_pin, HIGH);
  long distance = duration / 58;
  
  Serial.print(distance);
  Serial.println(" cm");
  
  delay(1000);
}