#include <iostream>
#include <stdexcept>
#include <cmath>
#include "Quadtree.hpp"
#include "illegal_exception.hpp"
#include "Node.hpp"
#include "Leaf.hpp"

int main(){

    std::string input;
    int N = 0;             // number of points
    int m;             // max number of points before expansion
    double x0;
    double y0;
    double x1;
    double y1;
    double x;
    double y;
    double d;
    double xr0;
    double yr0;
    double xr1;
    double yr1;
    Quadtree *tree = nullptr;
    double close_x;
    double close_y;
    double d1 = INFINITY;

    while (std::cin >> input){

        if (input == "INIT"){

            std::cin >> m >> x0 >> y0 >> x1 >> y1;

            try {
                if (x0 >= x1 || y0 >= y1){
                    throw illegal_exception();
                } else {
                    tree = new Quadtree(m, x0, y0, x1, y1);
                    std::cout << "success" << std::endl;
                }
            } catch (illegal_exception& e){
                std::cout << e.what() << std::endl;
            }
            
        } else if (input == "INSERT"){

            std::cin >> x >> y;
            if (x < x0 || x > x1 || y < y0 || y > y1){ // make sure the point is in bounds
                std::cout << "failure" << std::endl;
            } else if (tree->insert(x, y, tree->get_root())){
                N++; // number of points counter
                std::cout << "success" << std::endl;
            } else {
                std::cout << "failure" << std::endl;
            }
            
        } else if (input == "SEARCH"){

            std::cin >> x >> y >> d;

            if (N == 0){   // if there are no points in the tree
                std::cout << "no point exists" << std::endl;
            } else {
                if (tree->search(x, y, d, tree->get_root())){
                std::cout << "point exists" << std::endl;
            } else {
                std::cout << "no point exists" << std::endl;
            }
            }
        
        } else if (input == "NEAREST"){

            std::cin >> x >> y;
            if (N == 0){      // if there are no points in the tree
                std::cout << "no point exists" << std::endl;
            } else {
                tree->nearest(x, y, tree->get_root(), close_x, close_y, d1);
                std::cout << close_x << " " << close_y << std::endl;
                d1 = INFINITY;
            }

        } else if (input == "RANGE"){

            std::cin >> xr0 >> yr0 >> xr1 >> yr1;

            try{
                if (xr0 < xr1 && yr0 < yr1){
                    if (tree->range(xr0, yr0, xr1, yr1, tree->get_root())){
                        tree->set_found(false);
                        std::cout << std::endl;
                    } else {
                        std::cout << "no points within range" << std::endl;
                    }
                } else {
                    throw illegal_exception();                 
                }
            } catch (illegal_exception& e){
                std::cout <<e.what()<< std::endl;
            }
            
        } else if (input == "NUM"){
            std::cout << N << std::endl;
            
        } else if (input == "EXIT"){
            if (tree != nullptr){
                delete tree;
            }
            return 0;
        }
    }
}