volatile unsigned long count = 0;
float reduction = 61.0 / 38.0;
unsigned long last_time = 0;
double rpm = 0.0;

void setup() {
//  Serial.begin(9600);
  attachInterrupt(0, isr, RISING);

}

void isr()
{
  count++;
}
void loop() {
  if (millis() - last_time >= 1000)
  {
//    Serial.println(((count / 6.0)* reduction) * 60.0);
    rpm = (count / 6.0)* reduction) * 60.0;
    count = 0;
    last_time = millis();
  }
  

}
