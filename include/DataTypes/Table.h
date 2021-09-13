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
    private:
        template<class T>
        class row_base : public std::map<QString, T> {
            static_assert(std::is_same<T, const DataType *>::value || std::is_same<T, DataType *>::value,
                          "Only 'DataType*' and 'const DataType*' are acceptable.");
        };

    public:
        using row = row_base<DataType *>;
        using const_row = row_base<const DataType *>;
    public:
        template<class T>
        class iterator_base {
            static_assert(std::is_same<T, row>::value || std::is_same<T, const_row>::value,
                          "Only 'Table::row' and 'Table::const_row' are acceptable.");
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
            T _row;
        private:
            explicit iterator_base(Table *target, const std::size_t &shift = 0);
        private:
            T &sync() noexcept;
        public:
            iterator_base<T> &operator++() noexcept;
            const iterator_base<T> operator++(int) noexcept;
            iterator_base<T> &operator--() noexcept;
            const iterator_base<T> operator--(int) noexcept;
        public:
            iterator_base<T> &operator+=(const std::size_t &x) noexcept;
            iterator_base<T> &operator-=(const std::size_t &x) noexcept;
        public:
            reference operator*() noexcept;
            pointer operator->() noexcept;
        public:
            template<class E>
            friend iterator_base<E> operator+(const iterator_base<E> &lhs, const std::size_t &rhs) noexcept;
            template<class E>
            friend iterator_base<E> operator-(const iterator_base<E> &lhs, const std::size_t &rhs) noexcept;
            template<class Lhs, class Rhs>
            friend bool operator==(const iterator_base<Lhs> &lhs, const iterator_base<Rhs> &rhs) noexcept;
            template<class Lhs, class Rhs>
            friend bool operator!=(const iterator_base<Lhs> &lhs, const iterator_base<Rhs> &rhs) noexcept;
        };

    public:
        using const_iterator = iterator_base<const_row>;
        using iterator = iterator_base<row>;
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
        Table &append(const const_row &row);
        Table &append(const Table &table);
        Table &emplace(const row &row);
        Table &emplace(const Table &table);
    public:
        Table &dropColumn(const QString &name) noexcept;
        Table &addColumn(const QString &name, const TYPES &type);
        Table &addColumn(const QString &name, const DataType *defaultValue) noexcept;
    public:
        template<class T>
        iterator erase(const iterator_base<T> &position) noexcept; //TODO: add template type checks.
        template<class T>
        iterator
        erase(const iterator_base<T> &from, const iterator_base<T> &to) noexcept; //TODO: add template type checks.
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
