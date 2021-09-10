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
            using std::map<QString, DataType *>::iterator;
            using std::map<QString, DataType *>::const_iterator;
            using std::map<QString, DataType *>::reverse_iterator;
            using std::map<QString, DataType *>::const_reverse_iterator;
            using std::map<QString, DataType *>::operator[];
        };

    public:
        template<class T>
        class iterator_base {
            friend Table;
        public:
            using iterator_category = std::forward_iterator_tag;
            using value_type = T;
            using difference_type = std::ptrdiff_t;
            using pointer = T *;
            using reference = T &;
        private:
            Table *target;
            std::size_t shift;
            Row row;
        private:
            explicit iterator_base(Table *target, const std::size_t &shift = 0);
        private:
            void sync() noexcept;
        public:
            iterator_base<T> &operator++() noexcept;
            iterator_base<T> operator++(int) noexcept;
            iterator_base<T> &operator--() noexcept;
            iterator_base<T> operator--(int) noexcept;
        public:
            iterator_base<T> &operator+=(const std::size_t &x) noexcept;
            iterator_base<T> &operator-=(const std::size_t &x) noexcept;
        public:
            Row &operator*() noexcept;
            Row *operator->() noexcept;
        public:
            friend iterator_base<T> operator+(const iterator_base<T> &lhs, const std::size_t &rhs);
            friend iterator_base<T> operator-(const iterator_base<T> &lhs, const std::size_t &rhs);
        };

    public:
        using const_iterator = iterator_base<const Row>;
        using iterator = iterator_base<Row>;
        friend iterator;
        friend const_iterator;
    protected:
        using vector_t = std::vector<DataType *>;
        using map_item_t = std::pair<std::vector<DataType *>, TYPES>;
        using storage_t = std::map<QString, map_item_t>;
    private:
        storage_t data;
        std::size_t _size;
        std::size_t _capacity;
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
        template<class T>
        iterator erase(const iterator_base<T> &position) noexcept;
        template<class T>
        iterator erase(const iterator_base<T> &from, const iterator_base<T> &to) noexcept;
    public:
        iterator begin() noexcept;
        iterator end() noexcept;
        const_iterator cbegin() noexcept;
        const_iterator cend() noexcept;
    public:
        Table &reserve(const std::size_t &newCapacity);
        [[nodiscard]] std::size_t capacity() const noexcept;
        [[nodiscard]] std::size_t size() const noexcept;
    private:
        storage_t::iterator dropColumn(const storage_t::iterator &column) noexcept;
    private:
        storage_t::iterator createColumn(const QString &name, const TYPES &type);
        storage_t::iterator createColumn(const QString &name, const DataType *defaultValue) noexcept;
        void syncColumn(const storage_t::iterator &column) noexcept;
        inline void syncAllColumns() noexcept;
        inline void syncCapacity() noexcept;
    public: //TODO: add ifdef debug
        std::ostream &print(std::ostream &os) const noexcept override;
    public:
        [[nodiscard]] Table *copy() const override;
    };
}


#endif //POINT_VORTEX_TABLE_H
