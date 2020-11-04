#include <iostream>

#include <string>

#include "BigInt.h"

#include <algorithm>

BigInt::BigInt(int val) {
    int buf_val = val >= 0 ? val : -val;
    if (val < 0) {
        sign_ = false;
    }
    size_t new_size = 1, cur_size = 0;
    while (buf_val) {
        cur_size++;
        if (cur_size > new_size) {
            new_size *= 2;
        }
        buf_val /= 10;
    }
    number_ = new unsigned int[new_size];
    size_ = new_size;
    real_size_ = cur_size ? cur_size : 1;
    number_[0] = 0;
    buf_val = val >= 0 ? val : -val;
    size_t i = 0;
    while (buf_val) {
        number_[i] = buf_val % 10;
        buf_val /= 10;
        i++;
    }
}

BigInt::BigInt(const std::string & str, size_t size) {
    size_t new_size = 1, real_size = size ? size : str.length();
    real_size_ = real_size;
    size_t i = 0;
    if (!size && str != "") {
        if (str[i] == '-') {
            i++;
            real_size_--;
            sign_ = false;
        }
        while (str[i] == '0' && real_size_ > 1) {
            real_size_--;
            i++;
        }

    }
    while (new_size < real_size) {
        new_size *= 2;
    }
    number_ = new unsigned int[new_size];
    size_ = new_size;
    number_[0] = 0;
    if (str != "") {
        for (size_t i = 0; i < real_size_; i++) {
            number_[i] = str[real_size - i - 1] - '0';
        }
    } else {
        std::fill(number_, number_ + real_size_, 0);
    }
    if (real_size_ == 1 && number_[0] == 0) {
        sign_ = true;
    }
}

std::ostream & operator << (std::ostream & ostream,
    const BigInt & num) {
    if (!num.sign_)
        ostream << '-';
    for (size_t i = 0; i < num.real_size_; i++) {
        ostream << num.number_[num.real_size_ - 1 - i];
    }
    ostream << std::endl;
    return ostream;
}

BigInt BigInt::operator + (const BigInt & add) const {
    if (sign_ != add.sign_) {
        return *this - (-add);
    }
    BigInt result("0", std::max(real_size_, add.real_size_));
    unsigned int add_im = 0, cur_res;
    for (size_t i = 0; i < result.real_size_; i++) {
        cur_res = (i < real_size_ ? number_[i] : 0) +
            (i < add.real_size_ ? add.number_[i] : 0) + add_im;
        if (cur_res < 10) {
            result.number_[i] = cur_res;
            add_im = 0;
        } else {
            add_im = cur_res / 10;
            result.number_[i] = cur_res % 10;
        }
    }
    if (add_im) {
        result = BigInt(result, real_size_ + 1);
        result.number_[result.real_size_ - 1] = add_im;
    }
    result.sign_ = sign_;
    return result;
}

BigInt BigInt::operator - (const BigInt & sub) const {
    if (sign_ != sub.sign_)
        return *this + (-sub);
    if ( * this == sub) {
        return BigInt();
    }
    BigInt result;
    if ((sign_ && ( * this > sub)) || (!sign_ && ( * this < sub))) {
        result = SubWithOrder( * this, sub);
        result.sign_ = sign_;
    } else {
        result = SubWithOrder(sub, * this);
        result.sign_ = !sign_;
    }
    return result;
}

BigInt BigInt::SubWithOrder(const BigInt & minuend,
    const BigInt & sub) const {
    BigInt result(minuend);
    unsigned int sub_im = 0, cur_res, cur;
    for (size_t i = 0; i < result.real_size_; i++) {
        cur = sub_im + (i < sub.real_size_ ? sub.number_[i] : 0);
        cur_res = result.number_[i];
        if (cur_res < cur) {
            cur_res += 10;
            sub_im = 1;
        } else {
            sub_im = 0;
        }
        cur_res -= cur;
        result.number_[i] = cur_res;
    }
    while (result.number_[result.real_size_ - 1] == 0) {
        result.real_size_--;
    }
    return result;
}

BigInt BigInt::operator * (const BigInt & mul) const {
    if ( * this == 0 || mul == 0) {
        return BigInt();
    }
    BigInt result("", real_size_ + mul.real_size_);
    for (size_t i = 0; i < mul.real_size_; i++) {
        result = result + ( * this * mul.number_[mul.real_size_ - 1 - i]);
        if (i != (mul.real_size_ - 1)) {
            for (size_t j = result.real_size_ + 1; j >= 1; j--) {
                result.number_[j] = result.number_[j - 1];

            }

            result.number_[0] = 0;
            result.real_size_ += 1;
        }
    }
    if (sign_ != mul.sign_)
        result.sign_ = false;
    while (result.number_[result.real_size_ - 1] == 0) {
        result.real_size_--;
    }
    return result;
}

