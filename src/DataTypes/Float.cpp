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

#include "DataTypes/Float.h"

namespace DTypes {
    const TYPES Float::static_type = TYPES::FLOAT;

    Float::Float(float x) noexcept: x(x) {}

    Float::Float(const Float &reference) noexcept: x(reference.x) {}

    Float *Float::copy() const noexcept {
        return new Float(*this);
    }

    float Float::get() const noexcept {
        return this->x;
    }

    Float &Float::set(float value) noexcept {
        this->x = value;
        return *this;
    }

    Float::operator float() const noexcept {
        return this->x;
    }

    Float::operator bool() const noexcept {
        return static_cast<bool>(this->x);
    }

    bool Float::operator==(const Float &rhs) const noexcept {
        return this->x == rhs.x;
    }

    bool Float::operator!=(const Float &rhs) const noexcept {
        return this->x != rhs.x;
    }

    bool Float::operator<(const Float &rhs) const noexcept {
        return this->x < rhs.x;
    }

    bool Float::operator>(const Float &rhs) const noexcept {
        return this->x > rhs.x;
    }

    bool Float::operator<=(const Float &rhs) const noexcept {
        return this->x <= rhs.x;
    }

    bool Float::operator>=(const Float &rhs) const noexcept {
        return this->x >= rhs.x;
    }

    Float &Float::operator++() noexcept {
        ++this->x;
        return *this;
    }

    Float Float::operator++(int) noexcept {
        Float old = *this;
        ++this->x;
        return old;
    }

    Float &Float::operator--() noexcept {
        --this->x;
        return *this;
    }

    Float Float::operator--(int) noexcept {
        Float old = *this;
        --this->x;
        return old;
    }

    Float &Float::operator+=(const Float &rhs) noexcept {
        this->x += rhs.x;
        return *this;
    }

    Float &Float::operator-=(const Float &rhs) noexcept {
        this->x -= rhs.x;
        return *this;
    }

    Float &Float::operator/=(const Float &rhs) noexcept {
        this->x /= rhs.x;
        return *this;
    }

    Float &Float::operator*=(const Float &rhs) noexcept {
        this->x *= rhs.x;
        return *this;
    }

    Float operator+(const Float &lhs, const Float& rhs) noexcept {
        return {lhs.x + rhs.x};
    }

    Float operator-(const Float &lhs, const Float& rhs) noexcept {
        return {lhs.x - rhs.x};
    }

    Float operator*(const Float &lhs, const Float& rhs) noexcept {
        return {lhs.x * rhs.x};
    }

    Float operator/(const Float &lhs, const Float& rhs) noexcept {
        return {lhs.x / rhs.x};
    }

    std::ostream &operator<<(std::ostream &os, const Float &value) noexcept {
        return value.print(os);
    }

    std::ostream &Float::print(std::ostream &os) const noexcept {
        os << this->x;
        return os;
    }
}
