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

#include "Table.h"

#include <utility>

namespace DTypes {
    Table::Table(): data() {

    }

    Table::Table(const Table &reference): data(reference.data) {

    }

    Table *Table::copy() const {
        return new Table(*this);
    }



    Table::Iterator::Iterator(Table *ptr, size_t row): rowsShift(row), table(ptr) {}

    Table::Iterator &Table::Iterator::operator++() {
        ++this->rowsShift;
        return *this;
    }

    Table::Iterator Table::Iterator::operator++(int) {
        ++this->rowsShift;
        return Table::Iterator(table);
    }

    Table::Iterator &Table::Iterator::operator--() {
        --this->rowsShift;
        return *this;
    }

    Table::Iterator Table::Iterator::operator--(int) {
        --this->rowsShift;
        return Table::Iterator(table);
    }

    bool operator==(const Table::Iterator &left, const Table::Iterator &right) {
        return left.rowsShift == right.rowsShift;
    }

    bool operator!=(const Table::Iterator &left, const Table::Iterator &right) {
        return left.rowsShift != right.rowsShift;
    }

    Table::Iterator::value_type &Table::Iterator::operator*() const {
        Table::Row row{};
        for (std::pair<const QString, std::vector<DataType *>>& item : this->table->data) {
            row.data.insert(std::make_pair(item.first, item.second.at(this->rowsShift)));
        }
        return row;
    }

    Table::Iterator::pointer Table::Iterator::operator->() {
        return nullptr;
    }
}
