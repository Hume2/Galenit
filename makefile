SOURCES = $(wildcard *.cpp) $(wildcard graphics/*.cpp) $(wildcard mesh/*.cpp)
OBJECTS = $(SOURCES:.cpp=.o)
DEPS = $(SOURCES:%.cpp=%.d)
TARGET = galenit

CFLAGS = -std=gnu++14 -Ofast
LFLAGS = -lX11 -lXi -lXmu -lglut -lGL -lGLU -lm -Ofast

all: $(TARGET)

clean:
	rm $(DEPS) $(OBJECTS) $(TARGET)

.cpp.o:
	g++ -ggdb -MMD -MP $(CFLAGS) -c $< -o $@

$(TARGET): $(OBJECTS)
	g++ $(OBJECTS) -o $(TARGET) $(LFLAGS)

-include $(DEPS)
