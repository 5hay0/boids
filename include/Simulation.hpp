//
// Created by lison on 06/01/2026.
//

#include <iostream>

#include <cstdlib> //pour random number
#include <thread>


#include "Flock.hpp"
#include "Rule.hpp"
#include "Settings.hpp"
#include "SFML/Graphics/ConvexShape.hpp"

#include "SFML/Graphics/RenderWindow.hpp"
#include "SFML/Graphics/View.hpp"

#include "SFML/Window/VideoMode.hpp"
#include "SFML/Window/Window.hpp"
#include "SFML/System/Angle.hpp"


#ifndef BLOIS_SIMULATION_HPP
#define BLOIS_SIMULATION_HPP


namespace bd {

    class Simulation {


        Settings settings;
        sf::RenderWindow window;

        Flock subjects;
        Flock predators;
        DynamicArray<Vec2<unit>> obstacles;

        Cohesion cohesion;
        Separation separation;
        Alignment alignment;
        Fuite fuite;

    public:

        Simulation(Settings s);
        ~Simulation();

        void drawBoids();
        void drawPredators();
        void drawObstacles();
        void drawInstructions();
        void drawSimulation();

        void borderManagement(Boid& b);

        float getRandomWithIntervale(int max_first, int min_second);

        void obstacleManagement(Boid& b);

        Settings getSettings(){return settings;}

        void setSettings(Settings& s){settings = s;};

        sf::Vector2u getWindowDimention(){return this->window.getSize();};
        void setWindowDimention(const Vec2<float> & v){this->window.setSize({(unsigned)v.getX(),(unsigned)v.getY()});};

        Flock getSubjects(){return this->subjects;};
        void setSubjects(Flock &f){this->subjects = f;};

        Flock getPredators(){return predators;};
        void setpredators(Flock &f){this->predators = f;};

        DynamicArray<Vec2<unit>> getObstacles(){return obstacles;};
        void setObstacles(DynamicArray<Vec2<unit>>& o){obstacles = o;};

        Cohesion getCohesion(){return cohesion.getWeight();};
        void setCohesion(float& f){cohesion.setWeight(f);};
        Separation getSeparation(){return separation.getWeight();};
        void setSeparation(float& f){separation.setWeight(f);};
        Alignment getAlignment(){alignment.getWeight();};
        void setAligment(float& f){alignment.setWeight(f);};


    };
}


#endif //BLOIS_SIMULATION_HPP