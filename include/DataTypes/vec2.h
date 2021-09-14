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

//
// Created by Denis Afendikov on 14.09.2021.
//

#ifndef _VEC2_H_
#define _VEC2_H_

#include "DataTypes/DataType.h"
#include <QVector2D>

namespace DTypes {
    /**
     * vec2 - class for storing vector of 2 floating point values (x, y).
     * @author Denys Afendikov
     */
    class vec2 : public DataType, public QVector2D {
    public:
        const static TYPES static_type;
    public:
        using QVector2D::QVector2D;
    public:
        vec2 *copy() const noexcept override;
    public:
        friend std::ostream &operator<<(std::ostream &os, const vec2 &value) noexcept;
        std::ostream &print(std::ostream &os) const noexcept override;
    };
}

#endif //_VEC2_H_
