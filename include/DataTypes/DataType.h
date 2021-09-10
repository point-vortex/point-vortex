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

#ifndef POINT_VORTEX_DATATYPE_H
#define POINT_VORTEX_DATATYPE_H

#include "utils/ICopyable.h"

#include <ostream>

namespace DTypes {
    enum class TYPES {
        UNKNOWN,
        INTEGER,
        FLOAT,
        BOOLEAN,
        STRING,
    };

    class Integer;

    class Float;

    class Boolean;

    class DataType : public utils::ICopyable {
    public:
        const static TYPES static_type = TYPES::UNKNOWN;
    public:
        virtual ~DataType() = default;
        [[nodiscard]] DataType *copy() const override = 0;
    public:
        virtual TYPES type() const noexcept { return TYPES::UNKNOWN; }
        virtual std::ostream& print(std::ostream& os) const noexcept = 0;
        virtual void a() {} //TODO: remove
    };
}

#endif //POINT_VORTEX_DATATYPE_H
