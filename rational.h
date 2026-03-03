#pragma once

#include <cstdint>
#include <iostream>
#include <numeric>

class Rational {
public:
	Rational() = default;

	Rational(std::int64_t numerator, std::int64_t denominator = 1)
		: numerator_(numerator), denominator_(denominator) {
		Normalize();
	}

	std::int64_t GetNumerator() const {
		return numerator_;
	}

	std::int64_t GetDenominator() const {
		return denominator_;
	}

	Rational operator-() const {
		return Rational(-numerator_, denominator_);
	}

	Rational& operator+=(const Rational& rhs) {
		numerator_ = numerator_ * rhs.denominator_ + rhs.numerator_ * denominator_;
		denominator_ *= rhs.denominator_;
		Normalize();
		return *this;
	}

	Rational& operator-=(const Rational& rhs) {
		numerator_ = numerator_ * rhs.denominator_ - rhs.numerator_ * denominator_;
		denominator_ *= rhs.denominator_;
		Normalize();
		return *this;
	}

	Rational& operator*=(const Rational& rhs) {
		numerator_ *= rhs.numerator_;
		denominator_ *= rhs.denominator_;
		Normalize();
		return *this;
	}

	Rational& operator/=(const Rational& rhs) {
		numerator_ *= rhs.denominator_;
		denominator_ *= rhs.numerator_;
		Normalize();
		return *this;
	}

	friend Rational operator+(Rational lhs, const Rational& rhs) {
		lhs += rhs;
		return lhs;
	}

	friend Rational operator-(Rational lhs, const Rational& rhs) {
		lhs -= rhs;
		return lhs;
	}

	friend Rational operator*(Rational lhs, const Rational& rhs) {
		lhs *= rhs;
		return lhs;
	}

	friend Rational operator/(Rational lhs, const Rational& rhs) {
		lhs /= rhs;
		return lhs;
	}

	friend bool operator==(const Rational& lhs, const Rational& rhs) {
		return lhs.numerator_ == rhs.numerator_ && lhs.denominator_ == rhs.denominator_;
	}

	friend bool operator!=(const Rational& lhs, const Rational& rhs) {
		return !(lhs == rhs);
	}

	friend bool operator<(const Rational& lhs, const Rational& rhs) {
		return lhs.numerator_ * rhs.denominator_ < rhs.numerator_ * lhs.denominator_;
	}

	friend bool operator>(const Rational& lhs, const Rational& rhs) {
		return rhs < lhs;
	}

	friend bool operator<=(const Rational& lhs, const Rational& rhs) {
		return !(rhs < lhs);
	}

	friend bool operator>=(const Rational& lhs, const Rational& rhs) {
		return !(lhs < rhs);
	}

	friend std::ostream& operator<<(std::ostream& out, const Rational& value) {
		if (value.denominator_ == 1) {
			out << value.numerator_;
			return out;
		}
		out << value.numerator_ << " / " << value.denominator_;
		return out;
	}

	friend std::istream& operator>>(std::istream& in, Rational& value) {
		std::int64_t numerator = 0;
		std::int64_t denominator = 1;
		if (!(in >> numerator)) {
			return in;
		}

		if (in.peek() == '/') {
			in.get();
			if (!(in >> denominator)) {
				in.setstate(std::ios::failbit);
				return in;
			}
		}

		value = Rational(numerator, denominator);
		return in;
	}

private:
	void Normalize() {
		if (denominator_ == 0) {
			denominator_ = 1;
			numerator_ = 0;
			return;
		}

		if (denominator_ < 0) {
			denominator_ = -denominator_;
			numerator_ = -numerator_;
		}

		const auto gcd = std::gcd(numerator_, denominator_);
		numerator_ /= gcd;
		denominator_ /= gcd;
	}

private:
	std::int64_t numerator_ = 0;
	std::int64_t denominator_ = 1;
};