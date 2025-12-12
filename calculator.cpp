#include "calculator.h"
#include <iostream>
#include <cmath>
#include <string>

bool ReadNumber(Number& result) {
    std::string input;
    std::cin >> input;
    
    try {
        result = std::stod(input);
        return true;
    } catch (const std::exception&) {
        return false;
    }
}

bool RunCalculatorCycle() {
    Number current = 0;
    Number memory = 0;
    bool memory_has_value = false;
    
    // Чтение начального числа
    if (!ReadNumber(current)) {
        std::cerr << "Error: Numeric operand expected" << std::endl;
        return false;
    }
    
    std::string command;
    while (std::cin >> command) {
        if (command == "q") {
            return true;  // Штатное завершение
        } 
        else if (command == "=") {
            std::cout << current << std::endl;
        }
        else if (command == "c") {
            current = 0;
        }
        else if (command == "s") {
            memory = current;
            memory_has_value = true;
        }
        else if (command == "l") {
            if (!memory_has_value) {
                std::cerr << "Error: Memory is empty" << std::endl;
                return false;
            }
            current = memory;
        }
        else if (command == "+" || command == "-" || command == "*" || 
                 command == "/" || command == "**" || command == ":") {
            Number operand;
            if (!ReadNumber(operand)) {
                std::cerr << "Error: Numeric operand expected" << std::endl;
                return false;
            }
            
            if (command == "+") {
                current += operand;
            } else if (command == "-") {
                current -= operand;
            } else if (command == "*") {
                current *= operand;
            } else if (command == "/") {
                current /= operand;
            } else if (command == "**") {
                current = std::pow(current, operand);
            } else if (command == ":") {
                current = operand;
            }
        }
        else {
            std::cerr << "Error: Unknown token " << command << std::endl;
            return false;
        }
    }
    
    return true;
}
