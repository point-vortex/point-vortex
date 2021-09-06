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

#ifndef POINT_VORTEX_BOOLEAN_H
#define POINT_VORTEX_BOOLEAN_H

#include "DataTypes/DataType.h"

namespace DTypes {
    /**
     * Boolean - class for boolean values.
     * @author Danil Andreev
     */
    class Boolean : public DataType {
    private:
        bool x;
    public:
        Boolean(bool x = false);
        Boolean(const Boolean &reference);
        ~Boolean() override = default;
    public:
        [[nodiscard]] Boolean *copy() const override;
    public:
        [[nodiscard]] virtual bool get() const;
        virtual void set(bool x);
    public:
        operator bool() const;
    public:
        bool operator==(const Boolean &rhs) const;
        bool operator!=(const Boolean &rhs) const;
        bool operator<(const Boolean &rhs) const;
        bool operator>(const Boolean &rhs) const;
        bool operator<=(const Boolean &rhs) const;
        bool operator>=(const Boolean &rhs) const;
    public:
        Boolean& operator+=(Boolean& rhs);
        Boolean& operator-=(Boolean& rhs);
        Boolean& operator/=(Boolean& rhs);
        Boolean& operator*=(Boolean& rhs);
    public:
        friend Boolean operator+(Boolean& lhs, Boolean rhs);
        friend Boolean operator-(Boolean& lhs, Boolean rhs);
        friend Boolean operator*(Boolean& lhs, Boolean rhs);
        friend Boolean operator/(Boolean& lhs, Boolean rhs);
    public:
        friend std::ostream& operator<<(std::ostream& os, const Boolean& value);
    };
}


#endif //POINT_VORTEX_BOOLEAN_H
