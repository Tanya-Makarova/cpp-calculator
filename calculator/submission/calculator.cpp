#include <iostream>
#include <string>
#include <cmath>

#include "calculator.h"

using namespace std::literals;

bool Calculator::ReadNumber(Number& result) {
    if (!(std::cin >> result)) {
        std::cerr << "Error: Numeric operand expected"s << std::endl;
        return false;
    }
    return true;
}
void Calculator::Set(Number n) {
    current_number_ = n;
}
Number Calculator::GetNumber() const {
    return current_number_;
}
void Calculator::Add(Number n) {
    current_number_ += n;
}
void Calculator::Sub(Number n) {
    current_number_ -= n;
}
void Calculator::Div(Number n) {
    current_number_ /= n;
}
void Calculator::Mul(Number n) {
    current_number_ *= n;
}
void Calculator::Pow(Number n) {
    current_number_ = pow(current_number_, n);
}
bool Calculator::HasMem() const {
    return is_memory_;
}
void Calculator::Save() {
    remembered_number_ = current_number_;
    is_memory_ = true;
}

void Calculator::ClearMemory() {
    is_memory_ = false;
}
void Calculator::Load() {
    current_number_ = remembered_number_;
}

std::string Calculator:: GetNumberRepr() const {
    return std::to_string(current_number_);
}
