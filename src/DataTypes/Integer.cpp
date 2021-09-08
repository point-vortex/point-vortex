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
    const TYPES Integer::static_type = TYPES::INTEGER;

    Integer::Integer(int x) noexcept: x(x) {}

    Integer::Integer(const Integer &reference) noexcept: x(reference.x) {}

    Integer *Integer::copy() const noexcept {
        return new Integer(*this);
    }

    TYPES Integer::type() const noexcept {
        return TYPES::INTEGER;
    }

    int Integer::get() const noexcept {
        return this->x;
    }

    Integer &Integer::set(int value) noexcept {
        this->x = value;
        return *this;
    }

    Integer::operator int() const noexcept {
        return this->x;
    }

    Integer::operator bool() const noexcept {
        return static_cast<bool>(this->x);
    }

    bool Integer::operator==(const Integer &rhs) const noexcept {
        return this->x == rhs.x;
    }

    bool Integer::operator!=(const Integer &rhs) const noexcept {
        return this->x != rhs.x;
    }

    bool Integer::operator<(const Integer &rhs) const noexcept {
        return this->x < rhs.x;
    }

    bool Integer::operator>(const Integer &rhs) const noexcept {
        return this->x > rhs.x;
    }

    bool Integer::operator<=(const Integer &rhs) const noexcept {
        return this->x <= rhs.x;
    }

    bool Integer::operator>=(const Integer &rhs) const noexcept {
        return this->x >= rhs.x;
    }

    Integer &Integer::operator++() noexcept {
        ++this->x;
        return *this;
    }

    Integer Integer::operator++(int) noexcept {
        Integer old = *this;
        ++this->x;
        return old;
    }

    Integer &Integer::operator--() noexcept {
        --this->x;
        return *this;
    }

    Integer Integer::operator--(int) noexcept {
        Integer old = *this;
        --this->x;
        return old;
    }

    Integer &Integer::operator+=(Integer &rhs) noexcept {
        this->x += rhs.x;
        return *this;
    }

    Integer &Integer::operator-=(Integer &rhs) noexcept {
        this->x -= rhs.x;
        return *this;
    }

    Integer &Integer::operator/=(Integer &rhs) noexcept {
        this->x /= rhs.x;
        return *this;
    }

    Integer &Integer::operator*=(Integer &rhs) noexcept {
        this->x *= rhs.x;
        return *this;
    }

    Integer operator+(Integer &lhs, Integer rhs) noexcept {
        return {lhs.x + rhs.x};
    }

    Integer operator-(Integer &lhs, Integer rhs) noexcept {
        return {lhs.x - rhs.x};
    }

    Integer operator*(Integer &lhs, Integer rhs) noexcept {
        return {lhs.x * rhs.x};
    }

    Integer operator/(Integer &lhs, Integer rhs) noexcept {
        return {lhs.x / rhs.x};
    }

    std::ostream &operator<<(std::ostream &os, const Integer &value) noexcept {
        return value.print(os);
    }

    std::ostream &Integer::print(std::ostream &os) const noexcept {
        os << this->x;
        return os;
    }
}
