#include "src/Boid.hpp"

int main(){
    Vec2<unit> v(5,4);

    Boid b = Boid(v, v, 1, 4, 5);
    b.update();
    
    std::cout << "Done" << std::endl;
    return 0;
}