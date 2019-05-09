CC = g++
CFLAGS = -Wall -Werror -pedantic -Wextra -std=c++14
EXEC_NAME = bin/warY
INCLUDES = `simple2d --libs`
LIBS =
SRC_FILES = src/main.cpp src/GameEngine.cpp
INSTALL_DIR = /usr/bin

all :
	$(CC) $(CFLAGS) $(SRC_FILES) $(INCLUDES) -o $(EXEC_NAME)

clean :
	rm -f $(EXEC_NAME)

run :
	$(EXEC_NAME)