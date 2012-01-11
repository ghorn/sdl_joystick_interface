# SDL Joystick Wrappers
C/C++/mex wrappers for SDL Joystick. C wrappers currently broken

## Dependencies
SDL development library

### Ubuntu
Available through apt-get

`apt-get install libsdl1.2-dev`

### OSX
Available through macports (which you can get at http://www.macports.org/install.php)

then

`port install libsdl-devel`

## To build the cpp example

    >> cd cppexample
    >> make
    >> ./cpp_example 
    initializing SDL Joystick subsystem
    found 1 joystick(s)
    Opening joystick 0... found Logitech Dual Action
    Joystick 0, name: Logitech Dual Action, buttons: [0, 0, 0, 0], axes: [0.00390637, -0.0117798, 0.00390637, 0.00390637]
    Joystick 0, name: Logitech Dual Action, buttons: [0, 0, 0, 0], axes: [0.00390637, -0.0117798, 0.00390637, 0.00390637]
    ...

## To build the mex function
from MATLAB

    >> cd mex
    >> build

Then you can call "joystick" immediately.

To see all available joysticks:

    >> joystick()
    Connected joysticks:
    0: Logitech Dual Action

To get one of those joysticks, call "joystick(joystick_index)"

    >> joystick(0)
    ans = 
    
           name: 'Logitech Dual Action'
           axes: [4x1 double]
        buttons: [12x1 double]

You don't need to call joystick() first, you can call joystick(0) immediately.

SDL and individual joysticks are opened and closed automatically by the wrapper. The SDL and joystick wrapper memory can be cleared with `clear all` or `clear mex`.

### BUG:
For some reason the first struct gotten is bad and random, you should manually discard it or suffer the consequences.

    >> clear all
    Closing "Logitech Dual Action"
    quitting SDL Joystick subsystem
    >> js = joystick(0);
    initializing SDL Joystick subsystem
    Opening joystick 0... found Logitech Dual Action
    >> js.buttons
    
    ans =
    
       1.0e+09 *
    
             0
        1.0737
        0.3022
        0.5369
        0.5396
        0.0000
        0.0000
             0
        1.9165
        0.0000
             0
        0.0002

I've tried to repeatedly grab values internally in a loop, but this does not force it to cycle. I suspect the bug is related to SDL events not working properly without having SDLMain.
