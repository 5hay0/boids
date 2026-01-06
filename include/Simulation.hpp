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

    public:
        Settings settings;
        sf::RenderWindow window;

        Flock subjects;
        Flock predators;
        DynamicArray<Vec2<unit>> obstacles;

        Cohesion cohesion;
        Separation separation;
        Alignment alignment;



        Simulation(Settings s);
        ~Simulation();

        void drawBoids();
        void drawPredators();
        void drawObstacles();
        void drawInstructions();
        void drawSimulation();

        void reset();

    };
}


#endif //BLOIS_SIMULATION_HPP