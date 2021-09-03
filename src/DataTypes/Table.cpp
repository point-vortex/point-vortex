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

#include <utility>

namespace DTypes {
    Table::Table() : data(), rowsSize(0) {
    }

    Table::Table(const Table &reference) : data(reference.data), rowsSize(reference.rowsSize) {

    }

    Table *Table::copy() const {
        return new Table(*this);
    }


    Table::iterator::iterator(Table *ptr, std::size_t row) : rowsShift(row), table(ptr) {}

    void Table::iterator::updateRow() {
        this->row.erase(this->row.begin(), this->row.end());
        for (std::pair<const QString, std::vector<DataType *>> &item : this->table->data) {
            this->row.insert(std::make_pair(item.first, item.second.at(this->rowsShift)));
        }
    }

    Table::iterator &Table::iterator::operator++() {
        ++this->rowsShift;
        this->updateRow();
        return *this;
    }

    const Table::iterator Table::iterator::operator++(int) {
        ++this->rowsShift;
        this->updateRow();
        return {table};
    }

    Table::iterator &Table::iterator::operator--() {
        --this->rowsShift;
        this->updateRow();
        return *this;
    }

    const Table::iterator Table::iterator::operator--(int) {
        --this->rowsShift;
        this->updateRow();
        return {table};
    }

    bool operator==(const Table::iterator &left, const Table::iterator &right) {
        return left.rowsShift == right.rowsShift;
    }

    bool operator!=(const Table::iterator &left, const Table::iterator &right) {
        return left.rowsShift != right.rowsShift;
    }

    Table::iterator Table::begin() noexcept {
        return {this, 0};
    }

    Table::iterator Table::end() noexcept {
        return {this, this->rowsSize};
    }

    void Table::erase(size_t row) noexcept {

    }

    Table::iterator Table::erase(const Table::iterator& position) noexcept {
        if (position.rowsShift >= this->rowsSize) return this->end();
        for (std::pair<const QString, std::vector<DataType*>>& column : this->data) {
            column.second.erase(column.second.begin() + position.rowsShift);
        }
        return {nullptr, position.rowsShift};
    }

    Table::iterator Table::erase(const Table::iterator& begin, const Table::iterator &end) noexcept {
        if (begin.rowsShift >= this->rowsSize) return this->end();
        if (end.rowsShift > this->rowsSize) return this->end();
        for (std::pair<const QString, std::vector<DataType*>>& column : this->data) {
            auto vectorBegin = column.second.begin();
            column.second.erase(vectorBegin + begin.rowsShift, vectorBegin + end.rowsShift);
        }
        return Table::iterator(nullptr);
    }

    void Table::addColumn(const QString &name) noexcept {
        this->data.insert(std::make_pair(name, std::vector<DataType*>{}));
    }

    Table::iterator::reference &Table::iterator::operator*() {
        return this->row;
    }

    Table::iterator::pointer Table::iterator::operator->() {
        return &this->row;
    }
}
