// main.c
// (c) 2011, Greg Horn

#include <stdio.h>
#include <unistd.h>


#include "../csrc/sdl_joystick_interface.h"

int
main()
{
  init_joystick();

  while(1){
    read_joystick();
    const rc_t * rc = get_rc();
    printf("throttle: % .3f, yaw: % .3f, pitch: % .3f, roll: % .3f, "
           "enable: %d, mode: %d, gear: %d, aux2: %d\n",
           rc->throttle,rc->yaw,rc->pitch,rc->roll,rc->enable,rc->mode,rc->gear,rc->aux2);
    usleep(100000);
  }

}
