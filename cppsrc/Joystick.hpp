#pragma once

#include <SDL/SDL_joystick.h>
#include <string>

using namespace std;

class Joystick{

friend std::ostream & operator << (std::ostream &, const Joystick &);

public:
    Joystick(const int _idx);
    ~Joystick();
    void setAxis(int axisNo, int val);
    void setButton(int buttonNo, int val);
    void grabStates();

private:
    static string stateString(const Joystick &);
    static double jsIntToDouble(int in);

    SDL_Joystick * sdlJs;
    int idx;
    string name;
    int numAxes;
    int numButtons;
    double * axes;
    int * buttons;
};
