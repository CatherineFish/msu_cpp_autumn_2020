#include <string>

#include <iostream>

#pragma once

class BigInt {
    unsigned int * number_ = nullptr;
    size_t size_ = 0, real_size_ = 0;
    bool sign_ = true;
    public:
        BigInt(int val = 0);
    BigInt(const std::string & str, size_t size = 0);
    friend std::ostream & operator << (std::ostream & ostream,
        const BigInt & num);
    BigInt operator + (const BigInt & add) const;
    BigInt operator - (const BigInt & sub) const;
    BigInt SubWithOrder(const BigInt & minuend,
        const BigInt & sub) const;
    BigInt operator * (const BigInt & mul) const;
    BigInt operator * (unsigned int mul) const;
    BigInt operator - () const;
    bool operator == (const BigInt & other) const;
    bool operator != (const BigInt & other) const;
    bool operator > (const BigInt & other) const;
    bool operator < (const BigInt & other) const;
    bool operator >= (const BigInt & other) const;
    bool operator <= (const BigInt & other) const;
    BigInt(const BigInt & copied, size_t real_size = 0);
    BigInt & operator = (const BigInt & copied);
    BigInt(BigInt && moved);
    BigInt & operator = (BigInt && moved);
    ~BigInt();
};