#include <algorithm>
#include <iostream>

#include "include/Rule.hpp"

#include "include/Settings.hpp"

#include <cstdlib> //pour random number
#include <thread>


#include "SFML/Graphics/CircleShape.hpp"
#include "SFML/Graphics/RectangleShape.hpp"

#include "SFML/Graphics/RenderWindow.hpp"
#include "SFML/Graphics/View.hpp"

#include "SFML/Window/VideoMode.hpp"
#include "SFML/Window/Window.hpp"


using namespace bd;


/*int main()
{
    sf::RenderWindow window(sf::VideoMode({800, 200}), "Scrollbar horizontale");
    window.setFramerateLimit(60);

    // Barre
    sf::RectangleShape bar(sf::Vector2f(400.f, 6.f));
    bar.setPosition({200.f, 100.f});
    bar.setFillColor(sf::Color(150, 150, 150));

    // Curseur
    sf::RectangleShape slider(sf::Vector2f(14.f, 24.f));
    slider.setFillColor(sf::Color::Red);
    slider.setOrigin({7.f, 12.f});
    slider.setPosition({200.f, 103.f});

    bool dragging = false;

    const float minX = bar.getPosition().x;
    const float maxX = bar.getPosition().x + bar.getSize().x;

    int lastValue = -1;

    while (window.isOpen())
    {
        while (const auto event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();

            if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
            {
                if (slider.getGlobalBounds().contains(
                        window.mapPixelToCoords(sf::Mouse::getPosition(window))))
                {
                    dragging = true;
                }
            }

            if (event->is<sf::Event::MouseButtonReleased>())
                dragging = false;
        }

        if (dragging)
        {
            float mouseX = window.mapPixelToCoords(
                sf::Mouse::getPosition(window)).x;

            mouseX = std::clamp(mouseX, minX, maxX);
            slider.setPosition({mouseX, slider.getPosition().y});

            // Conversion position → valeur 0..10
            float ratio = (mouseX - minX) / (maxX - minX);
            int value = static_cast<int>(ratio * 10.f + 0.5f);

            if (value != lastValue)
            {
                std::cout << "Valeur : " << value << std::endl;
                lastValue = value;
            }
        }

        window.clear(sf::Color::Black);
        window.draw(bar);
        window.draw(slider);
        window.display();
    }

    return 0;
}*/


