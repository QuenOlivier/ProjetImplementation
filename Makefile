CXX = g++
RM = rm

CFLAGS = ``
LIBS = `BeagleBoneBlack-GPIO-master/GPIO/GPIOConst.h` `BeagleBoneBlack-GPIO-master/GPIO/GPIOManager.h`

TARGET = BBBexample 

OBJS = BBBexample.o 

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) -o $@ $^ $(CFLAGS) $(LIBS)
	
%.o: %.cpp
	$(CXX) -c $(CFLAGS) $<

clean: 
	$(RM) -f *.o $(TARGET)