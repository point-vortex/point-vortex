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
    /**
     * Table - NFlow context data type for storing tables of information.
     * @note
     * - Table can contain one value type per column.
     *
     * @author Danil Andreev
     */
    class Table : public DataType {
    private:
        /**
         * row_base - class for single column row representation.
         * @tparam T - "DataType *" or "const DataType *"
         */
        template<class T>
        class row_base : public std::map<QString, T> {
            static_assert(std::is_same<T, const DataType *>::value || std::is_same<T, DataType *>::value,
                          "Only 'DataType*' and 'const DataType*' are acceptable.");
        };

    public:
        /// row - single table row representation.
        using row = row_base<DataType *>;
        /// const_row - single table row representation with constant access.
        using const_row = row_base<const DataType *>;
    public:
        /**
         * iterator_base - base class for table iterator.
         * @tparam T - "row" or "const_row"
         */
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
            /// target - pointer to the target table.
            Table *target;
            /// shift - table records shift from 0 record.
            std::size_t shift;
            /// _row - current table row representation.
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
        /// const_iterator - constant table forward iterator.
        using const_iterator = iterator_base<const_row>;
        /// const_iterator - table forward iterator.
        using iterator = iterator_base<row>;
        friend iterator;
        friend const_iterator;
    protected:
        using vector_t = std::vector<DataType *>;
        using map_item_t = std::pair<std::vector<DataType *>, TYPES>;
        using storage_t = std::map<QString, map_item_t>;
    private:
        /// data - container for table data.
        storage_t data;
        /// _size - table size;
        std::size_t _size;
        /// _capacity - table capacity. Reserved memory for new records.
        std::size_t _capacity;
    public:
        Table();
        Table(const Table &reference);
        ~Table() override;
    public:
        /// Appends a COPY of each record members to the end of the table.
        Table &append(const const_row &row);
        /// Appends a COPY of each table column members to the end of the table.
        Table &append(const Table &table);
        /// Appends a POINTER of each record members to the end of the table.
        Table &emplace(const row &row);
        /// Appends a POINTER of each table column members to the end of the table.
        Table &emplace(const Table &table);
    public:
        /// Drops column with selected name. If column does not exist - ignore.
        Table &dropColumn(const QString &name) noexcept;
        /// Creates new column with selected name and type.
        /// If column is already exists - it will be replaced.
        Table &addColumn(const QString &name, const TYPES &type);
        /// Creates new column with selected name and fills it with copies of passed value.
        /// If column is already exists - it will be replaced.
        Table &addColumn(const QString &name, const DataType *defaultValue) noexcept;
    public:
        //TODO: add template type checks.
        /// Erases data on the selected position.
        template<class T>
        iterator erase(const iterator_base<T> &position) noexcept;
        //TODO: add template type checks.
        /// Erases data in the selected range.
        template<class T>
        iterator erase(const iterator_base<T> &from, const iterator_base<T> &to) noexcept;
    public:
        /// Clears the table. All records and columns will be deleted.
        void clear();
        /// Returns true when the table is empty. False unless.
        [[nodiscard]] bool empty() const noexcept;
    public:
        /// Returns vector of table columns names.
        [[nodiscard]] std::vector<QString> columns() const noexcept;
    public:
        /// Returns iterator that points to the table first record.
        iterator begin() noexcept;
        /// Returns iterator that points to the one table record after the last.
        iterator end() noexcept;
        /// Returns const iterator that points to the one table record after the last.
        const_iterator cbegin() noexcept;
        /// Returns const iterator that points to the one table record after the last.
        const_iterator cend() noexcept;
    public:
        /// Reserves memory for n elements if n is greater than current capacity.
        Table &reserve(const std::size_t &newCapacity);
        /// Returns current table capacity.
        [[nodiscard]] std::size_t capacity() const noexcept;
        /// Returns the quantity of table records.
        [[nodiscard]] std::size_t size() const noexcept;
    private:
        storage_t::iterator dropColumn(const storage_t::iterator &column) noexcept;
    private:
        storage_t::iterator createColumn(const QString &name, const TYPES &type);
        storage_t::iterator createColumn(const QString &name, const DataType *defaultValue) noexcept;
        void syncColumn(const storage_t::iterator &column) noexcept;
        inline void syncAllColumns() noexcept;
        inline void syncCapacity() noexcept;
    public:
        std::ostream &print(std::ostream &os) const noexcept override;
    public:
        [[nodiscard]] Table *copy() const override;
    };
}

#endif //POINT_VORTEX_TABLE_H
