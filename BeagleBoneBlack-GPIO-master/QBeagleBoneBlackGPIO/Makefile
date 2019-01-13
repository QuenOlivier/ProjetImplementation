CXX = g++
RM = rm

CFLAGS = ``
LIBS = ``

SRCS = $(wildcard *.cpp)
OBJS = $(notdir $(SRCS:.cpp=.o))

TARGET = testQGPIO

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) -o $@ $^ $(CFLAGS) $(LIBS)

%.o: %.cpp
	$(CXX) -c $(CFLAGS) $<

clean:
	$(RM) -f *.o $(TARGET)
