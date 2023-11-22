#include <iostream>
#include "Leaf.hpp"

Leaf::Leaf(double x, double y)
{
    this->x = x;
    this->y = y;
}

Leaf::Leaf() // default constructor
{
}

Leaf::~Leaf()
{
}

double Leaf::get_x(){
    return x;
}

double Leaf::get_y(){
    return y;
}

void Leaf::set_x(double x){
    this->x = x;
}

void Leaf::set_y(double y){
    this->y = y;
}