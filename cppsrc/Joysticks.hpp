#pragma once

//#include <SDL/SDL.h>
#include <string>
#include <map>

#include "Joystick.hpp"

using namespace std;

// manages sdl interface
class Joysticks{

public:
    Joysticks();
    ~Joysticks();
    int numJs();
    Joystick & open(int idx);
    void handleEvents();
    void grabStates();

private:
    map <int,Joystick*> jsMap;
    SDL_Event event;
};
