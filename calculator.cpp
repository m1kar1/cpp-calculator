#include "calculator.h"

#include <cassert>
#include <cmath>
#include <iostream>

void Calculator::Add(Number r) {
    number_ += r;
}

void Calculator::Sub(Number r) {
    number_ -= r;
}

void Calculator::Div(Number r) {
    number_ /= r;
}

void Calculator::Mul(Number r) {
    number_ *= r;
}

void Calculator::Pow(Number r) {
    number_ = pow(number_, r);
}

void Calculator::Set(Number n) {
    number_ = n;
}

void Calculator::Negate(Number n) {
    Set(n);
    Mul(-1);
}

void Calculator::Save() {
    has_mem_ = true;
    mem_ = number_;
}

void Calculator::Load() {
    assert(has_mem_);
    number_ = mem_;
}

void Calculator::ClearMemory() {
    has_mem_ = false;
}

bool Calculator::GetHasMem() const {
    return has_mem_;
}

Number Calculator::GetNumber() const {
    return number_;
}

std::string Calculator::GetNumberRepr() const {
    return std::to_string(number_);
}
