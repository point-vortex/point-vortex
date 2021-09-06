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
    Boolean::Boolean(bool x) : x(x) {}

    Boolean::Boolean(const Boolean &reference) : x(reference.x) {}

    Boolean *Boolean::copy() const {
        return new Boolean(*this);
    }

    bool Boolean::get() const {
        return this->x;
    }

    void Boolean::set(bool value) {
        this->x = value;
    }

    Boolean::operator bool() const {
        return this->x;
    }

    bool Boolean::operator==(const Boolean &rhs) const {
        return this->x == rhs.x;
    }

    bool Boolean::operator!=(const Boolean &rhs) const {
        return this->x != rhs.x;
    }

    bool Boolean::operator<(const Boolean &rhs) const {
        return this->x < rhs.x;
    }

    bool Boolean::operator>(const Boolean &rhs) const {
        return this->x > rhs.x;
    }

    bool Boolean::operator<=(const Boolean &rhs) const {
        return this->x <= rhs.x;
    }

    bool Boolean::operator>=(const Boolean &rhs) const {
        return this->x >= rhs.x;
    }

    Boolean &Boolean::operator+=(Boolean &rhs) {
        this->x += rhs.x;
        return *this;
    }

    Boolean &Boolean::operator-=(Boolean &rhs) {
        this->x -= rhs.x;
        return *this;
    }

    Boolean &Boolean::operator/=(Boolean &rhs) {
        this->x /= rhs.x;
        return *this;
    }

    Boolean &Boolean::operator*=(Boolean &rhs) {
        this->x *= rhs.x;
        return *this;
    }

    Boolean operator+(Boolean &lhs, Boolean rhs) {
        return {static_cast<bool>(lhs.x + rhs.x)};
    }

    Boolean operator-(Boolean &lhs, Boolean rhs) {
        return {static_cast<bool>(lhs.x - rhs.x)};
    }

    Boolean operator*(Boolean &lhs, Boolean rhs) {
        return {static_cast<bool>(lhs.x * rhs.x)};
    }

    Boolean operator/(Boolean &lhs, Boolean rhs) {
        return {static_cast<bool>(lhs.x / rhs.x)};
    }

    std::ostream &operator<<(std::ostream &os, const Boolean &value) {
        os << value.x;
        return os;
    }
}
