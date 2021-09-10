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

#include <csignal>
#include <iostream>

#include <QApplication>
#include <QPushButton>

//-----TEMP INCLUDe
#include "DataTypes/Table.h"
//-----

void handleSIGINT(int signum) {
    //TODO: cleanup;
    exit(signum);
}

int main(int argc, char *argv[]) {
    DTypes::Table table1;
    DTypes::Table::Row row;
    row.insert(std::make_pair("hello", new DTypes::Integer(1)));
    row.insert(std::make_pair("my", new DTypes::Float(2.0f)));
    table1.emplace(row);

    row.clear();
    row.insert(std::make_pair("hello", new DTypes::Integer(2)));
    row.insert(std::make_pair("darkness", new DTypes::Float(3.0f)));

    table1.emplace(row);


    std::cout << "table1" << std::endl;
    table1.print(std::cout);


    DTypes::Table table2;
    row.insert(std::make_pair("hello", new DTypes::Integer(11)));
    row.insert(std::make_pair("lol", new DTypes::Float(21.0f)));
    table2.emplace(row);

    row.clear();
    row.insert(std::make_pair("kek", new DTypes::Integer(5)));
    row.insert(std::make_pair("darkness", new DTypes::Float(10.0f)));

    table2.emplace(row);

    std::cout << "table2" << std::endl;
    table2.print(std::cout);

    DTypes::Table table3;
    table3.append(table1);
    std::cout << "table3t1" << std::endl;
    table3.print(std::cout);
    table3.append(table2);
    std::cout << "table3t2" << std::endl;
    table3.print(std::cout);


    table3.erase(table3.begin());
    std::cout << "table3t3" << std::endl;
    table3.print(std::cout);

    table3.erase(table3.begin(), table3.begin() + 2);
    std::cout << "table3t4" << std::endl;
    table3.print(std::cout);

    DTypes::Table* table4 = new DTypes::Table();
    table4->append(table3);
    table4->append(table2);
    std::cout << "table4t1" << std::endl;
    table4->print(std::cout);

    std::cout << "table4t2 (t3 exists)" << std::endl;
    delete table4;
    table3.print(std::cout);


    for (const auto& a : table3) {
        dynamic_cast<DTypes::Integer*>(a.at("aa"))->set(1);
        a.at("aa")->a();
    }

    table3.cbegin()->at("a")->a();
    for (auto i = table3.cbegin(); i != table3.cend(); i++) {
        dynamic_cast<DTypes::Integer*>(i->at("aa"))->set(1);
        i->at("aa")->a();
    }

    signal(SIGINT, handleSIGINT);

    QApplication a(argc, argv);
    QPushButton button("Hello world!", nullptr);
    button.resize(200, 100);
    button.show();
    return QApplication::exec();
}
