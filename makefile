CC = g++
MINGW = i686-w64-mingw32-g++
CFLAGS = -Wall -Werror -pedantic -Wextra -std=c++14
EXEC_NAME = bin/strategy
EXEC_WINDOWS = main.exe
INCLUDES = `simple2d --libs`
LIBS =
SRC_FILES = src/main.cpp src/Interaction.cpp src/GameEngine.cpp src/Square.cpp src/Player.cpp src/Draw.cpp src/Bot.cpp src/Noeud.cpp src/Tree.cpp
INSTALL_DIR = /usr/bin

all :
	$(CC) $(CFLAGS) $(SRC_FILES) $(INCLUDES) -o $(EXEC_NAME)

windows :
	 $(MINGW) $(CFLAGS) $(SRC_FILES) -o $(EXEC_WINDOWS)

clean :
	rm -f $(EXEC_NAME)

run :
	$(EXEC_NAME)