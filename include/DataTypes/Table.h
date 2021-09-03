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
        class iterator;

        struct Row;
    protected:
        std::map<QString, std::vector<DataType *>> data;
        size_t rowsSize;
    public:
        explicit Table();
        Table(const Table &reference);
        ~Table() override = default;
    public:
        iterator end() noexcept;
        iterator begin() noexcept;
    public:
        void erase(size_t row) noexcept;
        iterator erase(const iterator &position) noexcept;
        iterator erase(const iterator &begin, const iterator &end) noexcept;
    public:
        void addColumn(const QString &name) noexcept;
        void removeColumn(const QString &name) noexcept;
    public:
        void push_back(const Row &row);
    public:
        Row at(size_t position) const noexcept;
    public:
        [[nodiscard]] Table *copy() const override;
    };

    namespace Table {
        class iterator {
            friend Table;
        public:
            using iterator_category = std::forward_iterator_tag;
            using difference_type = std::ptrdiff_t;
            using value_type = Row;
            using pointer = Row *;
            using reference = Row &;
        private:
            Table *table;
            std::size_t rowsShift;
            Row row;
        private:
            iterator(Table *ptr, std::size_t row = 0);
        private:
            inline void updateRow();
        public:
            reference operator*();
            pointer operator->();
            iterator &operator++();
            const iterator operator++(int);
            const iterator operator+=(std::size_t);
            iterator &operator--();
            const iterator operator--(int);
            const iterator operator-=(std::size_t);

            friend iterator operator+(const iterator &left, std::size_t right);
            friend iterator operator-(const iterator &left, std::size_t right);
            friend bool operator==(const iterator &left, const iterator &right);
            friend bool operator!=(const iterator &left, const iterator &right);
        };

        struct Row : public std::map<const QString, DataType *const> {
            friend iterator;
            // std::map<QString, TYPE>
            // TODO: add column type field
        private:
            std::size_t rowShift;
        };
    }
}


#endif //POINT_VORTEX_TABLE_H
