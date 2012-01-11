# SDL Joystick Wrappers

## Build the cpp example

>> cd cppexample
>> make
>> ./cpp_example 
initializing SDL Joystick subsystem
found 1 joystick(s)
Opening joystick 0... found Logitech Dual Action
Joystick 0, name: Logitech Dual Action, buttons: [0, 0, 0, 0], axes: [0.00390637, -0.0117798, 0.00390637, 0.00390637]
Joystick 0, name: Logitech Dual Action, buttons: [0, 0, 0, 0], axes: [0.00390637, -0.0117798, 0.00390637, 0.00390637]
...


## Build the mex function
from Matlab

`
>> cd mex
>> build
`

Then you can call "joystick" immediately.

To see all available joysticks:

`
>> joystick()
Connected joysticks:
0: Logitech Dual Action
`

To get one of those joysticks, call joystick(joystick_index)
`
>> joystick(0)

ans = 

       name: 'Logitech Dual Action'
       axes: [4x1 double]
    buttons: [12x1 double]
`
You don't need to call joystick() first, you can call joystick(0) immediately.

SDL and individual joysticks are opened and closed automatically by the wrapper. The SDL and joystick wrapper memory can be cleared with `clear all` or `clear mex`.

