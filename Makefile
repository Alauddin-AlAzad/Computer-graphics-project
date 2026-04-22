UNAME := $(shell uname -s)

ifeq ($(UNAME), Darwin)          # macOS
  LDFLAGS = -framework OpenGL -framework GLUT -Wno-deprecated
else ifeq ($(UNAME), Linux)       # Linux
  LDFLAGS = -lGL -lGLU -lglut -lm
else                              # Windows / MinGW
  LDFLAGS = -lfreeglut -lopengl32 -lglu32 -lm
endif

CC     = g++
CFLAGS = -Wall -Wno-deprecated -Wno-deprecated-declarations
TARGET = solar_blast
SRCS   = $(wildcard *.cpp)
OBJS   = $(SRCS:.cpp=.o)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS)

%.o: %.cpp
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f *.o $(TARGET) $(TARGET).exe hardinge_bridge split.py split_it.py split_to_files.py *~ test.cpp

run: all
	./$(TARGET)
