#pragma once

#include <compare>
#include <cstdint>
#include <cstdlib>
#include <iostream>
#include <numeric>

class Rational {
public:
    Rational() : numerator_(0), denominator_(1) {}

    Rational(int numerator) : Rational(numerator, 1) {}

    Rational(int numerator, int denominator)
        : numerator_(numerator)
        , denominator_(denominator) {
        if (denominator_ == 0) {
            std::abort();
        }
        Reduction();
    }

    Rational(const Rational& other) = default;

    int GetNumerator() const {
        return numerator_;
    }

    int GetDenominator() const {
        return denominator_;
    }

    Rational Inv() const {
        return Rational{denominator_, numerator_};
    }

    Rational& operator=(const Rational& other) = default;

    Rational& operator+=(const Rational& other) {
        numerator_ = numerator_ * other.denominator_ + other.numerator_ * denominator_;
        denominator_ = denominator_ * other.denominator_;
        Reduction();
        return *this;
    }

    Rational& operator-=(const Rational& other) {
        numerator_ = numerator_ * other.denominator_ - other.numerator_ * denominator_;
        denominator_ = denominator_ * other.denominator_;
        Reduction();
        return *this;
    }

    Rational& operator*=(const Rational& other) {
        numerator_ *= other.numerator_;
        denominator_ *= other.denominator_;
        Reduction();
        return *this;
    }

    Rational& operator/=(const Rational& other) {
        numerator_ *= other.denominator_;
        denominator_ *= other.numerator_;
        Reduction();
        return *this;
    }

    Rational operator+() const {
        return *this;
    }

    Rational operator-() const {
        return Rational{-numerator_, denominator_};
    }

    bool operator==(const Rational& other) const = default;

    auto operator<=>(const Rational& other) const {
        const std::int64_t left =
            static_cast<std::int64_t>(numerator_) * other.denominator_;
        const std::int64_t right =
            static_cast<std::int64_t>(other.numerator_) * denominator_;
        return left <=> right;
    }

    friend Rational operator+(Rational lhs, const Rational& rhs) {
        return lhs += rhs;
    }

    friend Rational operator-(Rational lhs, const Rational& rhs) {
        return lhs -= rhs;
    }

    friend Rational operator*(Rational lhs, const Rational& rhs) {
        return lhs *= rhs;
    }

    friend Rational operator/(Rational lhs, const Rational& rhs) {
        return lhs /= rhs;
    }

    friend std::istream& operator>>(std::istream& is, Rational& r);
    friend std::ostream& operator<<(std::ostream& os, const Rational& r);

private:
    void Reduction() {
        if (denominator_ == 0) {
            std::abort();
        }
        if (denominator_ < 0) {
            numerator_ = -numerator_;
            denominator_ = -denominator_;
        }
        const int divisor = std::gcd(numerator_, denominator_);
        numerator_ /= divisor;
        denominator_ /= divisor;
    }

    int numerator_ = 0;
    int denominator_ = 1;
};

inline std::istream& operator>>(std::istream& is, Rational& r) {
    const Rational original = r;

    int numerator = 0;
    int denominator = 1;
    char slash = '\0';

    if (!(is >> numerator)) {
        return is;
    }

    if (!(is >> slash)) {
        is.clear();
        r = Rational{numerator, 1};
        return is;
    }

    if (slash != '/') {
        is.unget();
        r = Rational{numerator, 1};
        return is;
    }

    if (!(is >> denominator) || denominator == 0) {
        is.setstate(std::ios::failbit);
        r = original;
        return is;
    }

    r = Rational{numerator, denominator};
    return is;
}

inline std::ostream& operator<<(std::ostream& os, const Rational& r) {
    if (r.denominator_ == 1) {
        os << r.numerator_;
    } else {
        os << r.numerator_ << " / " << r.denominator_;
    }
    return os;
}
