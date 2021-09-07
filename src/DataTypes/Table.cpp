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
    Table::Table() : size(0) {

    }

    Table::Table(const Table &reference) {

    }

    Table &Table::append(const Row &row) {
        storage_t::iterator column;
        for (const std::pair<QString, DataType *> record : row.data) {
            column = this->createColumn(record.first, record.second->type());
            column->second.first.emplace_back(record.second->copy());
        }
        return *this;
    }

    Table &Table::append(const Table &table) {
        storage_t::iterator column;
        for (const std::pair<QString, map_item_t> incomingColumn : table.data) {
            column = this->createColumn(incomingColumn.first, incomingColumn.second.second);
            vector_t & array = column->second.first;
            array.reserve(array.size() + table.size);
            for (DataType* record : incomingColumn.second.first) {
                array.emplace_back(record->copy());
            }
        }
        return *this;
    }

    Table &Table::emplace(const Table::Row &row) {
        storage_t::iterator column;
        for (const std::pair<QString, DataType *> record : row.data) {
            column = this->createColumn(record.first, record.second->type());
            column->second.first.emplace_back(record.second);
        }
        return *this;
    }

    Table &Table::emplace(const Table &table) {
        storage_t::iterator column;
        for (const std::pair<QString, map_item_t> incomingColumn : table.data) {
            column = this->createColumn(incomingColumn.first, incomingColumn.second.second);
            vector_t & array = column->second.first;
            const vector_t & incomingArray = incomingColumn.second.first;

            array.reserve(array.size() + table.size);
            array.insert(array.end(), incomingArray.begin(), incomingArray.end());
        }
        return *this;
    }

    Table::storage_t::iterator Table::createColumn(const QString &name, const TYPES &type) {
        auto prototype = DTProto.find(type);
        if (prototype == DTProto.end()) {
            //TODO: throw an error
        }
        return this->createColumn(name, prototype->second);
    }

    Table::storage_t::iterator Table::createColumn(const QString &name, const DataType *defVal) {
        storage_t::iterator column;
        if (column != this->data.end()) {
            vector_t &array = column->second.first;
            // Clear column
            if (column->second.second != defVal->type()) {
                for (DataType *field : array) {
                    delete field;
                }
                array.erase(array.begin(), array.end());
            } else {
                return column;
            }
        } else {
            // Create column
            auto result = this->data.insert(std::make_pair(name, std::make_pair(vector_t{}, defVal->type())));
            column = result.first;
        }

        // Fill column with default value
        for (std::size_t i = 0; i < this->size; i++) {
            column->second.first.emplace_back(defVal->copy());
        }
        return column;
    }
}
