#pragma once
#include <string>

using Number = double;

class Calculator {
public:
    bool ReadNumber(Number& result);
    bool RunCalculatorCycle();
    void Set(Number n);
    Number GetNumber() const;
    void Add(Number n);
    void Sub(Number n);
    void Div(Number n);
    void Mul(Number n);
    void Pow(Number n);
    void Save();
    void Load();
    void ClearMemory();
    bool HasMem() const;
    std::string GetNumberRepr() const;
private:
    double current_number_ = 0;
    bool is_memory_ = false;
    double remembered_number_ = 0;
};

