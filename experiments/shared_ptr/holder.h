#pragma once

#include <memory>
#include <iostream>

class Class;

class Holder
{
    std::shared_ptr<Class> pointer;

public:
    Holder() = default;
    void Attach(Class && cl)
    {
        pointer = std::make_shared<Class>(std::move(cl));
    }
};

class Class
{
    int a = 0;
    int b = 0;
    int c = 0;
    int d = 0;
    int e = 0;
    int f = 0;
public:

    Class() { a = 1; }
    Class(Class const & cl) { b=1; }
    Class(Class && cl) { c=1; }
    Class& operator=(Class && cl) {d = 1;}
    Class& operator= (Class const & cl) {e = 1;};

    ~Class()
    {
        std::cout << a << ' ' << b << ' ' << c << ' ' << d << ' ' << e << ' ' << f << std::endl;
    }
};