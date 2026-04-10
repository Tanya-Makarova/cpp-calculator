#include "calculator.h"
#include <iostream>
#include <cmath>
#include <string>

bool ReadNumber(Number& entered_digit) {
    if(std::cin >> entered_digit) 
        return true;
    std::cerr << "Error: Numeric operand expected" << std::endl;
    return false;
}

Operation StringToOperation(const std::string& operation) {
    if (operation == "s")
        return Operation::Memory;
    if (operation == "l")
        return Operation::Load;
    if (operation == "=")    
        return Operation::Print;
    if (operation == "c")
        return Operation::Clear;
    if (operation == "q")    
        return Operation::Quit;
    if (operation == "+")    
        return Operation::Addition;
    if (operation == "-")    
        return Operation::Subtract;
    if (operation == "*")    
        return Operation::Mul;
    if (operation == "/")   
        return Operation::Div;
    if (operation == "**")   
        return Operation::Pow;
    if (operation == "root") 
        return Operation::Root;
    if (operation == ":")    
        return Operation::Assign;
    return Operation::Unknown;
}

bool Calculate(Number& current_number, Operation operation, Number operand) {
    switch (operation) {
        case Operation::Addition:
            current_number += operand;
            break;
        case Operation::Subtract:
            current_number -= operand;
            break;
        case Operation::Mul:
            current_number *= operand;
            break;
        case Operation::Div:
            current_number = (current_number == 0.0) ? 1.0 : current_number;
            current_number = current_number / operand;
            break;
        case Operation::Pow:
            current_number = std::pow(current_number, operand);
            break;
        case Operation::Root:
            if (current_number < 0) {
                std::cout << "inf" << std::endl;
                // текущее число не меняется
            } else {
                if (operand == 0.0) {
                    std::cerr << "Error: Root degree cannot be zero" << std::endl;
                    return false;
                }
                current_number = std::pow(current_number, 1.0 / operand);
            }
            break;
        case Operation::Assign:
            current_number = operand;
            break;
        default:
            std::cerr << "Error: Unknown binary operation" << std::endl;
            return false;
    }
    return true;
}


bool RunCalculatorCycle() {
    Number current_number = 0.0;
    if(!ReadNumber(current_number)) 
        return false;

    Number remembered_number = 0.0;
    bool is_memory = false;

    std::string str_operation;
    while(std::cin >> str_operation) {
        Operation operation = StringToOperation(str_operation);

        switch(operation) {
            case Operation::Memory:
                is_memory = true;
                remembered_number = current_number;
                continue;
            case Operation::Load:
                if (!is_memory) {
                    std::cerr << "Error: Memory is empty" << std::endl;
                    return false;
                }
                current_number = remembered_number;
                continue;

            case Operation::Print:
                std::cout << current_number << std::endl;
                continue;

            case Operation::Clear:
                current_number = 0.0;
                continue;

            case Operation::Quit:
                return true;
            
            // Если что-то из бинарных операций, то считываем следующее число
            case Operation::Addition:
            case Operation::Subtract:
            case Operation::Mul:
            case Operation::Div:
            case Operation::Pow:
            case Operation::Root:
            case Operation::Assign:
                {
                    Number operand;
                    if (!ReadNumber(operand)) 
                        return false;
                    if (!Calculate(current_number, operation, operand))
                    return false;
                break;
            }
            default:
                std::cerr << "Error: Unknown token " << str_operation << std::endl;
                return false;
            }
    }
    return false;
}
