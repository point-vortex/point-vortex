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

#ifndef POINT_VORTEX_TABLE_H
#define POINT_VORTEX_TABLE_H

#include <vector>
#include <map>

#include <QString>

#include "DataTypes/DataType.h"

namespace DTypes {
    class Table : public DataType {
    public:
        struct Row {
            std::map<QString, DataType *> data;
            // std::map<QString, TYPE>
            // TODO: add column type field
        };

        class Iterator {
        public:
            using iterator_category = std::forward_iterator_tag;
            using difference_type = std::ptrdiff_t;
            using value_type = Row;
            using pointer = Row *;
            using reference = Row &;
        private:
            Table* table;
            size_t rowsShift;
            Iterator(Table* ptr, size_t row = 0);
        public:
            value_type operator*() const;
            pointer operator->();
            /// Prefix increment
            Iterator& operator++();
            /// Postfix increment
            Iterator operator++(int);
            /// Prefix decrement
            Iterator& operator--();
            /// Postfix decrement
            Iterator operator--(int);
            friend bool operator== (const Iterator& left, const Iterator& right);
            friend bool operator!= (const Iterator& left, const Iterator& right);
        };
    protected:
        std::map<QString, std::vector<DataType *>> data;

    public:
        explicit Table();
        Table(const Table &reference);
        ~Table() override = default;
    public:
        Iterator begin();
    public:
        [[nodiscard]] Table *copy() const override;
    };
}


#endif //POINT_VORTEX_TABLE_H