int main(){
    std::cout << "Main test start";

    const Settings settings;
    sf::RenderWindow window;
    unsigned height = settings.getHeightWindow();
    unsigned width = settings.getWidthWindow();

    std::cout<<"Main: height, width window"<< height << width ;
    std::cout<<"Main nb boids :"<<settings.getNbBoids();

    Flock flockTest = Flock(settings.getNbBoids());
    for (int i = 0; i<settings.getNbBoids(); i++) {
        Vec2<unit> v(rand()%((int)(width*0.75)),rand()%height); //génére position random dans la fenêtre
        Vec2<unit> dir(1,1); //revoir dir avec Marine
        flockTest.addBoid(Boid(v,dir,10,4,50));
    }

    DynamicArray<Boid> verif = flockTest.getBoids();
    /*for (int i = 0; i<settings.getNbBoids(); i++) { //It work
        flockTest.getBoids().get(i).getPos().operator<<(std::cout<<"Boid n"<<i<<":");
    }*/

    //Rules setting

    Cohesion cohesion = Cohesion(settings.getWC());
    Separation separation = Separation(settings.getWS());
    Alignment alignment = Alignment(settings.getWA());

    //Pas de liste pour l'instant

    //------------FRONT PART (NEED TO BE MOVE)-------------//


    window.create(sf::VideoMode({width,height}), "My window"); //800 by 600

    /*sf::CircleShape tester{50.f};
    tester.setPosition({100,100});*/


    // create triangles
    sf::VertexArray triangles(sf::PrimitiveType::Triangles);

    for (int i = 0; i< settings.getNbBoids(); i++)
    {
        sf::Vector2f pos(flockTest.getBoids().get(i).getPos().getX(), flockTest.getBoids().get(i).getPos().getY());

        sf::Vertex v1;
        v1.position = sf::Vector2f(0.f+pos.x, -10.f+pos.y);
        v1.color = sf::Color::White;

        sf::Vertex v2;
        v2.position = sf::Vector2f(-7.f+pos.x, 10.f+pos.y);
        v2.color = sf::Color::White;

        sf::Vertex v3;
        v3.position = sf::Vector2f(7.f+pos.x, 10.f+pos.y);
        v3.color = sf::Color::White;

        triangles.append(v1);
        triangles.append(v2);
        triangles.append(v3);
    }

    // test position
    for (std::size_t i = 0; i < triangles.getVertexCount(); i += 3)
    {
        flockTest.getBoids().get(i/3).getPos().operator<<(std::cout << "Triangle " << (i / 3) << "(");
        std::cout<<"):\n";

        for (int j = 0; j < 3; ++j)
        {
            sf::Vertex& v = triangles[i + j];
            std::cout << "  Vertex " << j
                      << " -> (" << v.position.x
                      << ", " << v.position.y << ")\n";
        }
    }

    sf::View simulation = window.getDefaultView();
    simulation.setViewport({{0.0f,0.0f},{0.75f,1.0f}});

    std::cout<<"\n size de simulation :"<<simulation.getSize().x<<" , "<<simulation.getSize().y;

    sf::View settingSimulation;
    settingSimulation.setViewport({{0.75f,0.0f},{0.25f,1.0f}});

    // run the program as long as the window is open
    while (window.isOpen())
    {
        // check all the window's events that were triggered since the last iteration of the loop
        while (const std::optional event = window.pollEvent())
        {
            // "close requested" event: we close the window
            if (event->is<sf::Event::Closed>()) {
                window.close();
            }

        }

        // BOID AFFICHAGE //

        window.clear();
        window.setView(simulation);

        //view simulation

        for (std::size_t i = 0; i < triangles.getVertexCount(); i += 3)
            {
                //apply rules
                Vec2<unit> cohestionVec = cohesion.apply(flockTest.getBoids().get(i/3),flockTest);
                Vec2<unit> alignmentVec = alignment.apply(flockTest.getBoids().get(i/3),flockTest);
                Vec2<unit> separationVec = separation.apply(flockTest.getBoids().get(i/3),flockTest);

            Vec2<unit> pos(flockTest.getBoids().get(i/3).getPos().getX()+
                    flockTest.getBoids().get(i/3).getDir().getX()+
                    cohestionVec.getX()+
                    alignmentVec.getX()+
                    separationVec.getX(),
                    flockTest.getBoids().get(i/3).getPos().getY()+
                    flockTest.getBoids().get(i/3).getDir().getY()+
                    cohestionVec.getY()+
                    alignmentVec.getY()+
                    separationVec.getY()
                    );

            flockTest.getBoids().get(i/3).setPos(pos);

            if (flockTest.getBoids().get(i/3).getPos().getX()<=0.f) {
                //std::cout<<"Main, je change dir x\n";
                //flockTest.getBoids().get(i/3).getPos().operator<<(std::cout << "Triangle " << (i / 3) << "(");
                //std::cout<<"):\n";
                Vec2<unit> newDir(flockTest.getBoids().get(i/3).getDir().getX()*-1,
                                                flockTest.getBoids().get(i/3).getDir().getY());
                flockTest.getBoids().get(i/3).setDir(newDir);
                flockTest.getBoids().get(i/3).getDir()<<std::cout<<"Main, je change dir x:";
            }
            if (flockTest.getBoids().get(i/3).getPos().getX()>= settings.getWidthWindow()*0.75) {
                //flockTest.getBoids().get(i/3).getPos().operator<<(std::cout << "Triangle " << (i / 3) << "(");
                //std::cout<<"):\n";
                //std::cout<<"Main, je change dir x\n";
                Vec2<unit> newDir(flockTest.getBoids().get(i/3).getDir().getX()*-1,
                                                flockTest.getBoids().get(i/3).getDir().getY());
                flockTest.getBoids().get(i/3).setDir(newDir);
                flockTest.getBoids().get(i/3).getDir()<<std::cout<<"Main, je change dir x:";
                }
            if (flockTest.getBoids().get(i/3).getPos().getY()<=0.f || flockTest.getBoids().get(i/3).getPos().getY()>= settings.getHeightWindow()) {
                //std::cout<<"Main, je change dir y\n";
                Vec2<unit> newDir = Vec2<unit>(flockTest.getBoids().get(i/3).getDir().getX(),
                                                flockTest.getBoids().get(i/3).getDir().getY()*(-1));
                flockTest.getBoids().get(i/3).setDir(newDir);
                }

            //std::cout<<"Main, je get pos\n";

            //modify the visual
                triangles[i].position.x = pos.getX()+0.f;
                triangles[i].position.y = pos.getY()-10.f;
                triangles[i].color = sf::Color::White;
            //std::cout<<"Main, je fini mon vecteur 1 \n";
                triangles[i+1].position.x = pos.getX()-7.f;
                triangles[i+1].position.y = pos.getY()+10.f;
                triangles[i+1].color = sf::Color::White;
            //std::cout<<"Main, je fini mon vecteur 2";
                triangles[i+2].position.x = pos.getX()+7.f;
                triangles[i+2].position.y = pos.getY()+10.f;
                triangles[i+2].color = sf::Color::White;
            //std::cout<<"Main, je fini mon vecteur 3";
            }

        window.draw(triangles);

        //view setting

        window.setView(settingSimulation);


        window.display();

        //thread.join();
    }



    /*for (std::size_t i = 0; i < triangles.getVertexCount(); i += 3)
    {
        flockTest.getBoids().get(i/3).getPos().operator<<(std::cout << "Triangle " << (i / 3) << "(");
        std::cout<<"):\n";

        for (int j = 0; j < 3; ++j)
        {
            sf::Vertex& v = triangles[i + j];
            std::cout << "  Vertex " << j
                      << " -> (" << v.position.x
                      << ", " << v.position.y << ")\n";
        }
    }*/

    Vec2<unit> newDir(flockTest.getBoids().get(49).getDir().getX()*-8888888.f,
                                                flockTest.getBoids().get(49).getDir().getY());
    flockTest.getBoids().get(49).setDir(newDir);
    flockTest.getBoids().get(49).getDir()<<std::cout<<"DIR :";
    return 0;
}