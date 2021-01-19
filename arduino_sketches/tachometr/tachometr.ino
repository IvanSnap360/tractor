#define TACH_PIN 2  // пин тахометра (желательна внешняя подтяжка 10к к VCC)
#include "tachometr_lib.h"
Tacho tacho;
void setup() {
  Serial.begin(9600);
  pinMode(TACH_PIN, INPUT);  // тахо пин вентилятора тянем к VCC
  attachInterrupt(0, isr, RISING); // настраиваем прерывание
}
// обработчик прерывания
void isr() {
  tacho.tick();   // дёргаем тик
}
void loop() {
  // выводим два раза в секунду
  Serial.println(tacho.getRPM());   // вывод оборотов в минуту
  //Serial.println(tacho.getHz());  // вывод Герц
  //Serial.println(tacho.getPeriod());  // вывод периода
  delay(500);
}
