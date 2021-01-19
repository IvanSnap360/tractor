void setup() {
  Serial.begin(9600);
  pinMode(2, OUTPUT);
  pinMode(4, OUTPUT);
  relay1(false);
  relay2(false);
}
bool relay_1_st = false;
bool relay_2_st = false;
void loop() 
{
  if (Serial.available() > 0)
  {
    char data = (char)Serial.read();
    Serial.println(data);
    if (data == 'p')
    {
      relay_1_st = !relay_1_st;
    }
    if (data == 's')
    {
      relay_2_st = !relay_2_st;
    }
    relay1(relay_1_st);
    relay2(relay_2_st);
  }
  
}

void relay1(bool st)
{
  digitalWrite(2, st);
}
void relay2(bool st)
{
  digitalWrite(4, st);
  digitalWrite(6, 0);
}
