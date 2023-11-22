#ifndef LEAF_HPP
#define LEAF_HPP

// This class is created for consistency and organization of each node in the quadtree.

/*
CITATION: 
This was explained to me by SHIJIE XU to demonstrate how to keep the nodes organized */

class Leaf
{
private:
    double x;
    double y;
    
public:
    Leaf(double x, double y);
    Leaf();  // default constructor
    ~Leaf();
    
    double get_x();
    double get_y();
    void set_x(double x);
    void set_y(double y);
};

#endif
