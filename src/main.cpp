#include "../include/Rule.hpp"

int main(){
    Vec2<unit> v(5,4);
    Vec2<unit> dir(1,1);

    Boid b = Boid(v, dir, 1, 4, 5);
    Flock f = Flock();
    std::cout << f.getBoids().getSize() << std::endl;
    f.addBoid(b);
    std::cout << f.getBoids().getSize() << std::endl;

    Cohesion c = Cohesion();
    Alignment a = Alignment();
    Separation s = Separation();
    c.apply(b,f);
    a.apply(b,f);
    s.apply(b,f);
    return 0;
}