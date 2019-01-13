CXX = g++
RM = rm

CFLAGS = ``
LIBS = `BeagleBoneBlack-GPIO-master/GPIO/GPIOConst.h` `BeagleBoneBlack-GPIO-master/GPIO/GPIOManager.h`

SRCS = $(wildcard *.cpp)
OBJS = $(notdir $(SRCS:.cpp=.o))

TARGET = BBBexample

all:
	+$(MAKE) -C BeagleBoneBlack-GPIO-master
	+$(MAKE) -C BBB-eQEP-master
	+$(TARGET)

$(TARGET): $(OBJS)
	$(CXX) -o $@ $^ $(CFLAGS) $(LIBS)

%.o: %.cpp
	$(CXX) -c $(CFLAGS) $<

clean:
	$(RM) -f *.o $(TARGET)
