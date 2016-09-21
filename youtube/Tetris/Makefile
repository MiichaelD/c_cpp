
#compiler to use
CC=g++

#compiler flags
CFLAGS=-std=c++11

#linker flags
LDFLAGS=-pthread

#source files to compile
SOURCES=Piece.cpp\
PieceFactory.cpp\
PieceQueue.cpp Score.cpp\
Board.cpp\
Game.cpp\
_5_tetris.cpp
# SOURCES=*.cpp

#object files after compilation should be sources but replacing the extension
OBJECTS=$(SOURCES:.cpp=.o)

#name of the executable
EXECUTABLE=tetris
# WAY 1) This way we preprocess compile and link everything
# all:
# 	$(CC) $(CFLAGS) $(LDFLAGS) $(SOURCES) -o $(EXECUTABLE)

###--------------------------------------------------------------------------------###



# WAY 2) this way we only preprocess and compile new/changed files
# all: virtual_example

# virtual_example: Window.o WindowSpecial.o virtual.o
# 	$(CC) $(CFLAGS) Window.o WindowSpecial.o virtual.o -o virtual

# Window.o: Window.cpp
# 	$(CC) -c $(CFLAGS) Window.cpp

# WindowSpecial.o: WindowSpecial.cpp
# 	$(CC) -c $(CFLAGS) WindowSpecial.cpp

# virtual.o: virtual.cpp
# 	$(CC) -c $(CFLAGS) virtual.cpp

###--------------------------------------------------------------------------------###



# WAY 3)this way uses the variables - SUPER FANCY
all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	@echo Linking all object files and generating an executable
	$(CC) $(CFLAGS) $(LDFLAGS) $(OBJECTS) -o $@

.cpp.o:
	$(CC) -c $(CFLAGS) $< -o $@