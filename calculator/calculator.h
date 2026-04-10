#pragma once
#include <iostream>

using Number = double;

// Возвращает true, если удалось прочитать число
// и сохранить его в Number.
bool ReadNumber(Number& entered_digit);

enum class Operation {
    Memory,     // s
    Load,       // l
    Print,      // =
    Clear,      // c
    Quit,       // q
    Addition,   // +
    Subtract,   // -
    Mul,        // *
    Div,        // /
    Pow,        // **
    Root,       // root
    Assign,     // :
    Unknown
};
//Преобразовываем строку операции в конкретный тип
Operation StringToOperation(const std::string& operation); 

bool Calculate(Number& curr_number, Operation operation, Number operand);

// Возвращает true, если работа завершилась командой q.
// Если ошибкf - возвращает false.
bool RunCalculatorCycle();
