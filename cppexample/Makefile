PROJ = cpp_example

Q = @
CXX = g++

CPP_SRC = \
	main.cpp \
	../cppsrc/Joystick.cpp \
	../cppsrc/Joysticks.cpp

CPP_OBJ = $(CPP_SRC:.cpp=.o) 

WARNINGFLAGS = -Wall -Wextra -Werror
DEBUGFLAGS = -g

INCLUDES =

CPPFLAGS = $(WARNINGFLAGS) $(DEBUGFLAGS) $(INCLUDES) $(OPTFLAGS) #-std=gnu99 

LDFLAGS = -lSDL

.PHONY: clean

$(PROJ): $(CPP_OBJ)
	@echo LD $@
	$(Q)$(CXX) $(CPP_OBJ) $(LDFLAGS) -o $@

%.o : %.cpp
	@echo CXX $@
	$(Q)$(CXX) $(CPPFLAGS) -c $< -o $@

clean:
	rm -f $(PROJ)
	rm -f $(CPP_OBJ)
