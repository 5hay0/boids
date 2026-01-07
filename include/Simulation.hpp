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

        /**
         * Draw the flock of Boids in the simulation
         * Manage/check:
         * - the rules / movement
         * - the collision with obstacles and border
         * - reaction to predators
         */
        void drawBoids();

        /**
         * Draw the flock of Predators in the simulation
         * Manage/check:
         * - the rules / movement
         * - the collision with obstacles and border
         */
        void drawPredators();

        /**
         *  Draw all Obstacles (circles with a radius of 50)
         */
        void drawObstacles();

        /**
         *  Draw all instructions to use the simulation on the left side of the window
         */
        void drawInstructions();

        /**
         *  Manage the entire simulation :
         *  - Create the window
         *  - Manage all actions on the simulation
         *  - Call functions to draw all element
         *  @ref drawInstructions/drawObstacles/drawPredators/drawBoids
         */
        void drawSimulation();

        /**
         * Modify the direction of a Boid if it is at a border
         * @param b the Boid who's geeting checked
         */
        void borderManagement(Boid& b);

        /**
         * Generate a random number between two intervals (of the same size) for the direction of a Boid
         * @param max_first max value of the first interval (0 to max_first)
         * @param min_second min value of the second interval ( min_second to min_second+max_first)
         * @return
         */
        float getRandomWithIntervale(int max_first, int min_second);

        /**
         * Modify randomly the direction of the Boid to avoid the obstacle
         * @param b the Boid who is checked
         */
        void obstacleManagement(Boid& b);

        /**
         * Get settings of the simulation
         * @return
         */
        Settings getSettings(){return settings;}
        /**
         * Put new settings inside the simulation
         * @param s the new settings
         */
        void setSettings(Settings& s){settings = s;};
        /**
         * Get the dimention (x, y) of the simulation
         * @return
         */
        sf::Vector2u getWindowDimention(){return this->window.getSize();};
        /**
         * Modify the size of the simulation
         * @param v new dimention of the window (both value in the vector need to be positive)
         */
        void setWindowDimention(const Vec2<float> & v){this->window.setSize({(unsigned)v.getX(),(unsigned)v.getY()});};
        /**
         * Get the Flock of Boids
         * @return
         */
        Flock getSubjects(){return this->subjects;};
        /**
         * Replace the Flock of Boid with a new one
         * @param f new Flock
         */
        void setSubjects(Flock &f){this->subjects = f;};
        /**
         * Get the Flock of Predators
         * @return
         */
        Flock getPredators(){return predators;};
        /**
         * Replace the Flock of Predators with a new one
         * @param f new Flock
         */
        void setpredators(Flock &f){this->predators = f;};
        /**
         * get the array of obstacles
         * @return
         */
        DynamicArray<Vec2<unit>> getObstacles(){return obstacles;};
        /**
         * Replace the array of obstacles by a new one
         * @param o new array of obstacles
         */
        void setObstacles(DynamicArray<Vec2<unit>>& o){obstacles = o;};
        /**
         * Get the weight of Cohesion rule
         * @return
         */
        Cohesion getCohesion(){return cohesion.getWeight();};
        /**
         * Replace weight of Cohesion rule
         * @param f new weight
         */
        void setCohesion(float& f){cohesion.setWeight(f);};
        /**
         * Get the weight of Separation rule
         * @return
         */
        Separation getSeparation(){return separation.getWeight();};
        /**
         * Replace weight of Separation rule
         * @param f new weight
         */
        void setSeparation(float& f){separation.setWeight(f);};
        /**
         * Get weight of Alignment rule
         * @return
         */
        Alignment getAlignment(){alignment.getWeight();};
        /**
         * Replace weight of Alignment rule
         * @param f new weight
         */
        void setAligment(float& f){alignment.setWeight(f);};


    };
}


#endif //BLOIS_SIMULATION_HPP