#include <cassert>

#include <iostream>

#include "Vector.h"


void DefaultTest() {
    Vector < int > a;
    assert(a.size() == 0);
    assert(a.capacity() == 0);
    assert(a.empty() == true);

    Vector < double > b(16);
    assert(b.size() == 16);
    assert(b.capacity() == 16);
    assert(b.empty() == false);

    Vector < char > c(20, 'c');
    assert(c.size() == 20);
    assert(c.capacity() == 32);
    for (size_t i = 0; i < c.size(); i++) {
        assert(c[i] == 'c');
    }

    c.push_back('a');
    b.push_back(10.5);
    a.push_back(1);
    assert(c[c.size() - 1] == 'a');
    assert(b[16] == 10.5);
    assert(a[0] == 1);

    c.pop_back();
    assert(c[c.size() - 1] == 'c');

    b.emplace_back(1.2);
    b.emplace_back(28.9);
    assert(b[b.size() - 1] == 28.9 && b[b.size() - 2] == 1.2);

    b.clear();
    assert(b.size() == 0);

    c.resize(15);
    assert(c.size() == 15 && c.capacity() == 16);
    for (size_t i = 0; i < c.size(); i++) {
        assert(c[i] == 'c');
    }

    a.resize(33);
    assert(a.size() == 33 && a.capacity() == 64);

    b.reserve(56);
    assert(b.capacity() == 56);

    Vector < double > d(3, 78.9);
    d.push_back(5.5);
    d.push_back(5.5);
    d.push_back(5.5);
    d.push_back(5.5);
    d.push_back(5.5);
    d.push_back(5.5);
    assert(d.size() == 9 && d.capacity() == 16);
    for (size_t i = 0; i < d.size(); i++) {
        if (i < 3) {
            assert(d[i] == 78.9);
        } else {
            assert(d[i] == 5.5);
        }
    }
    return;
}

void IterTest() {
    Vector < unsigned short > a(17, 78);
    for (auto & i: a) {
        assert(i == 78);
    }

    Vector < unsigned long > b(89, 78980789867);
    auto i = b.begin();
    while (i < b.end()) {
        assert( * i == 78980789867);
        i += 5;
        i -= 3;
    }

    Vector < long > c(64, -100);
    auto j = c.rbegin();
    while (j >= c.rend()) {
        assert( * j == -100);
        j += 7;
        j -= 5;
    }

    return;
}

int main(void) {
    DefaultTest();
    IterTest();
    std::cout << "Success!\n";
    return 0;
}