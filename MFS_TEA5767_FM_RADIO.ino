// http://un7fgo.gengen.ru (C) 2019
// https://github.com/UN7FGO 
// 
// Скетч FM-приемника для модулей Multi Function Shield и TEA5767.

// подключаем библиотеку для Multi Function Shield
#include <MFShield.h>
// подключаем бибилиотеку для I2C интерфейса
#include <Wire.h>
// подключаем библиотеку для модуля TEA5767
#include <TEA5767N.h>

// определяем назначение кнопок на Multi Function Shield
#define BUTTON_START  2
#define BUTTON_PLUS   3
#define BUTTON_MINUS  1

// создаем объекты для модулей 
MFShield mfs;
TEA5767N radio = TEA5767N();

// создаем переменную и устанавливаем начальную частоту
// частота хранится в целых значениях, а на модуль отпарвляем ее деленную на 10
int freq = 1029;
uint32_t t; 

// Обрабатываем нажатия клавиш
void keyAction (uint8_t key)
{
  switch (key)
  {
    // увеличиваем частоту на 0.1 МГц
    case BUTTON_PLUS:
      freq += 1;
      break;

    // увеличиваем частоту на 0.1 МГц
    case BUTTON_MINUS:
      freq -= 1;
      break;

    // отпарвляем текущее значение частоты в модуль ФМ-приемника
    case BUTTON_START:
      mfs.showDisplay (false);
      radio.setStandByOn();
      radio.selectFrequency(float(freq) / 10);
      radio.setStandByOff();
      mfs.showDisplay (true);
      break;
  }
  // выводим текущую частоту на индикатор
  mfs.display(freq, true);     
}
/* =================================================== */
void setup() {
  // выключаем радио, если оно было включено
  radio.setStandByOff();
  // привязываем нашу функцию обработки кнопок к объекту Multi Function Shield
  mfs.onKeyPress (keyAction);
  // отправляем текущую частоту в модуль ФМ-радио
  radio.selectFrequency(float(freq) / 10);
}

void loop() {
  // выводим текущую частоту на индикатор
  mfs.display(freq, true);
  mfs.loop(); 
}
