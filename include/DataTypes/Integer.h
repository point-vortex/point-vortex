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
    private:
        int x;
    public:
        Integer(int x = 0);
        Integer(const Integer& reference);
        ~Integer() override = default;
    public:
        Integer *copy() const override;
    public:
        [[nodiscard]] virtual int get() const;
        virtual Integer& set(int x);
    public:
        operator int() const;
        operator bool() const;
    public:
        bool operator==(const Integer &rhs) const;
        bool operator!=(const Integer &rhs) const;
        bool operator<(const Integer &rhs) const;
        bool operator>(const Integer &rhs) const;
        bool operator<=(const Integer &rhs) const;
        bool operator>=(const Integer &rhs) const;
    public:
        Integer& operator++();
        Integer operator++(int);
        Integer& operator--();
        Integer operator--(int);
    public:
        Integer& operator+=(Integer& rhs);
        Integer& operator-=(Integer& rhs);
        Integer& operator/=(Integer& rhs);
        Integer& operator*=(Integer& rhs);
    public:
        friend Integer operator+(Integer& lhs, Integer rhs);
        friend Integer operator-(Integer& lhs, Integer rhs);
        friend Integer operator*(Integer& lhs, Integer rhs);
        friend Integer operator/(Integer& lhs, Integer rhs);
    public:
        friend std::ostream& operator<<(std::ostream& os, const Integer& value);
    };
}


#endif //POINT_VORTEX_INTEGER_H
