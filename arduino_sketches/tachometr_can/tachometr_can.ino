#include <mcp_can.h>
#include <SPI.h>
#define ID 0xF3
const int SPI_CS_PIN = 10;
volatile unsigned long count = 0;
float reduction = 61.0 / 38.0;
unsigned long last_time = 0;
float rpm = 0.0;
MCP_CAN CAN(SPI_CS_PIN);
void setup() {
  //  Serial.begin(9600);
  attachInterrupt(0, isr, RISING);
  while (CAN_OK != CAN.begin(CAN_1000KBPS));
}

void isr()
{
  count++;
}
 byte a,b,c,d = 0;
byte stmp[8] = {0, 0, 0, 0, 0, 0, 0, 0};
void loop() {
  if (millis() - last_time >= 1000)
  {
    //    Serial.println(((count / 6.0)* reduction) * 60.0);
    rpm = ((count / 6.0) * reduction) * 60.0;
    float_to_bytes(rpm);
    stmp[0] = a;
    stmp[1] = b;
    stmp[2] = c;
    stmp[3] = d;
    stmp[4] = 0;
    stmp[5] = 0;
    stmp[6] = 0;
    stmp[7] = 0;
    CAN.sendMsgBuf(ID, 0, 8, stmp);
    count = 0;
    last_time = millis();
  }
}



void float_to_bytes(float data1)
{
  union myval
  {
    float fl;
    int8_t bytes[4];
  } x;
  x.fl = data1;
  a=x.bytes[0];
  b=x.bytes[1];
  c=x.bytes[2];
  d=x.bytes[3];
}
