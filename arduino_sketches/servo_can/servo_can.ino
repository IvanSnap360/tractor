#include <mcp_can.h>
#include <SPI.h>
#include "macros_float2byte.h"
#include "macros_int2byte.h"
#include "macros_double2byte.h"


/////////////////////////////////////////////////////////////////////////////////////
#define SEARCHING_MESSAGE_ID 0x00     // id сообщения по которому будет проходить фильтрация
#define CAN_SPEED CAN_1000KBPS        // скорость can шиныы
#define SPI_CHIP_SELECT_PIN 10        // пин выбора чипа (CS)
// #define DEBUG                         // режим отладка (закометировать если не надо)  
/////////////////////////////////////////////////////////////////////////////////////

MCP_CAN CAN(SPI_CHIP_SELECT_PIN); // объявляем объект CAN с пином выбора чипа (CS) 

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
    CAN.init_Filt(0,8,SEARCHING_MESSAGE_ID); // фильтр сообщений по SEARCHING_MESSAGE_ID
    CAN.readMsgBuf(&len, buf); // читатель сообщений

    fl2byte.float_bytes[0] = buf[0];
    fl2byte.float_bytes[1] = buf[1];
    fl2byte.float_bytes[2] = buf[2];
    fl2byte.float_bytes[3] = buf[3];

    float pos = fl2byte.float_value;

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