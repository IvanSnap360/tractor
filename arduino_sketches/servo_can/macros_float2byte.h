#pragma MACROS_FL2BYTE_H

union float2byte
{ 
  float float_value;
  byte float_bytes[sizeof(float)];
} fl2byte;
