CXX = g++
RM = rm

CFLAGS = ``
LIBS = ``

SRCS = $(wildcard *.cpp)
OBJS = $(notdir $(SRCS:.cpp=.o))

#TARGET = testGPIO

all:
	+$(MAKE) -C GPIO
	+$(MAKE) -C QBeagleBoneBlackGPIO


$(TARGET): $(OBJS)
	$(CXX) -o $@ $^ $(CFLAGS) $(LIBS)

%.o: %.cpp
	$(CXX) -c $(CFLAGS) $<

clean:
	$(RM) -f *.o $(TARGET)
