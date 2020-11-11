#include <iostream>


#include <string>


Serializer::Serializer(std::ostream & out): out_(out) {}

template < class ArgsT >
    Error Serializer::process(ArgsT && val) {
        return process_saving(val);
    }

template < class T, class...ArgsT >
    Error Serializer::process(T && val, ArgsT && ...args) {
        const Error er = process_saving(val);
        if (er == Error::NoError) {
            return process(std::forward < ArgsT > (args)...);
        } else {
            return er;
        }
    }

Error Serializer::process_saving(uint64_t val) {
    out_ << val << Separator;
    if (out_.fail()) {
        return Error::CorruptedArchive;
    }
    return Error::NoError;
}

Error Serializer::process_saving(bool val) {
    if (val) {
        out_ << "true" << Separator;
    } else {
        out_ << "false" << Separator;
    }
    if (out_.fail()) {
        return Error::CorruptedArchive;
    }
    return Error::NoError;
}

template < class T >
    Error Serializer::save(T & object) {
        return object.serialize( * this);
    }

template < class...ArgsT >
    Error Serializer::operator()(ArgsT && ...args) {
        return process(std::forward < ArgsT > (args)...);
    }

Deserializer::Deserializer(std::istream & in ): in_( in ) {}

template < class ArgsT >
    Error Deserializer::process(ArgsT && val) {
        return process_loading(val);
    }

template < class T, class...ArgsT >
    Error Deserializer::process(T && val, ArgsT && ...args) {
        const Error er = process_loading(val);
        if (er == Error::NoError) {
            return process(std::forward < ArgsT > (args)...);
        } else {
            return er;
        }
    }

Error Deserializer::process_loading(uint64_t & val) {
    std::string text;
    in_ >> text;
    try {
        val = std::stoull(text);
    } catch (const std::invalid_argument & exp) {
        return Error::CorruptedArchive;
    }
    return Error::NoError;
}

Error Deserializer::process_loading(bool & val) {
    std::string text;
    in_ >> text;
    if (text == "true")
        val = true;
    else if (text == "false")
        val = false;
    else
        return Error::CorruptedArchive;
    return Error::NoError;
}

template < class T >
    Error Deserializer::load(T & object) {
        return object.deserialize( * this);
    }

template < class...ArgsT >
    Error Deserializer::operator()(ArgsT && ...args) {
        return process(args...);
    }
