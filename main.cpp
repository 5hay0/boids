#include "include/Settings.hpp"

#include "Simulation.hpp"


using namespace bd;



int main() {

    //TODO : give the possibility to change default settings
    Settings settings = Settings();
    Simulation simulation = Simulation(settings);

    simulation.drawSimulation();

    return 0;
}