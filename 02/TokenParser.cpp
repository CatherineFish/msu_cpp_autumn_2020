#include "TokenParser.h"

#include <string>

#include <cctype>


TokenParser::TokenParser(const StartAndFinish_Func & StartCallback,
    const StartAndFinish_Func & FinishCallback,
        const WordParser_Func & WordParser,
            const DigitParser_Func & DigitParser): StartCallback(StartCallback), FinishCallback(FinishCallback), WordParser(WordParser), DigitParser(DigitParser) {}

void TokenParser::SetStartCallback(const StartAndFinish_Func & function) {
    StartCallback = function;
}

void TokenParser::SetFinishCallback(const StartAndFinish_Func & function) {
    FinishCallback = function;
}

void TokenParser::SetWordTokenCallback(const WordParser_Func & function) {
    WordParser = function;
}

void TokenParser::SetDigitTokenCallback(const DigitParser_Func & function) {
    DigitParser = function;
}

std::string TokenParser::GetToken(const std::string & token, bool flag) {
    if (token != "") {
        if (flag)
            return DigitParser(std::stoi(token));
        else
            return WordParser(token);
    }
    return token;
}

std::string TokenParser::InputParser(const std::string & input) {
    std::string token = "";
    bool IsDigit = true;
    std::string for_output = StartCallback();
    for (const auto & ch: input) {
        if (!std::isspace(ch)) {
            token += ch;
            if (!std::isdigit(static_cast < unsigned char > (ch))) {
                IsDigit = false;
            }

        } else {
            for_output += GetToken(token, IsDigit);
            token = "";
            IsDigit = true;
        }
    }
    for_output += GetToken(token, IsDigit);
    for_output += FinishCallback();
    return for_output;
}