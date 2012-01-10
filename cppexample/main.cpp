// main.cpp
// (c) 2011, Greg Horn

#include <stdio.h>
#include <iostream>

#include <SDL/SDL_joystick.h>
#include <SDL/SDL.h>

#include "../cppsrc/Joystick.hpp"
#include "../cppsrc/Joysticks.hpp"

int
main()
{
    Joysticks jss;
    int num = jss.numJs();
    cout << "found " << num << " joystick(s)\n";

    if (num == 0)
         return 1;

    int idx = 0;
    Joystick & js = jss.open(idx);

    for (int k=0; k<4; k++){
         cout << k << " is open: " << SDL_JoystickOpened(k) << endl;
    }

    for (;;){
        jss.handleEvents();
        jss.grabStates();
        cout << js;
        usleep(250000);
    }

    return 0;
}
