#include <string>

#include <iostream>

#include <cctype>

#include "TestFunc.h"


std::string Start_test() {
    std::string res = "Extraordinary Start parsing\r";
    return res;
}

std::string Finish_test() {
    std::string res = "Extraordinary Finish parsing\r";
    return res;

}

std::string WordParser_test(const std::string & str) {

    std::string res = "doubleword = " + str + str + "\r";
    return res;
}

std::string DigitParser_test(int digit) {
    std::string res = "Word ** 2 = " + std::to_string(digit * digit) + "\r";
    return res;
}