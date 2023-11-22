#include <iostream>
#include <cmath>
#include "Node.hpp"
#include "Leaf.hpp"


Node::Node(int m, double x0, double y0, double x1, double y1)
{
    this->m = m;
    this->x0 = x0;
    this->y0 = y0;
    this->x1 = x1;
    this->y1 = y1; 

    stack = new Leaf[m];
    top_index = 0;
    child = new Node*[4] {nullptr, nullptr, nullptr, nullptr};

    for (int i = 0; i < m; i++){
        stack[i] = Leaf(0, 0);
    }

}

Node::~Node()
{
    
    for (int i = 0; i < 4; ++i) {
        if (child[i] != nullptr){
            delete child[i];
            child[i] = nullptr;
        }
    }
    delete[] child;
    delete[] stack;

}

void Node::make_child(){ // O(D) time
    
    // calculate midpoints
    double mid_x = x0 + (x1 - x0) / 2;
    double mid_y = y0 + (y1 - y0) / 2;

    // create 4 new nodes
    child[0] = new Node (m, x0, mid_y, mid_x, y1);
    child[1] = new Node(m, mid_x, mid_y, x1, y1);
    child[2] = new Node (m, x0, y0, mid_x, mid_y); 
    child[3] = new Node (m, mid_x, y0, x1, mid_y);
   

    // for each point in the array, check if it is in the nw, ne, sw, or se node and insert it into it
    for (int i = 0; i < top_index; i++) {
        if (&stack[i] != nullptr){
            if (child[0] != nullptr && stack[i].get_x() <= mid_x && stack[i].get_y() >= mid_y) {
                child[0]->push(stack[i].get_x(), stack[i].get_y());
            } else if (child[1] != nullptr && stack[i].get_x() > mid_x && stack[i].get_y() >= mid_y) {
                child[1]->push(stack[i].get_x(), stack[i].get_y());
            } else if (child[2] != nullptr && stack[i].get_x() <= mid_x && stack[i].get_y() < mid_y) {
                child[2]->push(stack[i].get_x(), stack[i].get_y());
            } else if (child[3] != nullptr && stack[i].get_x() > mid_x && stack[i].get_y() < mid_y) {
                child[3]->push(stack[i].get_x(), stack[i].get_y());
            }
        }
    }

    delete[] stack;
    stack = nullptr;
    top_index = 0;
}

bool Node::isLeaf(Node* node){
    if (node -> child[0] == nullptr && node -> child[1] == nullptr && node -> child[2] == nullptr && node-> child[3] == nullptr){
        return true;
    } else {
        return false;
    }
}

bool Node::push(double x, double y){
    // adding a new element to the top of the stack
    // if the stack is empty, set the top to the leaf
    // if the stack is not empty, set the leaf to the top and set the top to the leaf

    // check if the point is already in the stack
    for (int i = 0; i < top_index; i++){
        if (stack[i].get_x() == x && stack[i].get_y() == y){
            return false;
        }
    }

    stack[top_index].set_x(x);
    stack[top_index].set_y(y);
    top_index++; // increment the top index
    return true;
}

bool Node::is_full(){
    // if the stack is full, return true
    // if the stack is not full, return false
    if (top_index == m) {
        return true;
    } else {
        return false;
    }
}

int Node::get_top_index(){
    return top_index;
}

double Node::get_x0(){
    return x0;
}

double Node::get_y0(){
    return y0;
}   

double Node::get_x1(){
    return x1;
}

double Node::get_y1(){
    return y1;
}

Leaf Node::get_stack(int j){
    return stack[j];
}

Node* Node::get_child(int i){
    return child[i];
}




