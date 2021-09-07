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

        class Row : protected std::map<QString, DataType *> {
        public:
            ~Row();
        public:
            using std::map<QString, DataType *>::insert;
            using std::map<QString, DataType *>::clear;
            using std::map<QString, DataType *>::erase;
            using std::map<QString, DataType *>::contains;
            using std::map<QString, DataType *>::size;
            using std::map<QString, DataType *>::at;
            using std::map<QString, DataType *>::begin;
            using std::map<QString, DataType *>::end;
            using std::map<QString, DataType *>::operator[];
        };

        class const_iterator {
            friend Table;
        private:
            Table *target;
            std::size_t shift;
            Row row;
        private:
            explicit const_iterator(Table *target, std::size_t shift = 0);
        public:
            const_iterator &operator++() noexcept;
            const_iterator operator++(int) noexcept;
            const_iterator &operator--() noexcept;
            const_iterator operator--(int) noexcept;
        public:
            const_iterator &operator+=(std::size_t x) noexcept;
            const_iterator operator-=(std::size_t x) noexcept;
        public:
            Row &operator*() noexcept;
            Row *operator->() noexcept;
        };

        class iterator : public const_iterator {
            friend Table;
        private:
            explicit iterator(Table *target, std::size_t shift = 0);
        };

        friend const_iterator;
        friend iterator;
    protected:
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
        Table &dropColumn(const QString &name) noexcept;
        Table &addColumn(const QString &name, const TYPES &type);
        Table &addColumn(const QString &name, const DataType *defaultValue) noexcept;
    public:
        iterator erase(const const_iterator &position) noexcept;
        iterator erase(const const_iterator &from, const const_iterator& to) noexcept;
    public:
        iterator begin() noexcept;
        iterator end() noexcept;
        const_iterator cbegin() noexcept;
        const_iterator cend() noexcept;
    private:
        storage_t::iterator dropColumn(const storage_t::iterator &column) noexcept;
    private:
        storage_t::iterator createColumn(const QString &name, const TYPES &type);
        storage_t::iterator createColumn(const QString &name, const DataType *defaultValue) noexcept;
    };
}


#endif //POINT_VORTEX_TABLE_H
