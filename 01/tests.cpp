#include "Allocator.h"
#include <cassert>
#include <iostream>


void TestBaseFunction()
{
    Allocator test_allocator = Allocator();
    char *mymemory;
    test_allocator.makeAllocator(50000);
    assert(test_allocator.alloc(10000) != nullptr);
    test_allocator.reset();
    return;
}


void ErrorCase_1()
{
    Allocator test_allocator = Allocator();
    char *mymemory;
    test_allocator.makeAllocator(1000);
    mymemory = test_allocator.alloc(500);
    assert(mymemory != nullptr);
    mymemory = test_allocator.alloc(300);
    assert(mymemory != nullptr);
    mymemory = test_allocator.alloc(100);
    assert(mymemory != nullptr);
    mymemory = test_allocator.alloc(200);
    assert(mymemory == nullptr);
    mymemory = test_allocator.alloc(100);
    assert(mymemory != nullptr);
    return;
}


void ErrorCase_2()
{
    Allocator test_allocator = Allocator();
    char *mymemory;
    mymemory = test_allocator.alloc(100);
    assert(mymemory == nullptr);
    return;
}


void ErrorCase_3()
{
    Allocator test_allocator = Allocator();
    char *mymemory;
    test_allocator.makeAllocator(1000);
    mymemory = test_allocator.alloc(1001);
    assert(mymemory == nullptr);
    mymemory = test_allocator.alloc(1000);
    assert(mymemory != nullptr);
    mymemory = test_allocator.alloc(1);
    assert(mymemory == nullptr);
    test_allocator.reset();
    test_allocator.makeAllocator(1);
    mymemory = test_allocator.alloc(1);
    assert(mymemory != nullptr);
    return;
}


int main(void)
{
    TestBaseFunction();
    ErrorCase_1();
    ErrorCase_2();
    ErrorCase_3();
    std::cout << "Success!\n";
    return 0;
}
