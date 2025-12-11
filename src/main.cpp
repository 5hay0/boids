#include "../include/Rule.hpp"

int main(){
    Vec2<unit> v(5,4);
    Vec2<unit> dir(1,1);

    bd::Boid b = bd::Boid(v, dir, 1, 4, 5);
    bd::Flock f = bd::Flock();
    std::cout << f.getBoids().getSize() << std::endl;
    f.addBoid(b);
    std::cout << f.getBoids().getSize() << std::endl;

    bd::Cohesion c = bd::Cohesion();
    bd::Alignment a = bd::Alignment();
    bd::Separation s = bd::Separation();
    c.apply(b,f);
    a.apply(b,f);
    s.apply(b,f);
    return 0;
}