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
//        template<class T>
//        class row_base
//                : protected std::map<QString, T> { //TODO: needs two row_base types. Const and not const. DataType* always not const.
//        public:
//            ~row_base();
//        public:
//            using std::map<QString, T>::insert;
//            using std::map<QString, T>::clear;
//            using std::map<QString, T>::erase;
//            using std::map<QString, T>::contains;
//            using std::map<QString, T>::size;
//            using std::map<QString, T>::at;
//            using std::map<QString, T>::begin;
//            using std::map<QString, T>::end;
//            using std::map<QString, T>::iterator;
//            using std::map<QString, T>::const_iterator;
//            using std::map<QString, T>::reverse_iterator;
//            using std::map<QString, T>::const_reverse_iterator;
//            using std::map<QString, T>::operator[];
//        };

    public:
        using row = std::map<QString, DataType *>;
        using const_row = std::map<QString, const DataType *>;

    public:
        template<class T>
        class iterator_base {
            friend Table;
        public:
            using iterator_category = std::forward_iterator_tag;
            using value_type = T;
            using difference_type = std::ptrdiff_t;
            using pointer = T *;
            using reference = T &; // TODO: Fix: Const qualifiers are lost. Suddenly...
        private:
            Table *target;
            std::size_t shift;
            T row;
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
            friend bool operator!=(const iterator_base<Rhs> &lhs, const iterator_base<Lhs> &rhs) noexcept;
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


    template<class T>
    Table::iterator Table::erase(const Table::iterator_base<T> &from, const Table::iterator_base<T> &to) noexcept {
        if (from.shift >= to.shift) return Table::iterator(this, from.shift);

        for (std::pair<const QString, map_item_t> &column : this->data) {
            vector_t &array = column.second.first;
            vector_t::iterator arrayBegin = array.begin();
            auto start = arrayBegin + static_cast<long long>(from.shift);
            auto finish = arrayBegin + static_cast<long long>(to.shift);
            for (auto record = start; record != finish; record++) {
                delete *record.base();
            }
            array.erase(start, finish);
        }
        this->_size -= to.shift - from.shift;
        this->syncCapacity();
        return Table::iterator(this, from.shift);
    }

    template<class T>
    Table::iterator Table::erase(const Table::iterator_base<T> &position) noexcept {
        return this->erase(position, position + 1);
    }

    void Table::syncCapacity() noexcept { if (this->_capacity < this->_size) this->_capacity = this->_size; }

// --------------------------------------------------------------------------------------------------- ITERATOR BASE ---

    template<class T>
    Table::iterator_base<T>::iterator_base(Table *target, const std::size_t &shift)
            : target(target), shift(shift), row() {}

    template<class T>
    T &Table::iterator_base<T>::sync() noexcept {
        if (this->target->_size < this->shift) {
            for (const std::pair<QString, Table::map_item_t> &column: target->data) {
                this->row.insert(std::make_pair(column.first, column.second.first.at(shift)));
            }
        }
        return this->row;
    }

    template<class T>
    Table::iterator_base<T> &Table::iterator_base<T>::operator++() noexcept {
        ++this->shift;
        return *this;
    }

    template<class T>
    const Table::iterator_base<T> Table::iterator_base<T>::operator++(int) noexcept {
        Table::iterator_base<T> old{*this};
        ++this->shift;
        return old;
    }

    template<class T>
    Table::iterator_base<T> &Table::iterator_base<T>::operator--() noexcept {
        --this->shift;
        return *this;
    }

    template<class T>
    const Table::iterator_base<T> Table::iterator_base<T>::operator--(int) noexcept {
        Table::iterator_base<T> old{*this};
        --this->shift;
        return old;
    }

    template<class T>
    Table::iterator_base<T> &Table::iterator_base<T>::operator+=(const std::size_t &x) noexcept {
        this->shift += x;
        return *this;
    }

    template<class T>
    Table::iterator_base<T> &Table::iterator_base<T>::operator-=(const std::size_t &x) noexcept {
        this->shift -= x;
        return *this;
    }

    template<class T>
    typename Table::iterator_base<T>::reference Table::iterator_base<T>::operator*() noexcept {
        return this->row;
    }

    template<class T>
    typename Table::iterator_base<T>::pointer Table::iterator_base<T>::operator->() noexcept {
        return &this->row;
    }

    template<class E>
    Table::iterator_base<E> operator+(const Table::iterator_base<E> &lhs, const std::size_t &rhs) noexcept {
        return Table::iterator_base<E>(lhs.target, lhs.shift + rhs);
    }

    template<class E>
    Table::iterator_base<E> operator-(const Table::iterator_base<E> &lhs, const std::size_t &rhs) noexcept {
        return Table::iterator_base<E>(lhs.target, lhs.shift - rhs);
    }

    template<class Rhs, class Lhs>
    bool operator==(const Table::iterator_base<Lhs> &lhs, const Table::iterator_base<Rhs> &rhs) noexcept {
        return lhs.shift == rhs.shift;
    }

    template<class Rhs, class Lhs>
    bool operator!=(const Table::iterator_base<Lhs> &lhs, const Table::iterator_base<Rhs> &rhs) noexcept {
        return lhs.shift != rhs.shift;
    }
}

#endif //POINT_VORTEX_TABLE_H
