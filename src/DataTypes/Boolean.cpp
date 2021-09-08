// MIT License
//
// Copyright (c) 2021 Point Vortex | Danil Maksimovich Andrieiev
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

#include "DataTypes/Boolean.h"

namespace DTypes {
    const TYPES Boolean::static_type = TYPES::BOOLEAN;

    Boolean::Boolean(bool x) noexcept: x(x) {}

    Boolean::Boolean(const Boolean &reference) noexcept: x(reference.x) {}

    Boolean *Boolean::copy() const noexcept {
        return new Boolean(*this);
    }

    TYPES Boolean::type() const noexcept {
        return TYPES::BOOLEAN;
    }

    bool Boolean::get() const noexcept {
        return this->x;
    }

    void Boolean::set(bool value) noexcept {
        this->x = value;
    }

    Boolean::operator bool() const noexcept {
        return this->x;
    }

    bool Boolean::operator==(const Boolean &rhs) const noexcept {
        return this->x == rhs.x;
    }

    bool Boolean::operator!=(const Boolean &rhs) const noexcept {
        return this->x != rhs.x;
    }

    bool Boolean::operator<(const Boolean &rhs) const noexcept {
        return this->x < rhs.x;
    }

    bool Boolean::operator>(const Boolean &rhs) const noexcept {
        return this->x > rhs.x;
    }

    bool Boolean::operator<=(const Boolean &rhs) const noexcept {
        return this->x <= rhs.x;
    }

    bool Boolean::operator>=(const Boolean &rhs) const noexcept {
        return this->x >= rhs.x;
    }

    Boolean &Boolean::operator+=(Boolean &rhs) noexcept {
        this->x += rhs.x;
        return *this;
    }

    Boolean &Boolean::operator-=(Boolean &rhs) noexcept {
        this->x -= rhs.x;
        return *this;
    }

    Boolean &Boolean::operator/=(Boolean &rhs) noexcept {
        this->x /= rhs.x;
        return *this;
    }

    Boolean &Boolean::operator*=(Boolean &rhs) noexcept {
        this->x *= rhs.x;
        return *this;
    }

    Boolean operator+(Boolean &lhs, Boolean rhs) noexcept {
        return {static_cast<bool>(lhs.x + rhs.x)};
    }

    Boolean operator-(Boolean &lhs, Boolean rhs) noexcept {
        return {static_cast<bool>(lhs.x - rhs.x)};
    }

    Boolean operator*(Boolean &lhs, Boolean rhs) noexcept {
        return {static_cast<bool>(lhs.x * rhs.x)};
    }

    Boolean operator/(Boolean &lhs, Boolean rhs) noexcept {
        return {static_cast<bool>(lhs.x / rhs.x)};
    }

    std::ostream &operator<<(std::ostream &os, const Boolean &value) noexcept {
        os << value.x;
        return os;
    }
}
