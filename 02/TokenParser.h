#include <functional>

#include <string>

#include "DefaultFunc.h"

#pragma once

using StartAndFinish_Func = std:: function < std::string() > ;
using WordParser_Func = std:: function < std::string(const std::string & ) > ;
using DigitParser_Func = std:: function < std::string(int) > ;

class TokenParser {
    StartAndFinish_Func StartCallback;
    StartAndFinish_Func FinishCallback;
    WordParser_Func WordParser;
    DigitParser_Func DigitParser;
    public:
        TokenParser(const StartAndFinish_Func & StartCallback = Start_default,
            const StartAndFinish_Func & FinishCallback = Finish_default,
                const WordParser_Func & WordParser = WordParser_default,
                    const DigitParser_Func & DigitParser = DigitParser_default);
    void SetStartCallback(const StartAndFinish_Func & function);
    void SetFinishCallback(const StartAndFinish_Func & function);
    void SetWordTokenCallback(const WordParser_Func & function);
    void SetDigitTokenCallback(const DigitParser_Func & function);
    std::string InputParser(const std::string & input);
    std::string GetToken(const std::string & token, bool flag);
};