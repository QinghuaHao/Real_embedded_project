FILES = \
        main.cpp \

#	PointSwitch.cpp \
 	SteeringEngine.cpp \     

OBJS = $(patsubst %.cpp, %.o, $(FILES))

DIR = $(foreach n,$(dir $(FILES)),.obj/$(n))

INCLUDES +=$(foreach n,$(dir $(FILES)),-I $(n))
INCLUDES += -I ./




EXENAME = server
BIN = ./$(EXENAME)

CPPFLAGS= -g -Wall -O0
CPPFLAGS  +=   -fomit-frame-pointer 
CPPFLAGS  +=  -Wall -Wundef -Wpointer-arith -fPIC

LIBS = -lpthread -lrt  -lm -lpigpio
LIBPATH = \
          -L ./ \
 
.PHONY:all
all : DIRS $(BIN)
$(BIN) :  $(OBJS)
	@echo "Linking" $(BIN)
	$(CXX) -o $@ $^ $(LIBPATH) $(LIBS)

.cpp.o :
	@echo "Compiling $<"
	$(CXX) $(CPPFLAGS) $(INCLUDES) -c $< -o $@ 

DIRS :
	@mkdir -p $(DIR)


.PHONY:clean
clean:
	@echo "rm "$(OBJS)
	rm -f *.o 
