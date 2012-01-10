#include <SDL/SDL.h>
#include <iostream>
//#include <SDL/SDL_joystick.h>

#include "Joysticks.hpp"

Joysticks::Joysticks(){
    // init sdl if not yet initialized
    if (!SDL_WasInit(SDL_INIT_JOYSTICK)){
        cout << "initializing SDL Joystick subsystem\n";
        if (SDL_InitSubSystem(SDL_INIT_JOYSTICK)){
            cout << "SDL_InitSubSystem(SDL_INIT_JOYSTICK) fail\n";
            exit(1);
        }
        SDL_JoystickEventState(SDL_ENABLE); // make joystick events start happening
    }
}

int Joysticks::numJs(){
    return SDL_NumJoysticks();
}

void Joysticks::handleEvents(){
    map<int,Joystick*>::iterator jsit;

    SDL_JoystickUpdate();
    cout << "trying to update\n";
    while (SDL_PollEvent( &event )){
        cout << "got event!\n";

        if (event.type == SDL_QUIT ){
            cout << "sdl quit detected, exiting" << endl;
            exit(0);
        }
        
        // If an axis was changed
        if( event.type == SDL_JOYAXISMOTION ){
            jsit = jsMap.find(event.jaxis.which);
            if (jsit != jsMap.end())
                jsit->second->setAxis(event.jaxis.axis, event.jaxis.value);
        }

        // if a button was changed
        else if ( event.type == SDL_JOYBUTTONDOWN || event.type == SDL_JOYBUTTONUP){
            jsit = jsMap.find(event.jbutton.which);
            if (jsit != jsMap.end()){
                if (event.type == SDL_JOYBUTTONDOWN)
                    jsit->second->setButton(event.jbutton.button, 1);
                else
                    jsit->second->setButton(event.jbutton.button, 0);
            }
        }
    } // while (SDL_PollEvent( &event ))
}


void Joysticks::grabStates(){
    map<int,Joystick*>::iterator jsit;

//    SDL_JoystickUpdate();
    for (jsit=jsMap.begin(); jsit!=jsMap.end(); ++jsit)
        jsit->second->grabStates();
}


Joystick & Joysticks::open(const int idx){
    map<int,Joystick*>::iterator jsit = jsMap.find(idx);

    if (jsit != jsMap.end()){
        cerr << "joystick " << idx << " was already open\n";
        return *(jsit->second);
    }

    jsMap.insert(std::pair<int,Joystick*>(idx,new Joystick(idx)));

    return *(jsMap.find(idx)->second);
}

Joysticks::~Joysticks(){
    for( map<int,Joystick*>::iterator ii=jsMap.begin(); ii!=jsMap.end(); ++ii){
        delete ii->second;
        jsMap.erase(ii->first);
    }
}
