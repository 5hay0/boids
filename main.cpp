#include "src/Vec2.hpp"
#include "src/Boid.hpp"

int main(){
    Vec2<unit> v(5,4);
    Vec2<unit> dir(1,1);

    Boid b = Boid(v, dir, 1, 4, 5);
    b.getPos() << std::cout << std::endl;
    b.update();

    std::cout << "After update" << std::endl;
    b.getPos() << std::cout << std::endl;
    b.getDir() << std::cout << std::endl;
    std::cout << b.getSpeed() << std::endl;
    std::cout << b.getSpeedMax() << std::endl;
    std::cout << b.getR() << std::endl;
    
    std::cout << "Done" << std::endl;
    return 0;
}