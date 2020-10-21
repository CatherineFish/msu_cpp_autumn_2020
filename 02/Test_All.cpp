#include "TokenParser.h"
#include "TestFunc.h"
#include "DefaultFunc.h"
#include <cassert>
#include <string>
#include <iostream>


void Default()
{
    TokenParser MyParser;
    std::string input = "Word \r Number HI \t 567 78\n";
    std::string test_output = MyParser.InputParser(input);
    std::string res_output = "Start parsing\rParsered word is Word\rParsered word is Number\rParsered word is HI\r"
        "Parsered number is 567\rParsered number is 78\rFinish parsing\r";
    assert(test_output == res_output);
    return;
}


void Test()
{
    TokenParser MyParser;
    MyParser.SetStartCallback(Start_test);
    MyParser.SetFinishCallback(Finish_test);
    MyParser.SetWordTokenCallback(WordParser_test);
    MyParser.SetDigitTokenCallback(DigitParser_test);
    std::string input = "word \r number HI \t 4 15\n";
    std::string test_output = MyParser.InputParser(input);
    std::string res_output = "Extraordinary Start parsing\rdoubleword = wordword\rdoubleword = numbernumber\rdoubleword = HIHI\r"
        "Word ** 2 = 16\rWord ** 2 = 225\rExtraordinary Finish parsing\r";
    assert(test_output == res_output);
    return;
}


void Defolt_And_Test()
{
    TokenParser MyParser;
    MyParser.SetStartCallback(Start_test);
    MyParser.SetFinishCallback(Finish_test);
    MyParser.SetWordTokenCallback(WordParser_test);
    MyParser.SetDigitTokenCallback(DigitParser_test);
    MyParser.SetStartCallback(Start_default);
    MyParser.SetWordTokenCallback(WordParser_default);
    std::string input = "word \r number HI \t 4 15\n";
    std::string test_output = MyParser.InputParser(input);
    std::string res_output = "Start parsing\rParsered word is word\rParsered word is number\rParsered word is HI\r"
        "Word ** 2 = 16\rWord ** 2 = 225\rExtraordinary Finish parsing\r";
    assert(test_output == res_output);
    return;
}



int main(void)
{
	//Default();
    Test();
    Defolt_And_Test();
    std::cout << "Success!\n";
	return 0;
}