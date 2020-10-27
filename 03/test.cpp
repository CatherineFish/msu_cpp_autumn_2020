#include <iostream>

#include <cassert>

#include <string>

#include <fstream>

#include "Matrix.h"


void DefaultTest(void) {
    Matrix m_1(77, 84);
    assert(m_1.getRows() == 77 && m_1.getColumns() == 84);
    return;
}

void MultTest(void) {
    Matrix m_1(10, 15);
    int elem = 0;
    for (size_t i = 0; i < m_1.getRows(); i++) {
        for (size_t j = 0; j < m_1.getColumns(); j++) {
            m_1[i][j] = elem;
            elem++;
        }
        elem += 10;
    }
    m_1 *= 3;
    elem = 0;
    for (size_t i = 0; i < m_1.getRows(); i++) {
        for (size_t j = 0; j < m_1.getColumns(); j++) {
            assert(m_1[i][j] == elem * 3);
            elem++;
        }
        elem += 10;
    }
    return;
}

std::string FileComp(std::string f_1, std::string f_2) {
    std::ifstream fin1(f_1, std::ios::binary);
    std::ifstream fin2(f_2, std::ios::binary);
    if (fin2 && fin2) {
        char ch1, ch2;
        bool result = true;
        while (fin1.get(ch1) && fin2.get(ch2)) {
            if (ch1 != ch2) {
                result = false;
                break;
            }
        }
        fin1.close();
        fin2.close();
        if (result) {
            return "Equal";
        } else {
            return "Unequal";
        }
    } else {
        return "Error opening file";
    }
}

void PrintTest(void) {
    Matrix m_1(3, 5);
    int elem = 0;
    for (size_t i = 0; i < m_1.getRows(); i++) {
        for (size_t j = 0; j < m_1.getColumns(); j++) {
            m_1[i][j] = elem;
            elem++;
        }
        elem += 10;
    }
    std::ofstream file_1("result.txt");
    file_1 << m_1;
    file_1.close();
    assert(FileComp("result.txt", "ref.txt") == "Equal");
    return;
}

void AddTest(void) {
    Matrix m_1(10, 15), m_2(10, 15);
    int elem = 0, elem_2 = 10;
    for (size_t i = 0; i < m_1.getRows(); i++) {
        elem += 10;
        elem_2 += 10;
        for (size_t j = 0; j < m_1.getColumns(); j++) {
            m_1[i][j] = elem;
            m_2[i][j] = elem_2;
            elem++;
            elem_2++;
        }
    }
    elem = 0;
    elem_2 = 10;
    Matrix m_3 = m_1 + m_2;
    for (size_t i = 0; i < m_3.getRows(); i++) {
        elem += 10;
        elem_2 += 10;
        for (size_t j = 0; j < m_3.getColumns(); j++) {
            assert(m_3[i][j] = elem + elem_2);
            elem++;
            elem_2++;
        }
    }
    return;
}

void CompareTest(void) {
    Matrix m_1(10, 15), m_2(10, 15), m_3(10, 15);
    int elem = 0, elem_2 = 10;
    for (size_t i = 0; i < m_1.getRows(); i++) {
        elem += 10;
        elem_2 += 10;
        for (size_t j = 0; j < m_1.getColumns(); j++) {
            m_1[i][j] = elem;
            m_2[i][j] = elem_2;
            m_3[i][j] = elem;
            elem++;
            elem_2++;
        }
    }
    assert(m_1 == m_3);
    assert(m_1 != m_2);
    return;
}

void OutOfRange(void) {
    Matrix m_1(50, 80);
    std::string res_1 = "";
    std::string res_2 = "";
    try {
        int elem = m_1[50][1];
    } catch (std::out_of_range & exeption) {
        res_1 = exeption.what();
    }
    try {
        int elem = m_1[1][80];
    } catch (std::out_of_range & exeption) {
        res_2 = exeption.what();
    }
    assert(res_1 == "Row Index");
    assert(res_2 == "Column Index");
    return;
}

int main(void) {
    DefaultTest();
    MultTest();
    PrintTest();
    AddTest();
    CompareTest();
    OutOfRange();
    std::cout << "Success!\n";
    return 0;
}