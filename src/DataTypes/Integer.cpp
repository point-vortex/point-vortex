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

#include "DataTypes/Integer.h"

namespace DTypes {
    Integer::Integer(int x) : x(x) {}

    Integer::Integer(const Integer &reference) : x(reference.x) {}

    Integer *Integer::copy() const {
        return new Integer(*this);
    }

    int Integer::get() const {
        return this->x;
    }

    Integer &Integer::set(int value) {
        this->x = value;
        return *this;
    }

    Integer::operator int() const {
        return this->x;
    }

    Integer::operator bool() const {
        return static_cast<bool>(this->x);
    }

    bool Integer::operator==(const Integer &rhs) const {
        return this->x == rhs.x;
    }

    bool Integer::operator!=(const Integer &rhs) const {
        return this->x != rhs.x;
    }

    bool Integer::operator<(const Integer &rhs) const {
        return this->x < rhs.x;
    }

    bool Integer::operator>(const Integer &rhs) const {
        return this->x > rhs.x;
    }

    bool Integer::operator<=(const Integer &rhs) const {
        return this->x <= rhs.x;
    }

    bool Integer::operator>=(const Integer &rhs) const {
        return this->x >= rhs.x;
    }

    Integer &Integer::operator++() {
        ++this->x;
        return *this;
    }

    Integer Integer::operator++(int) {
        Integer old = *this;
        ++this->x;
        return old;
    }

    Integer &Integer::operator--() {
        --this->x;
        return *this;
    }

    Integer Integer::operator--(int) {
        Integer old = *this;
        --this->x;
        return old;
    }

    Integer &Integer::operator+=(Integer &rhs) {
        this->x += rhs.x;
        return *this;
    }

    Integer &Integer::operator-=(Integer &rhs) {
        this->x -= rhs.x;
        return *this;
    }

    Integer &Integer::operator/=(Integer &rhs) {
        this->x /= rhs.x;
        return *this;
    }

    Integer &Integer::operator*=(Integer &rhs) {
        this->x *= rhs.x;
        return *this;
    }

    Integer operator+(Integer &lhs, Integer rhs) {
        return {lhs.x + rhs.x};
    }

    Integer operator-(Integer &lhs, Integer rhs) {
        return {lhs.x - rhs.x};
    }

    Integer operator*(Integer &lhs, Integer rhs) {
        return {lhs.x * rhs.x};
    }

    Integer operator/(Integer &lhs, Integer rhs) {
        return {lhs.x / rhs.x};
    }

    std::ostream &operator<<(std::ostream &os, const Integer &value) {
        os << value.x;
        return os;
    }
}
