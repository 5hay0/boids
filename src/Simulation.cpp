//
// Created by lison on 06/01/2026.
//

#include "../include/Simulation.hpp"

#include "../include/SaveSystem.hpp"
#include "SFML/Graphics/CircleShape.hpp"
#include "SFML/Graphics/Font.hpp"
#include "SFML/Graphics/Text.hpp"
#include <cmath>


bd::Simulation::Simulation(Settings s) {

    settings = s;

    //init rules
    cohesion = Cohesion(settings.getWC());
    separation = Separation(settings.getWS());
    alignment = Alignment(settings.getWA());
    fuite = Fuite();

    //init all flock / DynamicArray
    subjects = Flock(settings.getNbBoids(),20);
    for (int i = 0; i<settings.getNbBoids(); i++) {
        Vec2<unit> v(rand()%settings.getWidthWindow(),rand()%settings.getHeightWindow()); //génére position random dans la fenêtre
        Vec2<unit> dir(1,1);
        subjects.addBoid(Boid(v,dir,0.1,4,subjects.getDistance()));
    }
    predators = Flock();
    obstacles = DynamicArray<Vec2<unit>>();

    //Window
    sf::RenderWindow window;
}

void bd::Simulation::drawBoids() {
    constexpr unit PI = 3.14159265358979323846; //for the rotation of the boid because the variable can be undefined on Windows

    for (std::size_t i = 0; i < subjects.getBoids().getSize(); i ++){

            //apply rules
            Vec2<unit> cohestionVec = cohesion.apply(subjects.getBoids().get(i),subjects);
            Vec2<unit> alignmentVec = alignment.apply(subjects.getBoids().get(i),subjects);
            Vec2<unit> separationVec = separation.apply(subjects.getBoids().get(i),subjects);

            Vec2<unit> dir(subjects.getBoids().get(i).getDir().getX()+
                    cohestionVec.getX()+
                    alignmentVec.getX()+
                    separationVec.getX(),
                    subjects.getBoids().get(i).getDir().getY()+
                    cohestionVec.getY()+
                    alignmentVec.getY()+
                    separationVec.getY()
                    );

            Vec2<unit> runVec = fuite.apply(subjects.getBoids().get(i),predators);
            if (runVec.getX() != 0 || runVec.getY()) { //If one or more predator
                dir = runVec;
            }

            //normalisation de distance
            double len = sqrt(dir.getX()*dir.getX() + dir.getY()*dir.getY());
            if (len > 0) {
                dir = dir / len;
            }

            subjects.getBoids().get(i).setDir(dir);

        if (obstacles.getSize() != 0) {
            obstacleManagement(subjects.getBoids().get(i));
        }
            borderManagement(subjects.getBoids().get(i));

        //new speed
        if (len > subjects.getBoids().get(i).getSpeedLimit()) { //if too fast
            subjects.getBoids().get(i).setSpeed(subjects.getBoids().get(i).getSpeed()+0.1);
        }
        else {
            subjects.getBoids().get(i).setSpeed(subjects.getBoids().get(i).getSpeed()+len);
        }

        //new position

        subjects.getBoids().get(i).update();

            //modify the visual

            // create an empty shape
            sf::ConvexShape convex;

            // resize it to 3 points
            convex.setPointCount(3);

            // define the points
            convex.setPoint(0, {0.f, -10.f});
            convex.setPoint(1, {-7.f, 10.f});
            convex.setPoint(2, {+7.f, 10.f});

            convex.setFillColor(sf::Color::Green);

            // Origin at center else boid turn around a corner
            convex.setOrigin({0.f, 0.f});

            convex.setPosition({subjects.getBoids().get(i).getPos().getX(),subjects.getBoids().get(i).getPos().getY()});

            float angleDeg = std::atan2(subjects.getBoids().get(i).getDir().getY(),
                subjects.getBoids().get(i).getDir().getX()) * 180.f / PI;

            if (angleDeg<0) {
                angleDeg = angleDeg + 360.0f;
            }

            sf::Angle angle = sf::degrees(angleDeg+90.0f);
            convex.setRotation(angle);

            window.draw(convex);
            }
}

