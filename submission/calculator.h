
#pragma once

#include <cmath>
#include <optional>
#include <string>
#include <type_traits>

#include "pow.h"
#include "rational.h"

using Error = std::string;

template<class Number>
class Calculator {
public:
    void Set(Number number) {
        current_number_ = number;
    }

    Number GetNumber() const {
        return current_number_;
    }

    std::optional<Error> Add(Number number) {
        current_number_ += number;
        return std::nullopt;
    }

    std::optional<Error> Sub(Number number) {
        current_number_ -= number;
        return std::nullopt;
    }

    std::optional<Error> Mul(Number number) {
        current_number_ *= number;
        return std::nullopt;
    }

    std::optional<Error> Div(Number number) {
        if constexpr (std::is_floating_point_v<Number>) {
            current_number_ /= number;
            return std::nullopt;
        } else if constexpr (std::is_same_v<Number, Rational>) {
            if (number.GetNumerator() == 0) {
                return Error{"Division by zero"};
            }
            current_number_ /= number;
            return std::nullopt;
        } else {
            if (number == Number{}) {
                return Error{"Division by zero"};
            }
            current_number_ /= number;
            return std::nullopt;
        }
    }

    std::optional<Error> Pow(Number number) {
        if constexpr (std::is_floating_point_v<Number>) {
            current_number_ = std::pow(current_number_, number);
            return std::nullopt;
        } else if constexpr (std::is_same_v<Number, Rational>) {
            if (current_number_.GetNumerator() == 0 && number.GetNumerator() == 0) {
                return Error{"Zero power to zero"};
            }
            if (number.GetDenominator() != 1) {
                return Error{"Fractional power is not supported"};
            }
            current_number_ = ::Pow(current_number_, number);
            return std::nullopt;
        } else {
            if constexpr (!std::is_unsigned_v<Number>) {
                if (number < Number{}) {
                    return Error{"Integer negative power"};
                }
            }
            if (current_number_ == Number{} && number == Number{}) {
                return Error{"Zero power to zero"};
            }
            current_number_ = IntegerPow(current_number_, number);
            return std::nullopt;
        }
    }

    void Save() {
        mem_ = current_number_;
    }

    void Load() {
        current_number_ = mem_.value();
    }

    void ClearMemory() {
        mem_ = std::nullopt;
    }

    bool GetHasMem() const {
        return mem_.has_value();
    }

private:
    Number current_number_ = {};
    std::optional<Number> mem_;
};
