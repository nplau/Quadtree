#include <iostream>
#include <cmath>
#include <string>
#include "illegal_exception.hpp"
#include "Quadtree.hpp"
#include "Node.hpp"
#include "Leaf.hpp"

Quadtree::Quadtree(int m, double x0, double y0, double x1, double y1)
{
    root = new Node(m, x0, y0, x1, y1); // creating a root node once the quadtree is initialized
    found = false;
}

Quadtree::~Quadtree()
{
    delete root;
}

bool Quadtree::insert (double x, double y, Node* node){ // O(D) time
    // inserts a point into the quadtree
    // if the point is on a vertical boundary, it is inserted into the left subtree (node 1 or 3)
    // if the point is on a horizontal boundary, it is inserted into the top subtree (node 1 or 2)
    // if the point is at an intersection, it is inserted into the top left subtree (node 1) 
    
    if (node == nullptr){
        return false;
    }

    // calculate midpoints
        double mid_x = node->get_x0() + (node->get_x1() - node->get_x0()) / 2;
        double mid_y = node->get_y0() + (node->get_y1() - node->get_y0()) / 2;

    // if the point is inserted, return true
    if (node->isLeaf(node)){

        // check if the point is already in the tree
        for (int i = 0; i < node->get_top_index(); i++){
            if (node->get_stack(i).get_x() == x && node->get_stack(i).get_y() == y){
                return false;
            }
        }

        if (node->is_full()){
            // make 4 new nodes and enter the new point
            node -> make_child();
            // insert the new point into the correct child node
            if (x <= mid_x && y >= mid_y) {
                return insert(x, y, node->get_child(0));
            } else if (x > mid_x && y >= mid_y) {
                return insert(x, y, node->get_child(1));
            } else if (x <= mid_x && y < mid_y) {
                return insert(x, y, node->get_child(2));
            } else if (x > mid_x && y < mid_y) {
                return insert(x, y, node->get_child(3));
            }
        } else {
            // insert the point into the node
            //Leaf* new_leaf = new Leaf(x, y);
            bool inserted = node -> push(x,y);

            // if (!inserted){  // if the node is not inserted into the node, delete it
            //     delete new_leaf;
            // }

            return inserted;

        }
    } else {
        // calculate midpoints
        double mid_x = node->get_x0() + (node->get_x1() - node->get_x0()) / 2;
        double mid_y = node->get_y0() + (node->get_y1() - node->get_y0()) / 2;

        // insert the new point into the correct child node
        if (x <= mid_x && y >= mid_y) {
            return insert(x, y, node->get_child(0));
        } else if (x > mid_x && y >= mid_y) {
            return insert(x, y, node->get_child(1));
        } else if (x <= mid_x && y < mid_y) {
            return insert(x, y, node->get_child(2));
        } else if (x > mid_x && y < mid_y) {
            return insert(x, y, node->get_child(3));
        }
    }
    return false;
}

bool Quadtree::search (double x, double y, double d, Node* node){
    // is there at least one point within d of (x,y)

    // make sure that the radius is within a singular leaf node
    // traverse down into the leaf node at which (x,y) is located
    // then check x-d, x+d, y-d, y+d to see if the radius in within the leaf node
    
    double xr0 = x - d;
    double yr0 = y - d;
    double xr1 = x + d;
    double yr1 = y + d;

    // so we do not go into nodes where the range is not within that node
    if (xr1 <= node -> get_x0() || xr0 >= node -> get_x1() || yr1 <= node -> get_y0() || yr0 >= node -> get_y1()){
        return false;
    }

    if (node -> isLeaf(node)){
        // check if the point is within the range
        for (int i = 0; i < node -> get_top_index(); i++){
                double x1 = node -> get_stack(i).get_x();
                double y1 = node -> get_stack(i).get_y();

                if (d > sqrt(pow(((x1 - x)), 2) + pow((y1 - y), 2))){
                    return true;
                }
        }

    } else {
        // recursively call range on each child node
        for (int i = 0; i < 4; i++){ // for each child node
            if (node -> get_child(i) != nullptr){
                if (search(x, y, d, node -> get_child(i))){
                    return true;
                }
            }
        }
    }

    return false;
}

void Quadtree::nearest (double x, double y, Node* node, double& close_x, double& close_y, double& d1){
    // find the nearest point to (x,y)
    // if there are multiple that are closest, return the one with the largest x value, and if there are multiple with the same x value, return the one with the largest y value
    // if there are no points in the tree, return "no points exist"
    // if there are points in the tree, return the point in the format x y (no parentheses)

    if (node -> isLeaf(node)){
        // check if the point is within the range
        for (int i = 0; i < node -> get_top_index(); i++){
                double distance = sqrt(pow(((node -> get_stack(i).get_x() - x)), 2) + pow((node -> get_stack(i).get_y() - y), 2)); // pythagorean theorem
               
                if (distance < d1){       // if this point is closer, replace it with the closest point
                    close_x = node -> get_stack(i).get_x();
                    close_y = node -> get_stack(i).get_y();
                    d1 = distance;
                } else if (distance == d1){   // if this point is equadistant, check the x and y values
                    if (node -> get_stack(i).get_x() > x){
                        close_x = node -> get_stack(i).get_x();
                        close_y = node -> get_stack(i).get_y();
                    } else if (node -> get_stack(i).get_x() == x){
                        if (node -> get_stack(i).get_y() > y){
                            close_x = node -> get_stack(i).get_x();
                            close_y = node -> get_stack(i).get_y();
                        }
                    }
                }
            }

    } else {
        // recursively call range on each child node
        for (int i = 0; i < 4; i++){ // for each child node
            if (node -> get_child(i) != nullptr){
                nearest(x, y, node -> get_child(i), close_x, close_y, d1);
            }
        }
    }
}

bool Quadtree::range (double xr0, double yr0, double xr1, double yr1, Node* node){ // O(D) time 
/*
    CITATION:
    This function implementation was explained to me by Gavin Lusby
*/
    
    // check to ensure that nodes that are not within the range are not traversed
    // if the range is not within the node, return false
    if (xr1 <= node -> get_x0() || xr0 >= node -> get_x1() || yr1 <= node -> get_y0() || yr0 >= node -> get_y1()){  
        return false;
    }

    if (node -> isLeaf(node)){
        // check if the point is within the range
        for (int i = 0; i < node -> get_top_index(); i++){
            if (node -> get_stack(i).get_x() > xr0 && node -> get_stack(i).get_x() < xr1 && node -> get_stack(i).get_y() > yr0 && node -> get_stack(i).get_y() < yr1){
                std::cout << node -> get_stack(i).get_x() << " " << node -> get_stack(i).get_y() << " ";
                found = true;
            }
        }
        return found;
    } else {
        // recursively call range on each child node
        for (int i = 0; i < 4; i++){ // for each child node
            if (node -> get_child(i) != nullptr){
                bool foundChild = range(xr0, yr0, xr1, yr1, node -> get_child(i));
                found = found || foundChild;
            }
        }
    }
   return found;
}

Node* Quadtree::get_root(){
    return root;
}

void Quadtree::set_found(bool found){
    this -> found = found;
}