void bd::Simulation::drawPredators() {
    constexpr unit PI = 3.14159265358979323846; //for the rotation of the boid because the variable can be undefined on Windows

    for (std::size_t i = 0; i < predators.getBoids().getSize(); i ++){
                //apply rules
                Vec2<unit> cohestionVec = cohesion.apply(predators.getBoids().get(i),predators);
                Vec2<unit> alignmentVec = alignment.apply(predators.getBoids().get(i),predators);
                Vec2<unit> separationVec = separation.apply(predators.getBoids().get(i),predators);

            Vec2<unit> dir(predators.getBoids().get(i).getDir().getX()+
                    cohestionVec.getX()+
                    alignmentVec.getX()+
                    separationVec.getX(),
                    predators.getBoids().get(i).getDir().getY()+
                    cohestionVec.getY()+
                    alignmentVec.getY()+
                    separationVec.getY()
                    );

            //normalisation of distance
            double len = sqrt(dir.getX()*dir.getX() + dir.getY()*dir.getY());
            if (len > 0) {
                dir = dir / len;
            }

            predators.getBoids().get(i).setDir(dir);

        predators.getBoids().get(i).update();

        if (obstacles.getSize() != 0) {
            obstacleManagement(predators.getBoids().get(i));
        }
        borderManagement(predators.getBoids().get(i));

        //new speed
        if (len > predators.getBoids().get(i).getSpeedLimit()) { //if too fast
            predators.getBoids().get(i).setSpeed(predators.getBoids().get(i).getSpeed()+0.1);
        }
        else {
            predators.getBoids().get(i).setSpeed(predators.getBoids().get(i).getSpeed()+len);
        }

            //modify the visual

            // create an empty shape
            sf::ConvexShape convex;

            // resize it to 3 points
            convex.setPointCount(3);

            // define the points
            convex.setPoint(0, {0.f, -10.f});
            convex.setPoint(1, {-7.f, 10.f});
            convex.setPoint(2, {+7.f, 10.f});

            convex.setFillColor(sf::Color::Red);

            // Origin of center else boid turn around a corner
            convex.setOrigin({0.f, 0.f});

            convex.setPosition({predators.getBoids().get(i).getPos().getX(),predators.getBoids().get(i).getPos().getY()});

            float angleDeg = std::atan2(predators.getBoids().get(i).getDir().getY(),
                predators.getBoids().get(i).getDir().getX()) * 180.f / PI;

            if (angleDeg<0) {
                angleDeg = angleDeg + 360.0f;
            }

            sf::Angle angle = sf::degrees(angleDeg+90.0f);
            convex.setRotation(angle);

            window.draw(convex);
            }
}

void bd::Simulation::drawInstructions() {
    sf::Font font("asset/font/Roboto-Regular.ttf"); //obligatory
    sf::Text text(font);

    sf::String message = "Add Boid: LAlt + B \n";
    message.operator+=("Remove Boid: LControl + B \n");
    message.operator+=("nb Boids: "+std::to_string(subjects.getBoids().getSize())+"\n");
    //////PREDATORS//////////
    message.operator+=("Add Predator: LAlt + P \n");
    message.operator+=("Remove Predator: LControl + P \n");
    message.operator+=("nb Predators: "+std::to_string(predators.getBoids().getSize())+"\n");
    ///RULES///
    message.operator+=("Add to Cohesion: LAlt + C \n");
    message.operator+=("Remove to Cohesion: LControl + C\n");
    message.operator+=("Cohesion:"+std::to_string(cohesion.getWeight())+"\n");

    message.operator+=("Add to Separation: LAlt + S \n");
    message.operator+=("Remove to Separation: LControl + S \n");
    message.operator+=("Separation:"+std::to_string(separation.getWeight())+"\n");

    message.operator+=("Add to Alignment: LAlt + A \n");
    message.operator+=("Remove to Alignment: LControl + A \n");
    message.operator+=("Alignment:"+std::to_string(alignment.getWeight())+"\n");

    message.operator+=("Add to R: LAlt + R \n");
    message.operator+=("Remove to R: LControl + R \n");
    message.operator+=("R of Boid:"+std::to_string(subjects.getR())+"\n");

    message.operator+=("Add to distance: LAlt + D \n");
    message.operator+=("Remove to distance: LControl + D \n");
    message.operator+=("Distance between Boid:"+std::to_string(subjects.getDistance())+"\n");

    message.operator+=("Add obstacle: RClick \n");
    message.operator+=("Remove last obstacle: Echap \n");

    message.operator+=("Save: W \n");
    message.operator+=("Load: L \n");

    text.setString(message);
    text.setCharacterSize(15);

    window.draw(text);
}

void bd::Simulation::drawObstacles() {
    for (int i=0; i<obstacles.getSize();i++) {
        sf::CircleShape shape(30);
        shape.setOrigin({0.f, 0.f});
        shape.setPosition({obstacles.get(i).getX(),obstacles.get(i).getY()});
        shape.setFillColor(sf::Color::Magenta);

        window.draw(shape);
    }
}


