#include "calculator.h"
#include <iostream>
#include <cmath>
#include <string>

bool ReadNumber(Number& entered_digit) {
    if(std::cin >> entered_digit) return true;
    else {
        std::cerr << "Error: Numeric operand expected" << std::endl;
        return false;
    }
}

bool RunCalculatorCycle() {
    Number current_number;
    if(!ReadNumber(current_number)) return false;

    Number remembered_number = 0.0;
    bool is_memory = false;

    std::string operation;
    while(std::cin >> operation) {
        if(operation == "s") {
            is_memory = true;
            remembered_number = current_number;
        }
        else if(operation == "l") {
            if(!is_memory) {
                std::cerr << "Error: Memory is empty" << std::endl;
                return false;
            }
            current_number = remembered_number;
        }
        else if(operation == "=") {
            std::cout << current_number << std::endl;
        }
        else if(operation == "c") current_number = 0.0;
        else if(operation == "q") return true;
        else if(operation == "+" || operation == "-" ||
                operation == "*" || operation == "/" ||
                operation == "**" || operation == "root" ||
                operation == ":") {
                    Number operand;
                    if(!ReadNumber(operand)) return false;

                    if(operation == "+") current_number += operand;
                    else if(operation == "-") current_number -= operand;
                    else if(operation == "*") current_number *= operand;
                    else if(operation == "**") current_number = std::pow(current_number, operand);
                    else if(operation == ":") current_number = operand;
                    else if(operation == "/") {
                        // Важно сделать бесконечность с правильным знаком
                        current_number = (current_number == 0.0) ? 1.0 : current_number;
                        current_number = current_number / operand;
                    }
                    // Добавляю команду от себя - взятие корня
                    else if(operation == "root") {
                        if(current_number < 0) std::cout << "inf" << std::endl;
                        else current_number = std::pow(current_number, 1.0 / operand);
                    }
                }
                else {
                    std::cerr << "Error: Unknown token " << operation << std::endl;
                    return false;
                }
    }
    return false; // Если строка закончилась не командой q
}