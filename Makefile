CXXFLAGS = -g -Wall
RM = rm
SRCS = $(wildcard *.cpp)

PROGRAM = BBBexample
OBJS = $(notdir $(SRCS:.cpp=.o))

all: $(PROGRAM)


	
%.o: %.cpp
	$(CXX) -MT $@ -MD -MP -MF $*.Tpo -c -o $@ $(CXXFLAGS) $<

$(PROGRAM): $(OBJS)
	$(CXX) -o $(PROGRAM) $(OBJS) $(LIBS)

clean: 
	$(RM) -f *.o $(PROGRAM)
