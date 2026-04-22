ifeq ($(OS),Windows_NT)           # Windows
  LDFLAGS = -lfreeglut -lopengl32 -lglu32 -lm
  CC = c:/msys64/mingw64/bin/g++
else ifeq ($(shell uname -s), Darwin)          # macOS
  LDFLAGS = -framework OpenGL -framework GLUT -Wno-deprecated
  CC = g++
else                              # Linux
  LDFLAGS = -lGL -lGLU -lglut -lm
  CC = g++
endif

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
	-del /Q *.o $(TARGET) $(TARGET).exe hardinge_bridge split.py split_it.py split_to_files.py test.cpp 2>nul

run: all
	$(TARGET).exe
