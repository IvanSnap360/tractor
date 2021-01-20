#include <mcp_can.h>
#include <SPI.h>

////////////////////////////////////////////////////////
#define ID 0xF3
const int SPI_CS_PIN = 10;
#define FLOAT_SIZE sizeof(float)
#define CAN_SPEED CAN_1000KBPS
#define SENSOR_PIN 2
////////////////////////////////////////////////////////

volatile unsigned long count = 0;
float reduction = 61.0 / 38.0;
unsigned long last_time = 0;
float rpm = 0.0;

MCP_CAN CAN(SPI_CS_PIN);

void setup() {
  //  Serial.begin(9600);
  attachInterrupt(digitalPinToInterrupt(SENSOR_PIN), isr, RISING);
  while (CAN_OK != CAN.begin(CAN_SPEED));
}

void isr()
{
  count++;
}

byte stmp[8] = {0, 0, 0, 0, 0, 0, 0, 0};

union float2can
{ 
  float float_value;
  byte float_bytes[FLOAT_SIZE];
} fl2can;

void loop() 
{
  if (millis() - last_time >= 1000)
  {
    //    Serial.println(((count / 6.0)* reduction) * 60.0);
    rpm = ((count / 6.0) * reduction) * 60.0;
    
    fl2can.float_value = rpm;
    stmp[0] = fl2can.float_bytes[0];
    stmp[1] = fl2can.float_bytes[1];
    stmp[2] = fl2can.float_bytes[2];
    stmp[3] = fl2can.float_bytes[3];
    stmp[4] = 0;
    stmp[5] = 0;
    stmp[6] = 0;
    stmp[7] = 0;
    CAN.sendMsgBuf(ID, 0, 8, stmp);
    count = 0;
    last_time = millis();
  }
}

