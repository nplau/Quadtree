#ifndef QUADTREE_HPP
#define QUADTREE_HPP

#include "illegal_exception.hpp"
#include "Node.hpp"
#include "Leaf.hpp"

class Quadtree
{
private:

    Node *root; 
    bool found;

public:
    Quadtree(int m, double x0, double y0, double x1, double y1);
    ~Quadtree();

    bool insert (double x, double y, Node* node);
    bool search (double x, double y, double d, Node* node);
    void nearest (double x, double y, Node* node, double& close_x, double& close_y, double& d1);
    bool range (double xr0, double yr0, double xr1, double yr1, Node* node);
    Node* get_root();
    void set_found(bool found);

};

#endif