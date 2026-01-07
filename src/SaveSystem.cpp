#include "../include/SaveSystem.hpp"
#include <iostream>
#include <filesystem>
#include <fstream>
#include <sstream>
#include <string>

namespace fs = std::filesystem;

bd::SaveSystem::SaveSystem() {}

bd::SaveSystem::~SaveSystem() {}

void bd::SaveSystem::createSave(Simulation* s) {

    std::string save = "";
    std::cout << "Nom de la sauvegarde: ";
    std::getline(std::cin, save);
    std::string path =filemway+save+".txt";

    std::ofstream file(path); // create OR overwrite
    if (!file) {
        // erreor (invalid path, rights...)
        return;
    }

    Flock flock = s->getSubjects();
    Flock flock2 = s->getPredators();
    const auto& boids = flock.getBoids();
    const auto& predators = flock2.getBoids();
    const auto& obstacles = s->getObstacles();

    file << "SAVE\n\n";

    // World
    file << "WINDOW DIMENTION\n";
    file << "width "  << s->getWindowDimention().x  << "\n";
    file << "height " << s->getWindowDimention().y << "\n";

    // Boids
    file << "BOIDS\n";
    file << "count " << boids.getSize() << "\n";

    for (size_t i = 0; i < boids.getSize() ; ++i) {
        const Boid& b = boids.get(i);

        Vec2<float> dir = b.getDir();

        file << "boid "  // type
            << b.getPos().getX() << " " << b.getPos().getY() << " "  // position
            << dir.getX() << " " << dir.getY() << " " // direction
            << b.getSpeed() << " " << b.getSpeedMax() << " " << b.getR() << "\n";

    }

    // Predators
    file << "PREDATORS\n";
    file << "count " << predators.getSize() << "\n";

    if (predators.getSize()>0) {
        for (size_t i = 0; i < predators.getSize() ; ++i) {
            const Boid& b = predators.get(i);

            Vec2<float> dir = b.getDir();

            file << "predator "  // type
                << b.getPos().getX() << " " << b.getPos().getY() << " "  // position
                << dir.getX() << " " << dir.getY() << "\n";     // direction

        }
    }

    // Obstacles
    file << "OBSTACLES\n";
    file << "count " << obstacles.getSize() << "\n";

    if (obstacles.getSize()>0) {
        for (size_t i = 0; i < obstacles.getSize() ; ++i) {
            const Vec2<unit>& b = obstacles.get(i);

            file << "obstacles "  // type
                << b.getX() << " " << b.getY() << "\n";  // position
        }
    }

    std::cout<<"Sauvegarde terminé \n";
}


void bd::SaveSystem::loadSave(Simulation* s) {
    std::string save = "";
    std::cout << "Mettre le nom du fichier a charger sans l'extention (.txt uniquement) : ";
    std::getline(std::cin, save);
    std::string file =filemway+save+".txt";

    if (save != "" && fs::exists(file) ) {
        std::cout<<"Fichier existe, chargement en cours...\n";
        std::ifstream in(file);
        std::string line;

        std::getline(in, line);

        while (std::getline(in, line)) {
            if (line == "WINDOW DIMENTION") {
                std::getline(in, line);
                unit width = (float)std::stof(line.substr(6));
                std::getline(in, line);
                unit height = (float)std::stof(line.substr(7));
                s->setWindowDimention(Vec2<float>(width,height));
            }
            else if (line == "BOIDS") {
                std::getline(in, line);
                int count = std::stoi(line.substr(6));
                s->getSubjects().clearBoid();
                Flock subject = Flock();

                for (int i = 0; i < count; ++i) {
                    std::getline(in, line);
                    std::istringstream iss(line);

                    std::string tag;
                    float x, y;
                    float dx, dy;
                    float speed, speedMax, r;

                    iss >> tag >> x >> y >> dx >> dy >> speed >> speedMax >> r;

                    //std::cout<< tag<<"\n";

                    Vec2<unit> pos(x,y);
                    Vec2<unit> dir(dx,dy);
                    Boid b(pos,dir,speed,speedMax,r);

                    subject.addBoid(b);
                }

                s->setSubjects(subject);
            }
            else if (line == "PREDATORS") {
                std::getline(in, line);
                int count = std::stoi(line.substr(6));
                s->getPredators().clearBoid();

                Flock predators = Flock();

                for (int i = 0; i < count; ++i) {
                    std::getline(in, line);
                    std::istringstream iss(line);

                    std::string tag;
                    float x, y;
                    float dx, dy;
                    float speed, speedMax, r;

                    iss >> tag >> x >> y >> dx >> dy >> speed >> speedMax >> r;

                    Vec2<unit> pos(x,y);
                    Vec2<unit> dir(dx,dy);
                    Boid b(pos,dir,speed,speedMax,r);

                    predators.addBoid(b);
                }
                s->setpredators(predators);
            }
            else if (line == "OBSTACLES") {
                std::getline(in, line);
                int count = std::stoi(line.substr(6));
                s->getObstacles().clear();

                DynamicArray<Vec2<unit>> obstacle;

                for (int i = 0; i < count; ++i) {
                    std::getline(in, line);
                    std::istringstream iss(line);

                    std::string tag;
                    float x, y;

                    iss >> tag >> x >> y ;

                    //std::cout<<"OBSTACLES \n";

                    Vec2<unit> pos(x,y);
                    Vec2<unit> b(pos);

                    obstacle.add(b);
                }
                s->setObstacles(obstacle);
            }
        }
        std::cout<<"Fin de chargement\n";
    }
    else {
        std::cout<<"Fichier introuvable, retour simulation\n";
    }

}


