#include <exception>

#include <string>

#pragma once

template < class...ArgsT >
    std::string format(const std::string & str_, const ArgsT & ...args);

template < class T, class...ArgsT >
    std::string search_elem(size_t search_pos, const T & val, const ArgsT & ...args);

template < class T >
    std::string search_elem(size_t search_pos, const T & val);

class TooFewArguments: public std::exception {};

class IncorrectBracketSequence: public std::exception {
    size_t pos_;
    public:
        IncorrectBracketSequence(size_t pos): pos_(pos) {};
    size_t GetPos() {
        return pos_;
    }
};

#include "Format.tpp"