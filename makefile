CXX=g++
LD=g++
CFLAGS=-std=c++17
LFLAGS=
OBJS=main.o vec.o sim.o
EXE=sim

all: $(OBJS)
	$(LD) $^ -o $(EXE) $(LFLAGS)

clean:
	rm -f $(OBJS)
	rm -f $(EXE)

%.o: %.cpp
	$(CXX) -c $< $(CFLAGS) -o $@