void bd::Simulation::drawSimulation() {

    SaveSystem save_system = SaveSystem();

    unsigned width = settings.getWidthWindow();
    unsigned height = settings.getHeightWindow();
    window.create(sf::VideoMode({width,height}), "My window"); //800 by 600

    sf::View simulation = window.getDefaultView();
    simulation.setViewport({{0.0f,0.0f},{1.0f,1.0f}});

    //If key/mouse pressed
    bool addPressed = false;
    bool removePressed = false;

    bool boidPressed = false;
    bool predatorPressed = false;

    bool separationPressed = false;
    bool alignPressed = false;
    bool cohesionPressed = false;

    bool rPressed = false;
    bool distancePressed = false;

    bool obstaclePressed = false;
    bool clickPressed = false;

    bool savePressed = false;
    bool loadPressed = false;

    while (window.isOpen()) {
        // check all the window's events that were triggered since the last iteration of the loop
        while (const std::optional event = window.pollEvent())
        {
            // "close requested" event: we close the window
            if (event->is<sf::Event::Closed>()) {
                window.close();
            }
        }

        /**
         *  All if that follow were written to force creation each key/mouse pressed
         *  instead of "for each frame it was pressed" by default
         **/


        //add boid
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::LAlt) &&
            sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::B) &&
                (!addPressed || !boidPressed)){
            //last check is for avoiding adding for each frame

            Vec2<unit> v(rand()%((int)(width)),rand()%height); //generate random position in window
            Vec2<unit> dir(1,1);
            subjects.addBoid(Boid(v,dir,0.1,1,50));
                }
        //remove boid
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::LControl) &&
            sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::B)&&
            (!removePressed || !boidPressed)) {
            subjects.getBoids().removeLast();
        }

        //add predator
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::LAlt) &&
            sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::P) &&
                (!addPressed || !predatorPressed)){
            //last check is for avoiding adding for each frame

            Vec2<unit> v(rand()%((int)(width)),rand()%height); //generate random position in window
            Vec2<unit> dir(1,1);
            predators.addBoid(Boid(v,dir,0.1,1,50));
                }
        //remove predator
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::LControl) &&
            sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::P)&&
            (!removePressed || !predatorPressed)) {
            predators.getBoids().removeLast();
            }

        ///RULES///

        //add weight to alignment
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::LAlt) &&
            sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::A) &&
                (!addPressed || !alignPressed)){
            alignment.addWeight();
                }
        //remove weight to alignment
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::LControl) &&
            sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::A)&&
            (!removePressed || !alignPressed)) {
            alignment.removeWeight();
            }
        //add weight to alignment
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::LAlt) &&
            sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::S) &&
                (!addPressed || !separationPressed)){
            separation.addWeight();
                }
        //remove weight to alignment
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::LControl) &&
            sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::S)&&
            (!removePressed || !separationPressed)) {
            separation.removeWeight();
            }
        //add weight to alignment
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::LAlt) &&
            sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::C) &&
                (!addPressed || !cohesionPressed)){
            cohesion.addWeight();
                }
        //remove weight to alignment
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::LControl) &&
            sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::C)&&
            (!removePressed || !cohesionPressed)) {
            cohesion.removeWeight();
            }

        //add 1 to r of boid
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::LAlt) &&
            sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::R) &&
                (!addPressed || !rPressed)){
            subjects.addR(1);
                }
        //remove 1 from r of boid
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::LControl) &&
            sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::R)&&
            (!removePressed || !rPressed)) {
            subjects.addR(-1);
            }

        //add 1 to distance
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::LAlt) &&
            sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::D) &&
                (!addPressed || !distancePressed)){
            subjects.addDistance(1);
                }
        //remove 1 to distance between boid
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::LControl) &&
            sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::D)&&
            (!removePressed || !distancePressed)) {
            subjects.addDistance(-1);
            }

        //add an obstacle where we clicked
        if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && (!clickPressed))
        {
            sf::Vector2i localPosition = sf::Mouse::getPosition(window);
            if ((localPosition.x > -1 && localPosition.x < width)&&
                (localPosition.y > -1 && localPosition.y < height)
                ){
                Vec2<unit> obstacle(localPosition.x,localPosition.y);
                obstacles.add(obstacle);
            }
        }
        //remove last obstacle
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::O) &&(!obstaclePressed)) {
            std::cout<<"O pressed \n";
            obstacles.removeLast();
        }
        //create a save
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::W)&&
            (!savePressed)) {
            std::cout<<"Save Pressed \n";
            save_system.createSave(this);
            }
        //load a save
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::L)&&(!loadPressed)) {
            save_system.loadSave(this);
            obstacles = this->getObstacles();
            }

        //check if key/mouse if still pressed
        addPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::LAlt);
        removePressed = sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::LControl);

        boidPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::B);
        predatorPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::P);

        separationPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::S);
        alignPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::A);
        cohesionPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::C);

        rPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::R);
        distancePressed = sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::D);

        obstaclePressed = sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::O);
        clickPressed = sf::Mouse::isButtonPressed(sf::Mouse::Button::Left);

        savePressed = sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::W);
        loadPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::L);

        window.clear();
        window.setView(simulation);

        drawObstacles();
        drawBoids();
        drawPredators();

        drawInstructions();

        window.display();

    }
}

