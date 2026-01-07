#ifndef BLOIS_SAVESYSTEM_HPP
#define BLOIS_SAVESYSTEM_HPP
#include <string>

#include "Simulation.hpp"

namespace bd {

    class SaveSystem {
        std::string filemway = "save/";

    public:
        /**
         * Constructor without argument
         */
        SaveSystem();

        /**
         * Destructor
         */
        ~SaveSystem();

        /**
         * Modify the simulation given in argument to be identical to the one that got saved in the folder save
         * @param s Where the simulation is in the memory in order to modify it
         */
        void loadSave(Simulation* s);

        /**
         * Get all information of the simulation given in argument to create a save file inside the folder save
         * @param s Where the simulation is in the memory in order to get all information
         */
        void createSave(Simulation* s);
    };

}

#endif //BLOIS_SAVESYSTEM_HPP
