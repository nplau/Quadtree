#ifndef NODE_HPP
#define NODE_HPP

#include "Leaf.hpp"

class Node
{
private:
    int m;
    int x0;
    int y0;
    int x1;
    int y1;

    Leaf *stack; // array of points in the node
    int top_index;
    Node **child; // child nodes of the array


public:
    Node(int m, double x0, double y0, double x1, double y1);
    ~Node();
    
    void make_child();  
    bool isLeaf(Node* node);

    bool push(double x, double y);
    bool is_full();

    int get_top_index();
    double get_x0();
    double get_y0();
    double get_x1();
    double get_y1();

    Leaf get_stack(int j);
    Node* get_child(int i);
};

#endif
