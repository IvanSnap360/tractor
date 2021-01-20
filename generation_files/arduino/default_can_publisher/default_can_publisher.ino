#include <mcp_can.h>
#include <SPI.h>
#include "macros_float2byte.h"
#include "macros_int2byte.h"
#include "macros_double2byte.h"

/////////////////////////////////////////////////////////////////////////////////////
#define PUBLISH_MESSAGE_ID 0x00     // id сообщения по которому будет проходить фильтрация
#define CAN_SPEED CAN_1000KBPS        // скорость can шиныы
#define SPI_CHIP_SELECT_PIN 10        // пин выбора чипа (CS)
// #define DEBUG                         // режим отладка (закометировать если не надо)  
#define PUBLISH_RATE_MS 1000            // период публикации в миллисекундах
/////////////////////////////////////////////////////////////////////////////////////

MCP_CAN CAN(SPI_CHIP_SELECT_PIN); // объявляем объект CAN с пином выбора чипа (CS) 
unsigned long last_publish_time = 0.0;
void setup()
{
    #if defined(DEBUG)
        Serial.begin(9600);
    #endif
    while (CAN_OK != CAN.begin(CAN_SPEED)); // ждем пока can конвертер не включится
}

void loop()
{
    unsigned char len = 0;
    unsigned char buf[8]; // <----- массив из которого надо брать данные
    if (millis() - last_publish_time >=  PUBLISH_RATE_MS)
    {
        CAN.sendMsgBuf(PUBLISH_MESSAGE_ID, 0, 8, buf);
        last_publish_time = millis();
    }
    #ifdef DEBUG
        Serial.print("MESSAGE ID: ");
        Serial.print(SEARCHING_MESSAGE_ID);
        Serial.print(" [ ");
        for (int i = 0; i < 8; i++)
        {
            Serial.print(buf[i], HEX);
            Serial.print(", ");
        }
        Serial.println("]");
    #endif
}