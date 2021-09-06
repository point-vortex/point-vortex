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

#ifndef POINT_VORTEX_FLOAT_H
#define POINT_VORTEX_FLOAT_H

#include "DataTypes/DataType.h"

namespace DTypes {
    /**
     * Float - class for floating point values.
     * @author Danil Andreev
     */
    class Float : public DataType {
    private:
        float x;
    public:
        Float(float x = 0.0f);
        Float(const Float& reference);
        ~Float() = default;
    public:
        Float *copy() const override;
    public:
        [[nodiscard]] virtual float get() const;
        virtual Float& set(float x);
    public:
        operator float() const;
        operator bool() const;
    public:
        bool operator==(const Float &rhs) const;
        bool operator!=(const Float &rhs) const;
        bool operator<(const Float &rhs) const;
        bool operator>(const Float &rhs) const;
        bool operator<=(const Float &rhs) const;
        bool operator>=(const Float &rhs) const;
    public:
        Float& operator++();
        Float operator++(int);
        Float& operator--();
        Float operator--(int);
    public:
        Float& operator+=(Float& rhs);
        Float& operator-=(Float& rhs);
        Float& operator/=(Float& rhs);
        Float& operator*=(Float& rhs);
    public:
        friend Float operator+(Float& lhs, Float rhs);
        friend Float operator-(Float& lhs, Float rhs);
        friend Float operator*(Float& lhs, Float rhs);
        friend Float operator/(Float& lhs, Float rhs);
    public:
        friend std::ostream& operator<<(std::ostream& os, const Float& value);
    };
}


#endif //POINT_VORTEX_FLOAT_H