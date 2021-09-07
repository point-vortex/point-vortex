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
        for (const std::pair<QString, DataType *> record : row) {
            column = this->createColumn(record.first, record.second->type());
            column->second.first.emplace_back(record.second->copy());
        }
        ++this->size;
        return *this;
    }

    Table &Table::append(const Table &table) {
        storage_t::iterator column;
        for (const std::pair<QString, map_item_t> incomingColumn : table.data) {
            column = this->createColumn(incomingColumn.first, incomingColumn.second.second);
            vector_t &array = column->second.first;
            array.reserve(array.size() + table.size);
            for (DataType *record : incomingColumn.second.first) {
                array.emplace_back(record->copy());
            }
        }
        this->size += table.size;
        return *this;
    }

    Table &Table::emplace(const Table::Row &row) {
        storage_t::iterator column;
        for (const std::pair<QString, DataType *> record : row) {
            column = this->createColumn(record.first, record.second->type());
            column->second.first.emplace_back(record.second);
        }
        ++this->size;
        return *this;
    }

    Table &Table::emplace(const Table &table) {
        storage_t::iterator column;
        for (const std::pair<QString, map_item_t> incomingColumn : table.data) {
            column = this->createColumn(incomingColumn.first, incomingColumn.second.second);
            vector_t &array = column->second.first;
            const vector_t &incomingArray = incomingColumn.second.first;

            array.reserve(array.size() + table.size);
            array.insert(array.end(), incomingArray.begin(), incomingArray.end());
        }
        this->size += table.size;
        return *this;
    }

    Table::storage_t::iterator Table::dropColumn(const storage_t::iterator &column) noexcept {
        if (column != this->data.end()) {
            for (DataType *record : column->second.first) {
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
        storage_t::iterator column;
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
        for (const std::pair<QString, Table::map_item_t> &column: this->data) {
            
        }
        return Table::iterator(nullptr); //TODO: finish return
    }

    Table::iterator Table::erase(const Table::const_iterator &position) noexcept {
        return this->erase(position, position + 1);
    }


// ------------------------------------------------------------------------------------------------------------- ROW ---
    Table::Row::~Row() {
        for (const std::pair<QString, DataType *> record: *this) {
            delete record.second;
        }
    }

// -------------------------------------------------------------------------------------------------- CONST ITERATOR ---
    Table::const_iterator::const_iterator(Table *target, std::size_t shift) : target(target), shift(shift), row() {
        if (target->size < shift) {
            for (const std::pair<QString, Table::map_item_t> &column: target->data) {
                this->row.insert(std::make_pair(column.first, column.second.first.at(shift)));
            }
        }
    }

// -------------------------------------------------------------------------------------------------------- ITERATOR ---
    Table::iterator::iterator(Table *target, std::size_t shift) : const_iterator(target, shift) {}
}