void bd::Simulation::borderManagement(Boid &b) {
    if (b.getPos().getX()<30.f) {
        if (b.getDir().getX() < 0) { //need to go the other way
            Vec2<unit> newDir((b.getDir().getX())*(-1),b.getDir().getY());
            b.setDir(newDir);
        }
        //else it's ok
    }
    if (b.getPos().getX()> settings.getWidthWindow()-15.f) {
        if (b.getDir().getX() > 0) {
            Vec2<unit> newDir((b.getDir().getX())*(-1),b.getDir().getY());
            b.setDir(newDir);
        }
    }
    if (b.getPos().getY()<30.f) {
        if (b.getDir().getY() < 0) {
            Vec2<unit> newDir(b.getDir().getX(),(b.getDir().getY())*(-1));
            b.setDir(newDir);
        }
    }
    if (b.getPos().getY()> settings.getHeightWindow()-15.f) {
        if (b.getDir().getY() > 0) {
            Vec2<unit> newDir = Vec2<unit>(b.getDir().getX(),(b.getDir().getY())*(-1));
            b.setDir(newDir);
        }
    }
}

void bd::Simulation::obstacleManagement(Boid& b) {

        float radius = 50.f;

        Vec2<unit> pos = b.getPos();
        Vec2<unit> dir = b.getDir();
        Vec2<unit> nega_dir = dir*-1;

        for (int i = 0; i < obstacles.getSize(); i++) {

            Vec2<unit> obs = obstacles.get(i);
            double dx;
            double dy;
            double dist2;

            if (dir.getX()>0) { //to the right
                dx = obs.getX()-radius - b.getPos().getX()+dir.getX()+b.getR();
            }
            else { //to the left
                dx = obs.getX()+radius - b.getPos().getX()+dir.getX()+b.getR();
            }

            if (dir.getY()>0) { //down
                dy = obs.getY()-radius - b.getPos().getY()+dir.getY()+b.getR();
            }
            else { //up
                dy = obs.getY()+radius - b.getPos().getY()+dir.getY()+b.getR();
            }

            dist2 = dx*dx + dy*dy;

            if (dist2 <= b.getR() * b.getR() + radius*radius) {
                double distmove_x;
                double distmove_y;
                double distmove;

                if (dir.getX()>0) { //right
                    distmove_x = obs.getX()-radius - b.getPos().getX()+(dir.getX()*2)+b.getR();
                }
                else { //left
                    distmove_x = obs.getX()+radius - b.getPos().getX()+(dir.getX()*2)+b.getR();
                }

                if (dir.getY()>0) { //down
                    distmove_y = obs.getY()-radius - b.getPos().getY()+(dir.getY()*2)+b.getR();
                }
                else { //up
                    distmove_y = obs.getY()+radius - b.getPos().getY()+(dir.getY()*2)+b.getR();
                }

                distmove = distmove_x*distmove_x + distmove_y*distmove_y;

                // if I'm getting closer to obstacle
                if (distmove<=dist2) {
                    //new random direction away from obstacle
                    float x = (this->getRandomWithIntervale(5,15)-10.0f)/10.0f;
                    float y = (this->getRandomWithIntervale(5,15)-10.0f)/10.0f;
                    Vec2<unit> newDir((b.getDir().getX())+(-1*x),b.getDir().getY()+(-1*y));
                    b.setDir(newDir);

                    Vec2<unit> pos(b.getPos().getX()+(b.getDir().getX())*b.getSpeed(),
                b.getPos().getY()+(b.getDir().getY())*b.getSpeed());
                    b.setPos(pos);
                }
            }
    }
}

float bd::Simulation::getRandomWithIntervale(int maxFirst, int minSecond) {
    float result = 0.0f;

    //select interval
    if (rand() % 2 == 0)
    {
        result = rand() % maxFirst;
    }
    else
    {
        result = minSecond + rand() % maxFirst;
    }
    return result;
}

bd::Simulation::~Simulation() {
    std::cout<<"Fin de la simulation \n";
}


