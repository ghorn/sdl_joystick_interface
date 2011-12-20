PROJ = sdl_joystick_interface_example

Q = @
CC = gcc

C_SRC = run_realtime.c \
	sdl_joystick_interface.c \
	main.c

OBJ = $(C_SRC:.c=.o) 

WARNINGFLAGS = -Wall -Wextra -Werror
DEBUGFLAGS = -g

INCLUDES =

CFLAGS = $(WARNINGFLAGS) $(DEBUGFLAGS) $(INCLUDES) $(OPTFLAGS) -std=gnu99 

LDFLAGS = -lSDL

.PHONY: clean

$(PROJ): $(OBJ)
	@echo LD $@
	$(Q)$(CC) $(OBJ) $(LDFLAGS) -o $@

%.o : %.c
	@echo CC $@
	$(Q)$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(PROJ)
	rm -f $(OBJ)
