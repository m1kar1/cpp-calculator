#pragma once

#include <string>

using Number = double;

class Calculator {
public:
    Calculator(Number init = 0) : number_(init) {
    }
    void Add(Number r);
    void Sub(Number r);
    void Div(Number r);
    void Mul(Number r);
    void Pow(Number r);

    void Set(Number n);
    void Negate(Number n);

    void Save();
    void Load();

    void ClearMemory();

    bool GetHasMem() const;

    Number GetNumber() const;

    std::string GetNumberRepr() const;

private:
    bool has_mem_ = false;
    Number number_;
    Number mem_;
};