BigInt BigInt::operator * (unsigned int mul) const {
    BigInt result("", real_size_ + 1);
    unsigned int add_mul = 0, cur;
    for (size_t i = 0; i < real_size_; i++) {
        cur = number_[i] * mul + add_mul;
        if (cur > 10) {
            result.number_[i] = cur % 10;
            add_mul = cur / 10;
        } else {
            result.number_[i] = cur;
            add_mul = 0;
        }
    }
    if (add_mul) {
        result.number_[result.real_size_ - 1] = add_mul;
    }
    return result;
}

BigInt BigInt::operator - () const {
    if (real_size_ == 1 && number_[0] == 0)
        return *this;
    BigInt result( * this);
    result.sign_ = !result.sign_;
    return result;
}

bool BigInt::operator == (const BigInt & other) const {

    if (real_size_ != other.real_size_ || sign_ != other.sign_) {
        return false;
    }
    for (size_t i = 0; i < real_size_; i++)
        if (number_[i] != other.number_[i]) {
            return false;
        }
    return true;
}

bool BigInt::operator != (const BigInt & other) const {
    return !( * this == other);
}

bool BigInt::operator > (const BigInt & other) const {
    if (sign_ > other.sign_) {
        return true;
    } else if (sign_ < other.sign_) {
        return false;
    }
    if ((sign_ && real_size_ > other.real_size_) || (!sign_ && real_size_ < other.real_size_)) {
        return true;
    }
    if ((sign_ && real_size_ < other.real_size_) || (!sign_ && real_size_ > other.real_size_)) {
        return false;
    }
    for (size_t i = 0; i < real_size_; i++) {
        if (number_[real_size_ - 1 - i] > other.number_[real_size_ - 1 - i]) {
            if (sign_) {
                return true;
            } else {
                return false;
            }
        } else if (number_[real_size_ - 1 - i] < other.number_[real_size_ - 1 - i]) {
            if (sign_) {
                return false;
            } else {
                return true;
            }
        }
    }
    return false;
}

bool BigInt::operator < (const BigInt & other) const {
    if (sign_ < other.sign_) {
        return true;
    } else if (sign_ > other.sign_) {
        return false;
    }
    if ((sign_ && real_size_ < other.real_size_) || (!sign_ && real_size_ > other.real_size_))
        return true;
    if ((sign_ && real_size_ > other.real_size_) || (!sign_ && real_size_ < other.real_size_))
        return false;
    for (size_t i = 0; i < real_size_; i++) {
        if (number_[real_size_ - 1 - i] < other.number_[real_size_ - 1 - i]) {
            if (sign_) {
                return true;
            } else {
                return false;
            }
        } else if (number_[real_size_ - 1 - i] > other.number_[real_size_ - 1 - i]) {
            if (sign_) {
                return false;
            } else {
                return true;
            }
        }
    }
    return false;
}

bool BigInt::operator >= (const BigInt & other) const {
    return (( * this > other) || ( * this == other));
}

bool BigInt::operator <= (const BigInt & other) const {
    return (( * this < other) || ( * this == other));
}

BigInt::BigInt(const BigInt & copied, size_t real_size) {
    size_t need_size = copied.size_;
    if (real_size > copied.size_) {
        need_size *= 2;
    }
    unsigned int * data = new unsigned int[need_size];
    real_size_ = std::max(copied.real_size_, real_size);
    size_ = need_size;
    sign_ = copied.sign_;
    if (number_) {
        delete[] number_;
    }
    number_ = data;
    for (size_t i = 0; i < copied.real_size_; i++)
        number_[i] = copied.number_[i];
}

BigInt & BigInt::operator = (const BigInt & copied) {
    if (this == & copied)
        return *this;
    unsigned int * data = new unsigned int[copied.size_];
    real_size_ = copied.real_size_;
    size_ = copied.size_;
    sign_ = copied.sign_;
    delete[] number_;
    number_ = data;
    for (size_t i = 0; i < real_size_; i++)
        number_[i] = copied.number_[i];
    return *this;
}

BigInt::BigInt(BigInt && moved): size_(moved.size_),
    real_size_(moved.real_size_), sign_(moved.sign_) {
        number_ = moved.number_;
        moved.number_ = nullptr;
        moved.size_ = 0;
        moved.real_size_ = 0;
        moved.sign_ = true;
    }

BigInt & BigInt::operator = (BigInt && moved) {
    if (this == & moved)
        return *this;
    size_ = std::move(moved.size_);
    real_size_ = std::move(moved.real_size_);
    sign_ = std::move(moved.sign_);
    delete[] number_;
    number_ = moved.number_;
    moved.number_ = nullptr;
    moved.size_ = 0;
    moved.real_size_ = 0;
    moved.sign_ = true;
    return *this;
}

BigInt::~BigInt() {
    if (number_ != nullptr) {
        delete[] number_;
    }
    size_ = 0;
    real_size_ = 0;
    sign_ = true;
}