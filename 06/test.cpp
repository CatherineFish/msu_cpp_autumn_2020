#include <cassert>

#include <iostream>

#include "Format.h"


void DefaultTest(void) {
    auto text = format("{1}+{1} = {0}", 2, "one");
    assert(text == "one+one = 2");
    std::cout << "Test 1:" << std::endl << text << std::endl;

    auto text_2 = format("{0} just text {1} one more text {2} text too", "my_text", 67, 90.2);
    assert(text_2 == "my_text just text 67 one more text 90.2 text too");
    std::cout << "Test 2:" << std::endl << text_2 << std::endl;

    auto text_3 = format("Hi! My name is {0}. I'm {2} years old. It's windy today? {1} {3} ", "Kate", true, 20, "blablabla");
    assert(text_3 == "Hi! My name is Kate. I'm 20 years old. It's windy today? 1 blablabla ");
    std::cout << "Test 3:" << std::endl << text_3 << std::endl;
    return;
}

void ErrorTest(void) {
    try {
        auto text = format("{not_number}+{1} = {0}", 2, "one");
    } catch (IncorrectBracketSequence & error) {
        assert(error.GetPos() == 0);
    }

    try {
        auto text = format("{1}+{+{1} = {0}", 2, "one");
    } catch (IncorrectBracketSequence & error) {
        assert(error.GetPos() == 4);
    }

    try {
        auto text = format("{1}+{0}+{1}} *text {0}", 2, "one");
    } catch (IncorrectBracketSequence & error) {
        assert(error.GetPos() == 11);
    }

    int TooFewArguments_error_count = 0;
    try {
        auto text = format("{1}+{1} = {0}", 2);
    } catch (TooFewArguments & error) {
        TooFewArguments_error_count++;
    }
    assert(TooFewArguments_error_count == 1);
    return;
}

int main(void) {
    DefaultTest();
    ErrorTest();
    std::cout << "Success!\n";
    return 0;
}