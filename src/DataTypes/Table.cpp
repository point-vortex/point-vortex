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

#include "DataTypes/Table.h"


namespace DTypes {
    extern DTProto_t DTProto;

// ----------------------------------------------------------------------------------------------------------- TABLE ---
    Table::Table() : _size(0) {}

    Table::Table(const Table &reference) : _size(reference._size), data(), _capacity(reference._size) {
        this->append(reference);
    }

    Table::~Table() {
        storage_t::iterator column = this->data.begin();
        while (column != this->data.end()) {
            column = this->dropColumn(column);
        }
    }

    Table &Table::append(const const_row &row) {
        storage_t::iterator column;
        for (const std::pair<const QString, const DataType *> &record: row) {
            column = this->createColumn(record.first, record.second->type());
            column->second.first.emplace_back(record.second->copy());
        }
        ++this->_size;
        this->syncCapacity();
        this->syncAllColumns();
        return *this;
    }

    Table &Table::append(const Table &table) {
        storage_t::iterator column;
        for (const std::pair<const QString, map_item_t> &incomingColumn: table.data) {
            column = this->createColumn(incomingColumn.first, incomingColumn.second.second);
            vector_t &array = column->second.first;
            array.reserve(array.size() + table._size);
            for (DataType *record: incomingColumn.second.first) {
                array.emplace_back(record->copy());
            }
        }
        this->_size += table._size;
        this->syncCapacity();
        this->syncAllColumns();
        return *this;
    }

    Table &Table::emplace(const Table::row &row) {
        storage_t::iterator column;
        for (const std::pair<const QString, DataType *> &record: row) {
            column = this->createColumn(record.first, record.second->type());
            column->second.first.emplace_back(record.second);
        }
        ++this->_size;
        this->syncCapacity();
        this->syncAllColumns();
        return *this;
    }

    Table &Table::emplace(const Table &table) {
        storage_t::iterator column;
        for (const std::pair<const QString, map_item_t> &incomingColumn: table.data) {
            column = this->createColumn(incomingColumn.first, incomingColumn.second.second);
            vector_t &array = column->second.first;
            const vector_t &incomingArray = incomingColumn.second.first;

            array.reserve(array.size() + table._size);
            array.insert(array.end(), incomingArray.begin(), incomingArray.end());
        }
        this->_size += table._size;
        this->syncCapacity();
        this->syncAllColumns();
        return *this;
    }

    Table::storage_t::iterator Table::dropColumn(const storage_t::iterator &column) noexcept {
        if (column != this->data.end()) {
            for (DataType *record: column->second.first) {
                delete (record);
            }
            column->second.first.clear();
            return this->data.erase(column);
        }
        return column;
    }

    Table &Table::addColumn(const QString &name, const TYPES &type) {
        this->createColumn(name, type);
        return *this;
    }

    Table &Table::addColumn(const QString &name, const DataType *defVal) noexcept {
        this->createColumn(name, defVal);
        return *this;
    }

    Table::storage_t::iterator Table::createColumn(const QString &name, const TYPES &type) {
        auto prototype = DTProto.find(type);
        if (prototype == DTProto.end()) {
            //TODO: throw an error
        }
        return this->createColumn(name, prototype->second);
    }

    Table::storage_t::iterator Table::createColumn(const QString &name, const DataType *defVal) noexcept {
        storage_t::iterator column = this->data.find(name);
        if (column != this->data.end()) {
            vector_t &array = column->second.first;
            // Clear column
            if (column->second.second != defVal->type()) {
                this->dropColumn(column);
            } else {
                return column;
            }
        }

        // Create column
        auto result = this->data.insert(std::make_pair(name, std::make_pair(vector_t{}, defVal->type())));
        column = result.first;

        // Fill column with default value
        for (std::size_t i = 0; i < this->_size; i++) {
            column->second.first.emplace_back(defVal->copy());
        }
        return column;
    }

    void Table::syncColumn(const storage_t::iterator &column) noexcept {
        auto defVal = DTProto.find(column->second.second);
        if (defVal == DTProto.end()) {
            //TODO: throw an error
        }


        vector_t &array = column->second.first;
        if (array.size() < this->_size) {
            array.reserve(this->_size);
            while (array.size() < this->_size) {
                array.push_back(defVal->second->copy());
            }
        }
    }

    void Table::syncAllColumns() noexcept {
        for (storage_t::iterator column = this->data.begin(); column != this->data.end(); column++) {
            this->syncColumn(column);
        }
    }

    Table &Table::dropColumn(const QString &name) noexcept {
        storage_t::iterator column = this->data.find(name);
        this->dropColumn(column);
        return *this;
    }

    Table::const_iterator Table::cbegin() noexcept {
        return Table::const_iterator(this, 0);
    }

    Table::const_iterator Table::cend() noexcept {
        return Table::const_iterator(this, this->_size);
    }

    Table::iterator Table::begin() noexcept {
        return Table::iterator(this, 0);
    }

    Table::iterator Table::end() noexcept {
        return Table::iterator(this, this->_size);
    }

