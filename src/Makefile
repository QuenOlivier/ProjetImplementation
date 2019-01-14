CXXFLAGS =  -g -Wall
LDFLAGS =
SRCS = $(wildcard *.cpp)
OBJS = $(notdir $(SRCS:.cpp=.o))
PROGRAM = test
LIBS = ``

all: $(PROGRAM)

%.o: src_temp/%.cpp
	$(CXX) -MT $@ -MD -MP -MF $*.Tpo -c -o $@ $(CXXFLAGS) $<

$(PROGRAM): $(OBJS)
	$(CXX) -o $(PROGRAM) $(OBJS) $(LIBS)

clean:
	$(RM) -f *.o $(PROGRAM)
