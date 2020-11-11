#include <cassert>

#include <sstream>

#include "Serializer.h"

struct Data {
    uint64_t a;
    bool b;
    uint64_t c;

    template < class Serializer >
        Error serialize(Serializer & serializer) {
            return serializer(a, b, c);
        }

    template < class Deserializer >
        Error deserialize(Deserializer & deserializer) {
            return deserializer(a, b, c);
        }
};

void DefaultTest() {
    Data x {
        1,
        true,
        2
    };
    std::stringstream stream;
    Serializer serializer(stream);
    serializer.save(x);
    Data y {
        0,
        false,
        0
    };
    Deserializer deserializer(stream);
    const Error err = deserializer.load(y);
    assert(err == Error::NoError);
    assert(x.a == y.a);
    assert(x.b == y.b);
    assert(x.c == y.c);
    return;
}

void ErrorTest() {
    Data x {
        5,
        false,
        'o'
    };
    std::stringstream stream;
    Deserializer deserializer(stream);
    const Error err = deserializer.load(x);
    assert(err == Error::CorruptedArchive);
    return;
}

int main(void) {
    DefaultTest();
    ErrorTest();
    std::cout << "Success!\n";
    return 0;
}