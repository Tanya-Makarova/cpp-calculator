#pragma once
#include <iostream>

using Number = double;

// Возвращает true, если удалось прочитать число
// и сохранить его в Number.
bool ReadNumber(Number& entered_digit);

// Возвращает true, если работа завершилась командой q.
// Если ошибкf - возвращает false.
bool RunCalculatorCycle();
