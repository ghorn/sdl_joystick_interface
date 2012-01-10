// sdl_joystick_interface.c
// (c) 2011, Greg Horn

#include <string.h>
#include <stdio.h>

#include <SDL/SDL.h>
#include <SDL/SDL_joystick.h>

#include "sdl_joystick_interface.h"

#define BOUND(x, min, max) {                    \
    if ((x) > (max)) (x) = (max);               \
    if ((x) < (min)) (x) = (min);               \
  }

//The event structure
SDL_Event event;

//The joystick that will be used
SDL_Joystick * stick = NULL;

uint8_t joystick_detected;

rc_t rc;

int
init_joystick()
{
  rc.throttle = 0;
  rc.yaw      = 0;
  rc.pitch    = 0;
  rc.roll     = 0;
  rc.gear     = 0;
  rc.mode     = 0;
  rc.aux2     = 0;
  rc.enable   = 0;

  //Initialize all SDL subsystems
  if( SDL_InitSubSystem( SDL_INIT_JOYSTICK ) == -1 ){
    printf("\n\nSDL_InitSubSystem fail...\n\n\n");
    joystick_detected = 0;
    return 1;
  }

  //Check if there's any joysticks
  if( SDL_NumJoysticks() < 1 )
  {
    printf("\n\nno joystick detected, using default values\n\n\n");
    joystick_detected = 0;
    return 1;
  } else {
    joystick_detected = 1;
  }

  //Open the joystick
  stick = SDL_JoystickOpen( 0 );

  //If there's a problem opening the joystick
  if( stick == NULL ){
    printf("\n\nproblem opening joystick...\n\n\n");
    joystick_detected = 0;
    return 1;
  }

  return 0;
}


static void clean_up(void)
{
  //Close the joystick
  SDL_JoystickClose( stick );

  //Quit SDL
  SDL_Quit();
}


static void handle_logitech_event(void)
{
  //If an axis was changed
  if( event.type == SDL_JOYAXISMOTION )
  {
    if( event.jaxis.which == 0 )
    {
      switch(event.jaxis.axis){
      case 0:
        if (event.jaxis.value > 0)
          rc.yaw = event.jaxis.value/32767.0;
        else
          rc.yaw = event.jaxis.value/32768.0;
        break;
      case 1:
      {
        double value;
        if (event.jaxis.value > 0)
          value = -event.jaxis.value/32767.0;
        else
          value = -event.jaxis.value/32768.0;
#ifdef INTEGRATE_LOGITECH_THROTTLE
        rc.throttle += 0.01*value;
        // rc.throttle is bound to (0,1) before output
#else
        rc.throttle = 0.5*(value + 1.0);
#endif
      }
      break;
      case 2:
        if (event.jaxis.value > 0)
          rc.roll = event.jaxis.value/32767.0;
        else
          rc.roll = event.jaxis.value/32768.0;
        break;
      case 3:
        if (event.jaxis.value > 0)
          rc.pitch = event.jaxis.value/32767.0;
        else
          rc.pitch = event.jaxis.value/32768.0;
        break;
      default:
        break;
      } // switch(event.jaxis.axis)
    } // if (event.jaxis.which == 0)
  } // if (event.type == SDL_JOYAXISMOTION)
  else if( event.type == SDL_JOYBUTTONDOWN ){
    if( event.jbutton.which == 0 )
    {
      switch(event.jbutton.button){ // button toggler, 3 state for mode/aux2
        // 2 state for gear/enable
      case 4:
        rc.mode++;
        if (rc.mode > 2)
          rc.mode = 0;
        break;
      case 5:
        rc.aux2++;
        if (rc.aux2 > 2)
          rc.aux2 = 0;
        break;
      case 6:
        rc.gear++;
        if (rc.gear > 1)
          rc.gear = 0;
        break;
      case 7:
        rc.enable++;
        if (rc.enable > 1)
          rc.enable = 0;
        break;
      default:
        break;
      } // switch(event.jaxis.button)
    } // if (event.jbutton.which == 0)
  } // else if (event.type == SDL_JOYBUTTONDOWN)
}

void read_joystick()
{
  while( SDL_PollEvent( &event ) )
  {
    if (joystick_detected == 1){
      //Handle events for the joystick
      handle_logitech_event();
    }

    BOUND(rc.roll,-1,1);
    BOUND(rc.pitch,-1,1);
    BOUND(rc.yaw,-1,1);
    BOUND(rc.throttle,0,1);

    //If the user has Xed out the window
    if( event.type == SDL_QUIT )
    {
      //Quit the program
      printf("\nsdl quitting, yo\n"); // if you don't handle this, you can't ctrl-c out
      clean_up();
      exit(1);
    }
  }
}

const rc_t * get_rc(){
  return &rc;
}
