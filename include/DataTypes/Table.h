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
#include <utility>
#include <QString>
#include "DataTypes/DataTypes.h"

namespace DTypes {
    class Table : public DataType {
    public:

        struct Row {
        public:
            std::map<QString, DataType *> data;
        public:
            Row() = default;
        };

        class const_iterator {};
        class iterator : public const_iterator {};

    public:
        using vector_t = std::vector<DataType *>;
        using map_item_t = std::pair<std::vector<DataType *>, TYPES>;
        using storage_t = std::map<QString, map_item_t>;
    private:
        storage_t data;
        std::size_t size;
    public:
        Table();
        Table(const Table &reference);
        ~Table() override;
    public:
        Table &append(const Row &row);
        Table &append(const Table &table);
        Table &emplace(const Row &row);
        Table &emplace(const Table &table);
    public:
        Table& dropColumn(const QString& name) noexcept;
        Table& addColumn(const QString &name, const TYPES &type);
        Table& addColumn(const QString &name, const DataType *defaultValue) noexcept;
    public:
        iterator erase(const const_iterator& position) noexcept;
        iterator erase(const const_iterator& from, const const_iterator to) noexcept;
    public:
        iterator begin() noexcept;
        iterator end() noexcept;
        const_iterator cbegin() noexcept;
        const_iterator cend() noexcept;
    private:
        storage_t::iterator dropColumn(const storage_t::iterator& column) noexcept;
    private:
        storage_t::iterator createColumn(const QString &name, const TYPES &type);
        storage_t::iterator createColumn(const QString &name, const DataType *defaultValue) noexcept;
    };
}


#endif //POINT_VORTEX_TABLE_H
