union float2byte
{ 
  int integer_value;
  byte integer_bytes[sizeof(int)];
} int2byte;