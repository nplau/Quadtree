#ifndef ILLEGAL_EXCEPTION_HPP
#define ILLEGAL_EXCEPTION_HPP

#include <iostream>
#include <stdexcept>


class illegal_exception : public std::exception
{
public:
    std::string what();
};

#endif