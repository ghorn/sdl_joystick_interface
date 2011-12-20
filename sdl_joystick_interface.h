// sdl_joystick_interface.h
// (c) 2011, Greg Horn

#ifndef __SDL_JOYSTICK_INTERFACE_H__
#define __SDL_JOYSTICK_INTERFACE_H__

#include <inttypes.h>

//#define INTEGRATE_LOGITECH_THROTTLE

typedef struct rc_t {
  double throttle;
  double pitch;
  double roll;
  double yaw;
  uint8_t gear;
  uint8_t enable;
  uint8_t aux2;
  uint8_t mode;
} rc_t;

#ifdef __cplusplus
extern "C"{
#endif

  // This fcn is always run as part of the simulator initialization.
  int init_joystick(void);

  // This fcn is always called periodically, so that the latest joystick inputs are in an internal state.
  void read_joystick(void);

  // You should call this function to return a pointer to the joystick state
  const rc_t * get_rc(void);

#ifdef __cplusplus
}
#endif

#endif // __SDL_JOYSTICK_INTERFACE_H__
