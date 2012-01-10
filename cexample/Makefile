C_PROJ = c_example

Q = @
CC = gcc

C_SRC = \
	main.c \
	run_realtime.c \
	../csrc/sdl_joystick_interface.c

C_OBJ = $(C_SRC:.c=.o) 

WARNINGFLAGS = -Wall -Wextra -Werror
DEBUGFLAGS = -g

INCLUDES =

CFLAGS = $(WARNINGFLAGS) $(DEBUGFLAGS) $(INCLUDES) $(OPTFLAGS) -std=gnu99 

LDFLAGS = -lSDL

.PHONY: clean

$(C_PROJ): $(C_OBJ)
	@echo LD $@
	$(Q)$(CC) $(C_OBJ) $(LDFLAGS) -o $@

%.o : %.c
	@echo CC $@
	$(Q)$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(C_PROJ)
	rm -f $(C_OBJ)
