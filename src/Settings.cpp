#include "../include/Settings.hpp"

bd::Settings::Settings(){
    nbBoids = 50;
    widthWindow = 800;
    heightWindow = 600;
    vmax = 4.f;
    amax = 0.1f;
    pixelR = 50.f;
    distMin = 20.f;
    wC = 0.01f;
    wA = 0.125f;
    wS = 0.05f;
}

int bd::Settings::getNbBoids() const{
    return nbBoids;
}
int bd::Settings::getWidthWindow() const{
    return widthWindow;
}

int bd::Settings::getHeightWindow() const {
    return heightWindow;
}

float bd::Settings::getVMax() const{
    return vmax;
}

float bd::Settings::getAMax() const{
    return amax;
}

float bd::Settings::getPixelR() const{
    return pixelR;
}

float bd::Settings::getDistMin() const{
    return distMin;
}

float bd::Settings::getWC() const{
    return wC;
}

float bd::Settings::getWA() const{
    return wA;
}

float bd::Settings::getWS() const{
    return wS;
}

void bd::Settings::setNbBoids(const int& n){
    nbBoids = clamp(n, 10, 200);
}

void bd::Settings::setPixelR(const float& n){
    pixelR = clamp(n, 10.f, 100.f);
}

void bd::Settings::setDistMin(const float& n){
    distMin = clamp(n, 5.f, 50.f);
}

void bd::Settings::setWC(const float& n){
    wC = clamp(n, 0.f, 1.f);
}

void bd::Settings::setWA(const float& n){
    wA = clamp(n, 0.f, 1.f);
}

void bd::Settings::setWS(const float& n){
    wS = clamp(n, 0.f, 1.f);
}