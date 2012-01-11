// Joystick.cpp

#include <SDL/SDL.h>
#include <iostream>
#include <sstream>

#include "Joystick.hpp"

Joystick::Joystick(const int _idx){
    axes = NULL;
    buttons = NULL;

    idx = _idx;

    cout << "Opening joystick " << idx << "... ";

    // make sure there are enough joysticks
    if (idx >= SDL_NumJoysticks()){
        cout << "Can't open joystick " << idx << " because only " << SDL_NumJoysticks() << " joysticks seen\n";
        return;
    }

    // open the joystick
    if ((sdlJs = SDL_JoystickOpen( idx )) == NULL){
        cout << "SDL_JoystickOpen() fail\n";
        return;
    }

    name = string(SDL_JoystickName(idx));
    cout << "found " << name << endl;

    numAxes = SDL_JoystickNumAxes(sdlJs);
    numButtons = SDL_JoystickNumButtons(sdlJs);

    axes    = (double*)malloc(sizeof(double)*numAxes);
    buttons = (int*)malloc(sizeof(int)*numButtons);
}

Joystick::~Joystick(){
    cout << "Closing \"" << name << "\"" << endl;
    if (axes != NULL)
        delete axes;
    if (buttons != NULL)
        delete buttons;
    SDL_JoystickClose(sdlJs);
}


// make nice string
string Joystick::stateString(const Joystick & js){
    ostringstream outs;
    outs << "Joystick " << js.idx << ", ";
    outs << "name: " << js.name << ", ";
    outs << "buttons: [";
    outs << js.buttons[0];
    for (int k=1; k<js.numButtons; k++)
        outs << ", " << js.buttons[k];
    outs << "], axes: [";
    outs << js.axes[0];
    for (int k=1; k<js.numAxes; k++)
        outs << ", " << js.axes[k];
    outs << "]" << endl;

    return outs.str();
}

// overloaded <<
std::ostream & operator << (std::ostream & stream, const Joystick & js){
    return stream << Joystick::stateString(js);
}


void Joystick::setAxis(int axisNo, int val){
    if (axisNo > numAxes){
        cerr << "Joystick::setAxis() called on axisNo: " << axisNo << " but only has " << numAxes << " axes\n";
        return;
    }
    axes[axisNo] = jsIntToDouble(val);
}

void Joystick::setButton(int buttonNo, int val){
    if (buttonNo > numButtons){
        cerr << "Joystick::setButton() called on buttonNo: " << buttonNo << " but only has " << numButtons << " buttons\n";
        return;
    }
    buttons[buttonNo] = val;
}

double Joystick::getAxis(int axisNo){
    if (axisNo > numAxes){
        cerr << "Joystick::getAxis() called on axisNo: " << axisNo << " but only has " << numAxes << " axes\n";
        return -1;
    }
    return axes[axisNo];
}

int Joystick::getButton(int buttonNo){
    if (buttonNo > numButtons){
        cerr << "Joystick::getButton() called on buttonNo: " << buttonNo << " but only has " << numButtons << " buttons\n";
        return -1;
    }
    return buttons[buttonNo];
}


int Joystick::getNumAxes(){
    return numAxes;
}

int Joystick::getNumButtons(){
    return numButtons;
}

string Joystick::getName(){
    return name;
}

double Joystick::jsIntToDouble(int in){
    if (in < 0)
        return ((double)in)/(32768.0);
    else
        return ((double)in)/(32767.0);
}

void Joystick::grabStates(){
    for (int k = 0; k<numButtons; k++)
        buttons[k] = Joystick::jsIntToDouble(SDL_JoystickGetButton(sdlJs, k));
    for (int k = 0; k<numAxes; k++)
        axes[k] = Joystick::jsIntToDouble(SDL_JoystickGetAxis(sdlJs, k));
}             