    Table &Table::reserve(const std::size_t &newCapacity) {
        if (this->_capacity < newCapacity) return *this;
        this->_capacity = newCapacity;
        for (std::pair<const QString, map_item_t> &column : this->data) {
            column.second.first.reserve(newCapacity);
        }
        return *this;
    }

    std::size_t Table::capacity() const noexcept {
        return this->_capacity;
    }

    std::size_t Table::size() const noexcept {
        return this->_size;
    }

    std::ostream &Table::print(std::ostream &os) const noexcept {
        //TODO: rewrite with self iterators
        for (auto column : this->data) {
            vector_t &array = column.second.first;
            os << column.first.toStdString();
            for (auto record : array) {
                os << " ";
                record->print(os);
            }
            os << std::endl;
        }
        return os;
    }

    Table *Table::copy() const {
        return new Table(*this);
    }

// ------------------------------------------------------------------------------------------------------------- ROW ---
//    template<class T>
//    Table::row_base<T>::~row_base() {
//        for (const std::pair<QString, DataType *> record: *this) {
//            delete record.second;
//        }
//    }



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
            : target(target), shift(shift), _row() {}

    template<class T>
    T &Table::iterator_base<T>::sync() noexcept {
        if (this->target->_size < this->shift) {
            for (const std::pair<QString, Table::map_item_t> &column: target->data) {
                this->_row.insert(std::make_pair(column.first, column.second.first.at(shift)));
            }
        }
        return this->_row;
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
        return this->_row;
    }

    template<class T>
    typename Table::iterator_base<T>::pointer Table::iterator_base<T>::operator->() noexcept {
        return &this->_row;
    }

    template<class E>
    Table::iterator_base<E> operator+(const Table::iterator_base<E> &lhs, const std::size_t &rhs) noexcept {
        return Table::iterator_base<E>(lhs.target, lhs.shift + rhs);
    }

    template<class E>
    Table::iterator_base<E> operator-(const Table::iterator_base<E> &lhs, const std::size_t &rhs) noexcept {
        return Table::iterator_base<E>(lhs.target, lhs.shift - rhs);
    }

    template<class Lhs, class Rhs>
    bool operator==(const Table::iterator_base<Lhs> &lhs, const Table::iterator_base<Rhs> &rhs) noexcept {
        return lhs.shift == rhs.shift;
    }

    template<class Lhs, class Rhs>
    bool operator!=(const Table::iterator_base<Lhs> &lhs, const Table::iterator_base<Rhs> &rhs) noexcept {
        return lhs.shift != rhs.shift;
    }

    template
    class Table::iterator_base<Table::row>;

    template
    class Table::iterator_base<Table::const_row>;

    template
    class Table::row_base<const DataType *>;

    template
    class Table::row_base<DataType *>;

    // Table methods.
    template Table::iterator Table::erase<Table::row>(const Table::iterator_base<Table::row> &position) noexcept;
    template Table::iterator
    Table::erase<Table::const_row>(const Table::iterator_base<Table::const_row> &position) noexcept;

    // ITERATOR OPERATOR !=
    template bool operator!=<Table::row, Table::row>(const Table::iterator_base<Table::row> &,
                                                     const Table::iterator_base<Table::row> &) noexcept;
    template bool operator!=<Table::const_row, Table::row>(const Table::iterator_base<Table::const_row> &,
                                                           const Table::iterator_base<Table::row> &) noexcept;
    template bool operator!=<Table::row, Table::const_row>(const Table::iterator_base<Table::row> &,
                                                           const Table::iterator_base<Table::const_row> &) noexcept;
    template bool operator!=<Table::const_row, Table::const_row>(const Table::iterator_base<Table::const_row> &,
                                                                 const Table::iterator_base<Table::const_row> &) noexcept;


    // ITERATOR OPERATOR ==
    template bool operator==<Table::row, Table::row>(const Table::iterator_base<Table::row> &,
                                                     const Table::iterator_base<Table::row> &) noexcept;
    template bool operator==<Table::const_row, Table::row>(const Table::iterator_base<Table::const_row> &,
                                                           const Table::iterator_base<Table::row> &) noexcept;
    template bool operator==<Table::row, Table::const_row>(const Table::iterator_base<Table::row> &,
                                                           const Table::iterator_base<Table::const_row> &) noexcept;
    template bool operator==<Table::const_row, Table::const_row>(const Table::iterator_base<Table::const_row> &,
                                                                 const Table::iterator_base<Table::const_row> &) noexcept;


    // ITERATOR OPERATOR +
    template Table::iterator_base<Table::row> operator+<Table::row>(const Table::iterator_base<Table::row> &,
                                                                    const std::size_t &) noexcept;
    template Table::iterator_base<Table::const_row>
    operator+<Table::const_row>(const Table::iterator_base<Table::const_row> &,
                                const std::size_t &) noexcept;


    // ITERATOR OPERATOR -
    template Table::iterator_base<Table::row> operator-<Table::row>(const Table::iterator_base<Table::row> &,
                                                                    const std::size_t &) noexcept;
    template Table::iterator_base<Table::const_row>
    operator-<Table::const_row>(const Table::iterator_base<Table::const_row> &,
                                const std::size_t &) noexcept;
}

