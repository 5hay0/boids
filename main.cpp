#include "src/Vec2.hpp"
#include <iostream>

int main(){
    Vec2<int> v(5,4);

    Vec2<int> v1(6,6);

    v *= 4;
    v << std::cout << std::endl;
    

    std::cout << "Done" << std::endl;
    return 0;
}