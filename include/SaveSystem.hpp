#ifndef BLOIS_SAVESYSTEM_HPP
#define BLOIS_SAVESYSTEM_HPP
#include <string>

#include "Simulation.hpp"

namespace bd {

    class SaveSystem {
        std::string filemway = "save/";

    public:

        SaveSystem();
        ~SaveSystem();
        void loadSave(Simulation* s);
        void createSave(Simulation* s);
    };

}

#endif //BLOIS_SAVESYSTEM_HPP