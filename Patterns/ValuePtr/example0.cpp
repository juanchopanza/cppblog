#include <iostream>
#include "value_ptr.hpp"

struct foo
{
    foo() { std::cout << "foo()\n"; }
    foo(const foo&) { std::cout << "foo(const foo&)\n"; }
    foo& operator=(const foo&) { 
        std::cout << "foo& operator=(const foo&)\n";
        return *this;
    }
    virtual void hello() const { std::cout << "hello from foo\n"; }
    virtual ~foo() { std::cout << "~foo()\n"; }
    virtual foo* clone() { return new foo(*this); }
};

struct bar : foo
{
    bar() { std::cout << "bar()\n"; }
    bar(const bar& b) : foo(b) { std::cout << "bar(const bar&)\n"; }
    bar& operator=(const bar&) { 
        std::cout << "bar& operator=(const bar&)\n";
        return *this;
    }
    virtual void hello() const { std::cout << "hello from bar\n"; }
    virtual ~bar() { std::cout << "~bar()\n"; }
    virtual foo* clone() { return new bar(*this); }
};

int main()
{
    value_ptr<foo> a(new foo);
    value_ptr<foo> b(new bar);

    a->hello();
    b->hello();

    std::cout << "assigning b to a\n";
    a = b;
    std::cout << "assigned b to a\n";
    a->hello();
    b->hello();

}
