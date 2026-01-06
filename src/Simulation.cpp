//
// Created by lison on 06/01/2026.
//

#include "../include/Simulation.hpp"

#include "SFML/Graphics/Font.hpp"
#include "SFML/Graphics/Text.hpp"


bd::Simulation::Simulation(Settings s) {

    settings = s;

    //init rules
    cohesion = Cohesion(settings.getWC());
    separation = Separation(settings.getWS());
    alignment = Alignment(settings.getWA());

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

//TODO : corriger bordure des Boids
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

            //normalisation de distance
            double len = sqrt(dir.getX()*dir.getX() + dir.getY()*dir.getY());
            if (len > 0) {
                dir = dir / len;
            }

            subjects.getBoids().get(i).setDir(dir);

            // bordure management
            if (subjects.getBoids().get(i).getPos().getX()<30.f) {
                Vec2<unit> newDir((subjects.getBoids().get(i).getDir().getX())*(-1),
                                                subjects.getBoids().get(i).getDir().getY());
                subjects.getBoids().get(i/3).setDir(newDir);
                subjects.getBoids().get(i).addBordureX(20);
            }
            if (subjects.getBoids().get(i).getPos().getX()> settings.getWidthWindow()-15.f) {
                Vec2<unit> newDir((subjects.getBoids().get(i).getDir().getX())*(-1),
                                                subjects.getBoids().get(i).getDir().getY());
                subjects.getBoids().get(i).setDir(newDir);
                subjects.getBoids().get(i).addBordureX(20);
            }
            if (subjects.getBoids().get(i).getPos().getY()<30.f) {
                Vec2<unit> newDir(subjects.getBoids().get(i).getDir().getX(),
                                                (subjects.getBoids().get(i).getDir().getY())*(-1));
                subjects.getBoids().get(i).setDir(newDir);
                subjects.getBoids().get(i).addBordureY(20);
            }
            if (subjects.getBoids().get(i).getPos().getY()> settings.getHeightWindow()-15.f) {
                Vec2<unit> newDir = Vec2<unit>(subjects.getBoids().get(i).getDir().getX(),
                                                (subjects.getBoids().get(i).getDir().getY())*(-1));
                subjects.getBoids().get(i).setDir(newDir);
                subjects.getBoids().get(i).addBordureY(20);
            }


        Vec2<unit> pos(subjects.getBoids().get(i).getPos().getX()+
                (subjects.getBoids().get(i).getDir().getX())*subjects.getBoids().get(i).getSpeed(),
            subjects.getBoids().get(i).getPos().getY()+
            (subjects.getBoids().get(i).getDir().getY())*subjects.getBoids().get(i).getSpeed());

        subjects.getBoids().get(i).setPos(pos);

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

            // Origine au centre sinon le boid tourne autour d'un coin
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

    for (std::size_t i = 0; i < predators.getBoids().getSize(); i ++)
            {
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

            //normalisation de distance
            double len = sqrt(dir.getX()*dir.getX() + dir.getY()*dir.getY());
            if (len > 0) {
                dir = dir / len;
            }

            predators.getBoids().get(i).setDir(dir);

            Vec2<unit> pos(predators.getBoids().get(i).getPos().getX()+
                (predators.getBoids().get(i).getDir().getX())*predators.getBoids().get(i).getSpeed(),
            predators.getBoids().get(i).getPos().getY()+
            (predators.getBoids().get(i).getDir().getY())*predators.getBoids().get(i).getSpeed());

            predators.getBoids().get(i).setPos(pos);

        // bordure management
            if (predators.getBoids().get(i).getPos().getX()<=15.f) {
                Vec2<unit> newDir(predators.getBoids().get(i).getDir().getX()*-1,
                                                predators.getBoids().get(i).getDir().getY());
                predators.getBoids().get(i/3).setDir(newDir);
            }
            if (predators.getBoids().get(i).getPos().getX()>= settings.getWidthWindow()-15.f) {
                Vec2<unit> newDir(predators.getBoids().get(i).getDir().getX()*-1,
                                                predators.getBoids().get(i).getDir().getY());
                predators.getBoids().get(i).setDir(newDir);
                }
            if (predators.getBoids().get(i).getPos().getY()<=15.f) {
                Vec2<unit> newDir(predators.getBoids().get(i).getDir().getX(),
                                                predators.getBoids().get(i).getDir().getY()*-1);
                predators.getBoids().get(i).setDir(newDir);
            }
            if (predators.getBoids().get(i).getPos().getY()>= settings.getHeightWindow()-15.f) {
                Vec2<unit> newDir = Vec2<unit>(predators.getBoids().get(i).getDir().getX(),
                                                predators.getBoids().get(i).getDir().getY()*(-1));
                predators.getBoids().get(i).setDir(newDir);
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

            // Origine au centre sinon le boid tourne autour d'un coin
            convex.setOrigin({0.f, 0.f});

            convex.setPosition({pos.getX(),pos.getY()});

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
    sf::Font font("../asset/font/Roboto-Regular.ttf"); //obligatory
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

    message.operator+=("\n");

    text.setString(message);
    text.setCharacterSize(15);

    window.draw(text);
}


void bd::Simulation::drawSimulation() {
    unsigned width = settings.getWidthWindow();
    unsigned height = settings.getHeightWindow();
    window.create(sf::VideoMode({width,height}), "My window"); //800 by 600

    sf::View simulation = window.getDefaultView();
    simulation.setViewport({{0.0f,0.0f},{1.0f,1.0f}});

    bool addPressed = false;
    bool removePressed = false;

    bool boidPressed = false;
    bool predatorPressed = false;

    bool separationPressed = false;
    bool alignPressed = false;
    bool cohesionPressed = false;

    bool rPressed = false;
    bool distancePressed = false;

    while (window.isOpen()) {
        // check all the window's events that were triggered since the last iteration of the loop
        while (const std::optional event = window.pollEvent())
        {
            // "close requested" event: we close the window
            if (event->is<sf::Event::Closed>()) {
                window.close();
            }
        }

        //add boid
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::LAlt) &&
            sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::B) &&
                (!addPressed || !boidPressed)){
            //dernière vérification pour éviter d'ajouter à chaque frame

            Vec2<unit> v(rand()%((int)(width)),rand()%height); //génére position random dans la fenêtre
            Vec2<unit> dir(1,1); //revoir dir avec Marine
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
            //dernière vérification pour éviter d'ajouter à chaque frame

            Vec2<unit> v(rand()%((int)(width)),rand()%height); //génére position random dans la fenêtre
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

        addPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::LAlt);
        removePressed = sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::LControl);

        boidPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::B);
        predatorPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::P);

        separationPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::S);
        alignPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::A);
        cohesionPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::C);

        rPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::R);
        distancePressed = sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::D);


        window.clear();
        window.setView(simulation);

        drawBoids();
        drawPredators();
        drawInstructions();

        window.display();

    }
}

bd::Simulation::~Simulation() {
    std::cout<<"Fin de la simulation \n";
}


