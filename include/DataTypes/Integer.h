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

#ifndef POINT_VORTEX_INTEGER_H
#define POINT_VORTEX_INTEGER_H

#include <ostream>
#include "DataTypes/DataType.h"

namespace DTypes {
    /**
     * Integer - class for integer values.
     * @author Danil Andreev
     */
    class Integer : public DataType {
    public:
        const static TYPES static_type;
    private:
        int x;
    public:
        Integer(int x = 0) noexcept;
        Integer(const Integer &reference) noexcept;
        ~Integer() noexcept override = default;
    public:
        Integer *copy() const noexcept override;
    public:
        TYPES type() const noexcept override;
    public:
        [[nodiscard]] virtual int get() const noexcept;
        virtual Integer &set(int x) noexcept;
    public:
        operator int() const noexcept;
        operator bool() const noexcept;
    public:
        bool operator==(const Integer &rhs) const noexcept;
        bool operator!=(const Integer &rhs) const noexcept;
        bool operator<(const Integer &rhs) const noexcept;
        bool operator>(const Integer &rhs) const noexcept;
        bool operator<=(const Integer &rhs) const noexcept;
        bool operator>=(const Integer &rhs) const noexcept;
    public:
        Integer &operator++() noexcept;
        Integer operator++(int) noexcept;
        Integer &operator--() noexcept;
        Integer operator--(int) noexcept;
    public:
        Integer &operator+=(Integer &rhs) noexcept;
        Integer &operator-=(Integer &rhs) noexcept;
        Integer &operator/=(Integer &rhs) noexcept;
        Integer &operator*=(Integer &rhs) noexcept;
    public:
        friend Integer operator+(Integer &lhs, Integer rhs) noexcept;
        friend Integer operator-(Integer &lhs, Integer rhs) noexcept;
        friend Integer operator*(Integer &lhs, Integer rhs) noexcept;
        friend Integer operator/(Integer &lhs, Integer rhs) noexcept;
    public:
        friend std::ostream &operator<<(std::ostream &os, const Integer &value) noexcept;
    };
}


#endif //POINT_VORTEX_INTEGER_H
