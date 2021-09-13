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

#include <iostream>

#include <gtest/gtest.h>

#include "DataTypes/Table.h"

// /**
// * @see https://github.com/google/googletest/blob/master/docs/advanced.md#death-tests
// */
// EXPECT_DEATH((std::raise(SIGTERM)), "");

TEST(DTypes__Table, Creation) {
    auto executor = []() {
        DTypes::Table table{};
    };

    ASSERT_EXIT(
            (executor(), exit(0)),
            ::testing::ExitedWithCode(0),
            ".*");
}

TEST(DTypes__Table, Copy_constructor) {
    DTypes::Table table1{};

    DTypes::Table::row row;
    row.insert(std::make_pair("foo", new DTypes::Integer(1)));
    row.insert(std::make_pair("bar", new DTypes::Float(1.0f)));
    table1.emplace(row);

    row.clear();
    row.insert(std::make_pair("bar", new DTypes::Float(2.0f)));
    table1.emplace(row);

    DTypes::Table table2 = table1;
    table1.clear();

    ASSERT_EQ(table1.size(), 0);
    ASSERT_EQ(table2.size(), 2);
    ASSERT_EQ(table1.columns().size(), 0);
    ASSERT_EQ(table2.columns().size(), 2);
    ASSERT_EQ((dynamic_cast<DTypes::Integer*>(table2.begin()->at("foo"))->get()), 1);
}

TEST(DTypes__Table, Clear) {
    DTypes::Table table1{};
    DTypes::Table::row row;

    row.insert(std::make_pair("foo", new DTypes::Integer(1)));
    row.insert(std::make_pair("bar", new DTypes::Float(1.0f)));
    table1.emplace(row);

    row.clear();
    row.insert(std::make_pair("bar", new DTypes::Float(2.0f)));
    row.insert(std::make_pair("baz", new DTypes::Boolean(true)));
    table1.emplace(row);

    ASSERT_FALSE(table1.empty());
    table1.clear();
    ASSERT_TRUE(table1.empty());
    EXPECT_DEATH((dynamic_cast<DTypes::Integer *>(row.at("bar"))->get()),"");
}
