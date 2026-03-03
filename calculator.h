
#pragma once

#include <string>
#include <optional>
#include <cmath>
#include <type_traits>
#include "rational.h"
#include "pow.h"

using Error = std::string;

template<class Number>
class Calculator {
public:
	void Set(Number value) {
		number_ = value;
	}

	Number GetNumber() const {
		return number_;
	}

	std::optional<Error> Add(Number rhs) {
		number_ += rhs;
		return std::nullopt;
	}

	std::optional<Error> Sub(Number rhs) {
		number_ -= rhs;
		return std::nullopt;
	}

	std::optional<Error> Mul(Number rhs) {
		number_ *= rhs;
		return std::nullopt;
	}

	std::optional<Error> Div(Number rhs) {
		if constexpr (std::is_integral_v<Number>) {
			if (rhs == 0) {
				return std::string{"Division by zero"};
			}
		}

		if constexpr (std::is_same_v<Number, Rational>) {
			if (rhs.GetNumerator() == 0) {
				return std::string{"Division by zero"};
			}
		}

		number_ /= rhs;
		return std::nullopt;
	}

	std::optional<Error> Pow(Number rhs) {
		if constexpr (std::is_integral_v<Number>) {
			if (number_ == 0 && rhs == 0) {
				return std::string{"Zero power to zero"};
			}

			if (rhs < 0) {
				return std::string{"Integer negative power"};
			}

			number_ = IntegerPow(number_, rhs);
			return std::nullopt;
		} else if constexpr (std::is_same_v<Number, Rational>) {
			if (number_.GetNumerator() == 0 && rhs.GetNumerator() == 0) {
				return std::string{"Zero power to zero"};
			}

			if (rhs.GetDenominator() != 1) {
				return std::string{"Fractional power is not supported"};
			}

			if (number_.GetNumerator() == 0 && rhs.GetNumerator() < 0) {
				return std::string{"Division by zero"};
			}

			number_ = ::Pow(number_, rhs);
			return std::nullopt;
		} else {
			number_ = std::pow(number_, rhs);
			return std::nullopt;
		}
	}

	void Save() {
		mem_ = number_;
	}

	void Load() {
		if (mem_.has_value()) {
			number_ = mem_.value();
		}
	}

	bool GetHasMem() const {
		return mem_.has_value();
	}

	void SaveToMemory() {
		Save();
	}

	bool LoadFromMemory() {
		const bool has_mem = mem_.has_value();
		Load();
		return has_mem;
	}

	void ClearMemory() {
		mem_ = std::nullopt;
	}

private:
	Number number_ = {};
	std::optional<Number> mem_ = {};
};