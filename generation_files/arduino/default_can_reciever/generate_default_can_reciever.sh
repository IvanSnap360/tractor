#!/bin/bash
echo "Write arduino program name:"
read program_name

mkdir ../../../arduino_sketches/"$program_name"
cp default_can_reciever.ino ../../../arduino_sketches/"$program_name"/
cp macros_float2byte.h ../../../arduino_sketches/"$program_name"/
cp macros_int2byte.h ../../../arduino_sketches/"$program_name"/
cp macros_double2byte.h ../../../arduino_sketches/"$program_name"/
mv ../../../arduino_sketches/"$program_name"/default_can_reciever.ino ../../../arduino_sketches/"$program_name"/"$program_name".ino

echo "Done"
