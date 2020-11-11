#pragma once

enum class Error {
    NoError,
    CorruptedArchive
};

class Serializer {
    static constexpr char Separator = ' ';
    std::ostream & out_;
private:
    template < class ArgsT >
        Error process(ArgsT && val);
    template < class T, class...ArgsT >
        Error process(T && val, ArgsT && ...args);
    Error process_saving(uint64_t val);
    Error process_saving(bool val);
public:
    explicit Serializer(std::ostream & out);
    template < class T >
        Error save(T & object);
    template < class...ArgsT >
        Error operator()(ArgsT && ...args);
};

class Deserializer {
    static constexpr char Separator = ' ';
    std::istream & in_;
private:
    template < class ArgsT >
        Error process(ArgsT && val);
    template < class T, class...ArgsT >
        Error process(T && val, ArgsT && ...args);
    Error process_loading(uint64_t & val);
    Error process_loading(bool & val);
public:
    explicit Deserializer(std::istream & in );
    template < class T >
        Error load(T & object);
    template < class...ArgsT >
        Error operator()(ArgsT && ...args);
};

#include "Serializer.tpp"