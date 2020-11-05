#include <iostream>

#include <string>

#include <sstream>

#include <cassert>

#include "BigInt.h"

void PrintTest(void) {
    BigInt a("1566778899000000087656789"), b("-123456789123456787654456789");
    std::stringstream test_out, ref_out;
    test_out << a << b;
    ref_out << "1566778899000000087656789" << std::endl;
    ref_out << "-123456789123456787654456789" << std::endl;
    assert(test_out.str() == ref_out.str());
    return;
}

void AddTest(void) {
    BigInt a("156677889900"), b("123456789123456789");
    assert((a + b) == BigInt("123456945801346689"));
    a = b;
    BigInt c = -2000000, d;
    d = -a + c;
    assert(d == BigInt("-123456789125456789"));
    assert((a + c) == BigInt("123456789121456789"));
    assert(BigInt("765456789") + BigInt("16782387612") ==
        BigInt("17547844401"));
    assert(BigInt("-34242765456789") + BigInt("-2354516782387612") ==
        BigInt("-2388759547844401"));
    assert(BigInt("765456734289") + BigInt("0") ==
        BigInt("765456734289"));
    return;
}

void SubTest(void) {
    BigInt a("156677889900"), b("123456789123456789");
    assert((b - a) == BigInt("123456632445566889"));
    assert((a - b) == BigInt("-123456632445566889"));
    BigInt c = -27892345, d = -1000000000;
    assert((d - c) == BigInt("-972107655"));
    assert((a - d) == BigInt("157677889900"));
    assert(BigInt("99999999999999999999999") - BigInt("99999999999999999999999") == 0);
    assert(BigInt("78978978799") - BigInt("567890") ==
        BigInt("78978410909"));
    assert(BigInt("-9090909090") - BigInt("8987654") ==
        BigInt("-9099896744"));
    assert(BigInt("8") - BigInt("5678909876") == BigInt("-5678909868"));
    assert(BigInt("12345678") - BigInt("12345876") == -198);
    assert(-BigInt("8978") - BigInt("89898") == -98876);
    assert(-BigInt("593") - BigInt("-933245484") ==
        BigInt("933244891"));
    assert(BigInt("87654323456789009876543234567890") - BigInt("9876543212345678900987654321345678") ==
        BigInt("-9788888888888889891111111086777788"));
    return;
}

void MulTest(void) {
    BigInt a, b("123456789123456789");
    assert((b * a) == BigInt("0"));
    BigInt c = 10000;
    BigInt d("567898765"), g("-567890987654");
    assert((d * g) == BigInt("-322504590543336847310"));
    BigInt n = c * d + 2;
    assert(n == BigInt("5678987650002"));
    assert(BigInt(24554325) * BigInt(3456256) ==
        BigInt("84866033107200"));
    assert(BigInt("24554325345654345543632") * BigInt("3456787654323456256") ==
        BigInt("84879088715099474371588276399001491361792"));
    assert(BigInt("-3") * BigInt("3456787654323456256") ==
        BigInt("-10370362962970368768"));
    assert(BigInt("1234567890") * BigInt("987654321") ==
        BigInt("1219326311126352690"));
    assert(-BigInt("10000000000") * BigInt("10000000000") ==
        BigInt("-100000000000000000000"));
    assert(-BigInt("9999999999") * BigInt("-9999999999") ==
        BigInt("99999999980000000001"));
    assert(-BigInt("-1234567890987654321") * -BigInt("1234567890") ==
        BigInt("-1524157876238378411126352690"));
    assert(BigInt("-3243567543") * BigInt("-10000234234") ==
        BigInt("32436435183799867062"));
    assert(BigInt("1245676543234567898765433243567543") * BigInt("-100000000000234234") ==
        BigInt("-124567654323748569675971330133953722490373799867062"));
    assert(BigInt("1245676543234567898213456543234567898765432765433243567543") * BigInt("10000000000023124565432123454234") ==
        BigInt("12456765432374484710865854558675619570853438888877720988896320824753376277736342448327062"));
    assert(BigInt("99999999999999999999999") * BigInt("99999999999999999999999") ==
        BigInt("9999999999999999999999800000000000000000000001"));
    BigInt e("99999999999999999999999");
    e = e * e;
    assert(e == BigInt("9999999999999999999999800000000000000000000001"));
    return;
}

void UnaryMinusTest(void) {
    BigInt a = 0, b("123456789123456789"), c("-909090909090");
    assert(a == -a);
    assert(-b == BigInt("-123456789123456789"));
    assert(-c == BigInt("909090909090"));
    assert(c == -BigInt("909090909090"));
    return;
}

void CompTest(void) {
    BigInt a = 6, b("123456789123456789");
    assert((a < b) == true);
    BigInt d("904345241132514"), e("-4326543245"), m("-6789");
    assert((m > e) == true);
    assert((d <= e) == false);
    assert((m >= e) == true);
    assert((m >= m) == true);
    assert((e != BigInt("-4326543245")) == false);
    assert((d == BigInt("904345241132514")) == true);
    return;
}

void DefaultTest(void) {
    BigInt a = 1;
    BigInt b("123456789012345678901234567890");
    assert(a == 1);
    assert(b == BigInt("123456789012345678901234567890"));
    BigInt c = a * b + 2;
    assert(c == BigInt("123456789012345678901234567892"));
    BigInt e(b);
    assert(e == BigInt("123456789012345678901234567890"));
    BigInt d;
    d = std::move(c);
    assert(d == BigInt("123456789012345678901234567892"));
    a = d + b;
    assert(a == BigInt("246913578024691357802469135782"));
    assert(BigInt("005") == 5);
    assert(BigInt("-000000095") == -95);
    assert(-BigInt("-00000000000000000000000000000000000000095") == 95);
    assert(BigInt("0000000") == 0);
    assert(BigInt("-0000000") == 0);
    assert(BigInt("0") == BigInt(0));
    return;
}

int main(void) {
    PrintTest();
    AddTest();
    SubTest();
    MulTest();
    UnaryMinusTest();
    CompTest();
    DefaultTest();
    std::cout << "Success!\n";
    return 0;
}