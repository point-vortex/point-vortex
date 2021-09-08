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
    Table::Table() : size(0) {}

    Table::Table(const Table &reference) : size(reference.size), data() {
        this->append(reference);
    }

    Table::~Table() {
        storage_t::iterator column = this->data.begin();
        while (column != this->data.end()) {
            column = this->dropColumn(column);
        }
    }

    Table &Table::append(const Row &row) {
        storage_t::iterator column;
        for (const std::pair<const QString, DataType *>& record: row) {
            column = this->createColumn(record.first, record.second->type());
            column->second.first.emplace_back(record.second->copy());
        }
        ++this->size;
        this->syncAllColumns();
        return *this;
    }

    Table &Table::append(const Table &table) {
        storage_t::iterator column;
        for (const std::pair<const QString, map_item_t>& incomingColumn: table.data) {
            column = this->createColumn(incomingColumn.first, incomingColumn.second.second);
            vector_t &array = column->second.first;
            array.reserve(array.size() + table.size);
            for (DataType *record: incomingColumn.second.first) {
                array.emplace_back(record->copy());
            }
        }
        this->size += table.size;
        this->syncAllColumns();
        return *this;
    }

    Table &Table::emplace(const Table::Row &row) {
        storage_t::iterator column;
        for (const std::pair<const QString, DataType *>& record: row) {
            column = this->createColumn(record.first, record.second->type());
            column->second.first.emplace_back(record.second);
        }
        ++this->size;
        this->syncAllColumns();
        return *this;
    }

    Table &Table::emplace(const Table &table) {
        storage_t::iterator column;
        for (const std::pair<const QString, map_item_t>& incomingColumn: table.data) {
            column = this->createColumn(incomingColumn.first, incomingColumn.second.second);
            vector_t &array = column->second.first;
            const vector_t &incomingArray = incomingColumn.second.first;

            array.reserve(array.size() + table.size);
            array.insert(array.end(), incomingArray.begin(), incomingArray.end());
        }
        this->size += table.size;
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
        for (std::size_t i = 0; i < this->size; i++) {
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
        if (array.size() < this->size) {
            array.reserve(this->size);
            while (array.size() < this->size) {
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
        return Table::const_iterator(this, this->size);
    }

    Table::iterator Table::begin() noexcept {
        return Table::iterator(this, 0);
    }

    Table::iterator Table::end() noexcept {
        return Table::iterator(this, this->size);
    }

    Table::iterator Table::erase(const Table::const_iterator &from, const Table::const_iterator &to) noexcept {
        if (from.shift >= to.shift) return Table::iterator(this, from.shift);

        for (std::pair<const QString, map_item_t> & column : this->data) {
            vector_t &array = column.second.first;
            vector_t::iterator arrayBegin = array.begin();
            auto start = arrayBegin + static_cast<long long>(from.shift);
            auto finish = arrayBegin + static_cast<long long>(to.shift);
            for (auto record = start; record != finish; record++) {
                delete *record.base();
            }
            array.erase(start, finish);
        }
        this->size -= to.shift - from.shift;
        return Table::iterator(this, from.shift); //TODO: finish return
    }

    Table::iterator Table::erase(const Table::const_iterator &position) noexcept {
        return this->erase(position, position + 1);
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
    Table::Row::~Row() {
        for (const std::pair<QString, DataType *> record: *this) {
            delete record.second;
        }
    }

// -------------------------------------------------------------------------------------------------- CONST ITERATOR ---
    Table::const_iterator::const_iterator(Table *target, std::size_t shift) : target(target), shift(shift), row() {
        this->sync();
    }

    void Table::const_iterator::sync() noexcept {
        if (this->target->size < this->shift) {
            for (const std::pair<QString, Table::map_item_t> &column: target->data) {
                this->row.insert(std::make_pair(column.first, column.second.first.at(shift)));
            }
        }
    }

    Table::const_iterator &Table::const_iterator::operator++() noexcept {
        ++this->shift;
        return *this;
    }

    Table::const_iterator Table::const_iterator::operator++(int) noexcept {
        Table::const_iterator old{*this};
        ++this->shift;
        return old;
    }

    Table::const_iterator &Table::const_iterator::operator--() noexcept {
        --this->shift;
        return *this;
    }

    Table::const_iterator Table::const_iterator::operator--(int) noexcept {
        Table::const_iterator old{*this};
        --this->shift;
        return old;
    }

    Table::const_iterator &Table::const_iterator::operator+=(std::size_t x) noexcept {
        this->shift += x;
        return *this;
    }

    Table::const_iterator &Table::const_iterator::operator-=(std::size_t x) noexcept {
        this->shift -= x;
        return *this;
    }

    Table::Row &Table::const_iterator::operator*() noexcept {
        return this->row;
    }

    Table::Row *Table::const_iterator::operator->() noexcept {
        return &this->row;
    }

    Table::const_iterator operator+(const Table::const_iterator &lhs, const std::size_t shift) {
        return Table::const_iterator(lhs.target, lhs.shift + shift);
    }

    Table::const_iterator operator-(const Table::const_iterator &lhs, const std::size_t shift) {
        return Table::const_iterator(lhs.target, lhs.shift - shift);
    }

// -------------------------------------------------------------------------------------------------------- ITERATOR ---
    Table::iterator::iterator(Table *target, std::size_t shift) : const_iterator(target, shift) {}
}

