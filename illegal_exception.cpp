#include <iostream>
#include <stdexcept>
#include "illegal_exception.hpp"

std::string illegal_exception::what() 
{
    return "illegal argument";
}